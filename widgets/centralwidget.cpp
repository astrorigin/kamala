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

/** @file centralwidget.cpp
 */

#include "centralwidget.hpp"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QString>
#include <QWidget>
#include <KDebug>

#include <core.h>

#include "../application.hpp"
#include "../mainwindow.hpp"
#include "chartdockwidget.hpp"
#include "chartwidget.hpp"
#include "subwindow.hpp"


CentralWidget::CentralWidget( QWidget* parent )
    : QMdiArea( parent )
{
    setAcceptDrops( true );

    /*setBackground( QBrush( QPixmap(
        KStandardDirs::locate( "data", "kamala/pics/kamalabg.png" ) ) ) );*/

    connect( this, SIGNAL( subWindowActivated( QMdiSubWindow* ) ),
        KamalaApp->mainWindow, SLOT( internalSubWindowActivated( QMdiSubWindow* ) ) );

}

void CentralWidget::dragEnterEvent( QDragEnterEvent* ev )
{
    if ( ev->source()
        && ev->source() != (QWidget*)KamalaApp->mainWindow->chartDock->widget->chartView
        && strequ( (char*)ev->format(), (char*)"text/plain" ) )
    {
        ev->acceptProposedAction();
    }
    else ev->ignore();
}

void CentralWidget::dropEvent( QDropEvent* ev )
{
    ev->acceptProposedAction();
    KamalaApp->mainWindow->internalOpenChart(
        (idx_t) atoi( ev->mimeData()->text().toAscii().constData() ) );
}

void CentralWidget::setActiveSubWindow( int iWin )
{
    if ( iWin < 0 ) return;
    QMdiArea::setActiveSubWindow( subWindowList().at( iWin ) );
}

void CentralWidget::addSubWindow( Chart* ch )
{
    SubWindow* win = new SubWindow( ch, this );
    QMdiSubWindow* sub = QMdiArea::addSubWindow( (QMdiSubWindow*) win );
    sub->show();
}

void CentralWidget::closeSubWindow( int iWin ) const
{
    if ( iWin == -1 )
    { // close current chart
        assert( currentSubWindow() );
        currentSubWindow()->close();
    }
    else
    { // close chart at given index
        assert( iWin >= 0 && iWin < KamalaApp->core->chartCollection->len );
        subWindowList().at( iWin )->close();
    }
}

void CentralWidget::closeAllSubWindows() const
{
    const uint cnt = KamalaApp->core->chartCollection->len;
    uint i = 0;
    for ( ; i < cnt; ++i ) // crash if closed in asc order
        closeSubWindow( cnt - 1 - i );
}

#if 0
void CentralWidget::zoomIn() const
{
    Q_ASSERT(currentSubWindow() != 0);
    ((SubWindow*) currentSubWindow())->zoomIn();
}

void CentralWidget::zoomOut() const
{
    Q_ASSERT(currentSubWindow() != 0);
    ((SubWindow*) currentSubWindow())->zoomOut();
}

void CentralWidget::saveChartAsImage(const QString &path) const
{
    Q_ASSERT(currentSubWindow() != 0);
    ((SubWindow*) currentSubWindow())->saveChartAsImage(path);
}

void CentralWidget::stepBack()
{
    Q_ASSERT(currentSubWindow() != 0);
    ((SubWindow*) currentSubWindow())->stepBack();
}

void CentralWidget::stepForward()
{
    Q_ASSERT(currentSubWindow() != 0);
    ((SubWindow*) currentSubWindow())->stepForward();
}

void CentralWidget::slotChartChanged( ChartCollection *coll, Chart *ch )
{
    const int idx = coll->chartList().indexOf( ch );

    if ( idx >= 0 && idx < subWindowList().count() )
    {
        SubWindow *subw = (SubWindow*) subWindowList().at( idx );
        subw->reload();
    }
}
#endif

