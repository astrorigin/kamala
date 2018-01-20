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

/** @file horoscopeview.cpp
 */

#include "horoscopeview.hpp"

#include <QAbstractItemModel>
#include <QAction>
#include <QContextMenuEvent>
#include <QCursor>
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
#include <KMenu>
#include <KMessageBox>
#include <KLocalizedString>
#include <KStandardGuiItem>

#include "../application.hpp"
#include "../mainwindow.hpp"
#include "../models/horoscopeproxymodel.hpp"
#include "../widgets/searchwidget.hpp"

HoroscopeView::HoroscopeView( HoroscopeProxyModel* model, QWidget* parent )
    : QTableView( parent ),
    _dragIndex( -1 ),
    _dragPix( KIcon( "tab-new-background" ).pixmap( 20, 20 ) )
{
    setModel( (QAbstractItemModel*) model );

    setSelectionBehavior( SelectRows );
    setSelectionMode( SingleSelection );
#if 0
    connect( this, SIGNAL( pressed( const QModelIndex& ) ),
        this, SLOT( viewPressed( const QModelIndex& ) ) );

    connect( this, SIGNAL( clicked( const QModelIndex& ) ),
        this, SLOT( viewClicked( const QModelIndex& ) ) );
    connect( this, SIGNAL( doubleClicked( const QModelIndex& ) ),
        this, SLOT( viewDoubleClicked( const QModelIndex& ) ) );
#endif

    // create context menu
    const KActionCollection* coll = KamalaApp->mainWindow->actionCollection();
    assert( coll );

    contextMenu = new KActionMenu( "Horoscope", this );
    contextMenu->addAction( coll->action( "openChart" ) );
    contextMenu->addAction( coll->action( "deleteChart" ) );
}

Horoscope* HoroscopeView::selectedHoroscope() const
{
    QModelIndex index = selectionModel()->currentIndex();
    if ( !index.isValid() )
        return 0;
    return (Horoscope*)
        ((HoroscopeProxyModel*) model())->mapToSource( index ).internalPointer();
}

void HoroscopeView::contextMenuEvent( QContextMenuEvent* ev )
{
    if ( !indexAt( ev->pos() ).isValid() )
        return;
    contextMenu->menu()->exec( ev->globalPos() );
}

void HoroscopeView::selectionChanged( const QItemSelection& selected,
    const QItemSelection& deselected )
{
    QTableView::selectionChanged( selected, deselected );
    KamalaApp->mainWindow->resetActions();
}

void HoroscopeView::mousePressEvent( QMouseEvent* ev )
{
    QTableView::mousePressEvent( ev );

    const QModelIndex index = indexAt( ev->pos() );
    if ( !index.isValid() )
    {
        _dragIndex = -1;
        return;
    }

    _dragStartPos = QCursor::pos();
    const HoroscopeProxyModel* mdl = (HoroscopeProxyModel*) model();
    _dragIndex = ((Horoscope*)mdl->mapToSource( index ).internalPointer())->_idx;
}

void HoroscopeView::mouseMoveEvent( QMouseEvent* ev )
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

#if 0
void HoroscopeView::deleteHoroscope()
{
    Horoscope *horo = selectedHoroscope();
    Q_ASSERT( horo );

    const int res = KMessageBox::warningContinueCancel( this,
        i18nc( "@info", "<warning>Are you certain you want to delete horoscope "
              "<resource>%1</resource> ?</warning>", horo->name() ),
        i18nc( "@title:window", "Delete Horoscope" ),
        KStandardGuiItem::cont(), KStandardGuiItem::cancel(),
        "HoroscopeDeletionWarning" );
    if ( res == KMessageBox::Continue )
    {
        const int idx = horo->erase();
        if ( idx > 0 )
        {
            ChartCollection::openedCharts()->horoscopeRemoved( horo );
            delete horo;
        }
        else
        {
            kWarning() << "Unable to delete horoscope" << horo->name();
        }
    }
}
#endif
