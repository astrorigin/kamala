/*
    This file is part of Kamala, an astrology application.
    Copyright (C) 2009 Stanislas Marquis <smarquis@chaosorigin.com>

    Kamala is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    Kamala is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Kamala.  If not, see <http://www.gnu.org/licenses/>.
*/

/** @file chartview.cpp
 */

#include "chartview.hpp"

#include <QAbstractItemModel>
#include <QContextMenuEvent>
#include <QItemSelection>
#include <QMenu>
#include <QMouseEvent>
#include <QPixmap>
#include <QPoint>
#include <QTableView>
#include <QWidget>

#include <KActionCollection>
#include <KActionMenu>
#include <KDebug>
#include <KIcon>
#include <KLocalizedString>
#include <KMenu>
#include <KMessageBox>
#include <KStandardAction>
#include <KStandardDirs>
#include <KStandardGuiItem>

#include "../application.hpp"
#include "../mainwindow.hpp"
#include "../models/chartmodel.hpp"
#include "../widgets/centralwidget.hpp"


ChartView::ChartView( const ChartModel* model, QWidget* parent )
    : QTableView( parent ),
    _dragIndex( -1 ),
    _dragPix( KIcon( "document-save" ).pixmap( 20, 20 ) )
{
    setAcceptDrops( true );

    setModel( (QAbstractItemModel*) model );

    setSelectionBehavior( SelectRows );
    setSelectionMode( SingleSelection );

    // create context menu
    KActionCollection* coll = KamalaApp->mainWindow->actionCollection();
    contextMenu = new KActionMenu( "Chart", this );
    contextMenu->addAction( coll->action( "editWheel1" ) );
    contextMenu->addAction( coll->action( "saveWheel1" ) );
    /*contextMenu->addAction( coll->action( "saveWheel1As" ) );*/
    contextMenu->addSeparator();
    contextMenu->addAction( coll->action( "closeChart" ) );
#if 0
    connect( this, SIGNAL( pressed( const QModelIndex& ) ),
        this, SLOT( viewPressed( const QModelIndex& ) ) );
#endif
    connect( this, SIGNAL( doubleClicked( const QModelIndex& ) ),
        this, SLOT( viewDoubleClicked( const QModelIndex& ) ) );
}

Chart* ChartView::selectedChart() const
{
    const QModelIndex index = selectionModel()->currentIndex();
    if ( !index.isValid() )
        return NULL;
    return (Chart*) index.internalPointer();
}

void ChartView::contextMenuEvent( QContextMenuEvent* ev )
{
    if ( !indexAt( ev->pos() ).isValid() )
        return;
    contextMenu->menu()->exec( ev->globalPos() );
}

void ChartView::selectionChanged( const QItemSelection& selected,
    const QItemSelection& deselected )
{
    QTableView::selectionChanged( selected, deselected );

    if ( selected.indexes().count() == 0 )
        return;
    const QModelIndex index = selected.indexes().at( 0 );
    assert( index.isValid() );
    // activate subwindow
    KamalaApp->mainWindow->central->setActiveSubWindow( index.row() );
    setFocus( Qt::OtherFocusReason ); // give focus back to us
}

void ChartView::mousePressEvent( QMouseEvent* ev )
{
    QTableView::mousePressEvent( ev );

    const QModelIndex index = indexAt( ev->pos() );
    if ( !index.isValid() )
    {
        _dragIndex = -1;
        return;
    }

    const Horoscope* h = ((Chart*)index.internalPointer())->wh1->horo;
    if ( !h->_idx || h->changed )
    {
        _dragStartPos = QCursor::pos();
        _dragIndex = index.row();
    }
    else _dragIndex = -1;
}

void ChartView::mouseMoveEvent( QMouseEvent* ev )
{
    if ( _dragIndex < 0 ) return;

    if ( ( ev->globalPos() - _dragStartPos ).manhattanLength()
          < QApplication::startDragDistance() ) return;

    QDrag* drag = new QDrag( this );
    drag->setDragCursor( _dragPix, Qt::CopyAction );

    QMimeData* mime = new QMimeData;
    char buf[32];
    sprintf( buf, "%d", _dragIndex );
    mime->setText( buf );
    drag->setMimeData( mime );

    drag->exec( Qt::CopyAction );
}

void ChartView::viewDoubleClicked( const QModelIndex& index )
{
    if ( !index.isValid() )
        return;
    KamalaApp->mainWindow->actionEditWheel1();
}
