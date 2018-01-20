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

/** @file chartgraphicsscene.cpp
 */

#include "chartgraphicsscene.hpp"

#include <QBrush>
#include <QColor>
#include <QGraphicsScene>
#include <QList>
#include <QObject>
#include <QRectF>

#include "../application.hpp"
#include "../items/chartgraphicsitem.hpp"

#include <core.h>

ChartGraphicsScene::ChartGraphicsScene( Chart* ch, QObject* parent )
    : QGraphicsScene( parent ),
    chart( ch )
{
    draw();
}

void ChartGraphicsScene::draw()
{
    setBackgroundBrush( QBrush( QColor( KamalaApp->core->prefs->bgcolor ) ) );

    clear();
    //setSceneRect( 0, 0, 1080, 1527 );
    setSceneRect( 0, 0, 720, 720 );

    ChartGraphicsItem* it = new ChartGraphicsItem( chart );
    addItem( it );

    QList<QRectF> rect;
    rect << QRectF( 0, 0, 720, 720 );
    emit changed( rect );
}
