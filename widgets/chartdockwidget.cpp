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

/** @file chartdockwidget.cpp
 */

#include "chartdockwidget.hpp"

#include <QDockWidget>
#include <QWidget>
#include <KLocalizedString>

#include "chartwidget.hpp"


ChartDockWidget::ChartDockWidget( QWidget* parent )
    : QDockWidget( parent )
{
    setObjectName( "ChartDockWidget" );

    setWindowTitle( i18nc( "@title:window", "Opened Charts" ) );

    setAllowedAreas( Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea );

    // create internal widget
    widget = new ChartWidget( this );
    setWidget( widget );
}

void ChartDockWidget::setCurrentIndex( int iWin ) const
{
    widget->setCurrentIndex( iWin );
}
