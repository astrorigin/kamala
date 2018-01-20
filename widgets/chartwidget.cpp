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

/** @file chartwidget.cpp
 */

#include "chartwidget.hpp"

#include <QDrag>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QGridLayout>
#include <QMimeData>
#include <QWidget>
#include <KDebug>

#include "../application.hpp"
#include "../mainwindow.hpp"
#include "../models/chartmodel.hpp"
#include "../views/chartview.hpp"


ChartWidget::ChartWidget( QWidget* parent )
    : QWidget( parent )
{
    setAcceptDrops( true );

    QGridLayout* grid = new QGridLayout( this );
    setLayout( grid );

    // create the chart view
    chartView = new ChartView( KamalaApp->chartModel, this );
    grid->addWidget( chartView, 0, 0 );

}

void ChartWidget::setCurrentIndex( int idx ) const
{
    if ( idx >= KamalaApp->core->chartCollection->len )
        idx = KamalaApp->core->chartCollection->len - 1;
    chartView->setCurrentIndex( KamalaApp->chartModel->index( idx, 0 ) );
}

void ChartWidget::dragEnterEvent( QDragEnterEvent* ev )
{
    if ( ev->source()
        && ev->source() != chartView
        && strequ( (char*)ev->format(), (char*)"text/plain" ) )
    {
        ev->acceptProposedAction();
    }
    else ev->ignore();
}

void ChartWidget::dropEvent( QDropEvent* ev )
{
    ev->acceptProposedAction();
    KamalaApp->mainWindow->internalOpenChart(
        (idx_t) atoi( ev->mimeData()->text().toAscii().constData() ) );
}
