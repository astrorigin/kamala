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

/** @file chartgraphicsview.cpp
 */

#include "chartgraphicsview.hpp"

#include <QGraphicsView>
#include <QPainter>
#include <QWidget>

#include "../scenes/chartgraphicsscene.hpp"

#include <core.h>

ChartGraphicsView::ChartGraphicsView( Chart* ch, QWidget* parent )
    : QGraphicsView( parent ),
    chart( ch )
{
    // create our scene
    ChartGraphicsScene* scene = new ChartGraphicsScene( ch, this );

    connect( scene, SIGNAL( changed( const QList<QRectF>& ) ),
        this, SLOT( updateScene( const QList<QRectF>& ) ) );

    setScene( scene );

    setRenderHints( QPainter::Antialiasing );
    setInteractive( true );
    show();
}

void ChartGraphicsView::reload()
{
    ((ChartGraphicsScene*)scene())->draw();
}
