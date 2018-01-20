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

/** @file planetgraphicsitem.cpp
 */

#include "planetgraphicsitem.hpp"

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSvgItem>
#include <QMap>
#include <QMapIterator>
#include <QPair>
#include <QString>
#include <QSvgRenderer>

#include <KDebug>
#include <KLocalizedString>

#include <core.h>

#include "../application.hpp"
#include "../translation.hpp"
#include "aspectgraphicsitem.hpp"
#include "chartgraphicsitem.hpp"
#include "svgcollection.hpp"


PlanetGraphicsItem::PlanetGraphicsItem( const PosData& data, int wheel,
    int numWh, QGraphicsItem* parent )
    : QGraphicsSvgItem( parent ),
    iWheel( wheel ),
    numWheels( numWh ),
    highlighted( false )
{
    plIdx = data.planet->_idx;

    setZValue( 100000 - data.planet->zValue ); // it just works..

    SvgCollection* svgColl = SvgCollection::theme(
        KamalaApp->core->prefs->theme->ptr );

    setSharedRenderer( svgColl->renderer(
        data.planet->glyph->ptr, data.planet->color ) );

    setToolTip( i18nc( "@info:tooltip {planet} {longitude}",
        "<emphasis>%1</emphasis><nl/>%2",
        translation( data.planet->name->ptr ),
        PosData_LongitudeToString( data ) ) );
}

void PlanetGraphicsItem::mousePressEvent( QGraphicsSceneMouseEvent* ev )
{
    if ( ev->button() != Qt::LeftButton )
        return;

    ChartGraphicsItem* parentChartItem = (ChartGraphicsItem*) parentItem();

    QMapIterator<QPair<int, int>, AspectGraphicsItem*> iterAsp(
        parentChartItem->aspectItems );
    QMapIterator<int, PlanetGraphicsItem*> iterPl(
        parentChartItem->planetItems1 );

    if ( numWheels == 1 )
    { // one visible wheel

        if ( highlighted )
        { // reset opacities
            while ( iterPl.hasNext() )
            {
                iterPl.next();
                iterPl.value()->highlighted = false;
                iterPl.value()->setOpacity( 1 );
            }
            while ( iterAsp.hasNext() )
            {
                iterAsp.next();
                iterAsp.value()->setOpacity( 1 );
            }
        }
        else
        { // highlight our stuff
            // first we hide all planets
            while ( iterPl.hasNext() )
            {
                iterPl.next();
                iterPl.value()->highlighted = false;
                iterPl.value()->setOpacity( 0.3 );
            }

            while ( iterAsp.hasNext() )
            {
                iterAsp.next();

                if ( iterAsp.key().first != plIdx
                    && iterAsp.key().second != plIdx )
                {
                    iterAsp.value()->setOpacity( 0.3 );
                }
                else
                {
                    iterAsp.value()->setOpacity( 1 );

                    parentChartItem->planetItems1.value(
                        iterAsp.key().first )->setOpacity( 1 );
                    parentChartItem->planetItems1.value(
                        iterAsp.key().second )->setOpacity( 1 );
                }
            }
            setOpacity( 1 ); // show unaspected planet
            highlighted = true;
        }
    }

    else
    { // two visible wheels

        QMapIterator<int, PlanetGraphicsItem*> iterPl2(
            parentChartItem->planetItems2 );

        if ( highlighted )
        { // reset opacities
            while ( iterPl.hasNext() )
            {
                iterPl.next();
                iterPl.value()->highlighted = false;
                iterPl.value()->setOpacity( 1 );
            }
            while ( iterPl2.hasNext() )
            {
                iterPl2.next();
                iterPl2.value()->highlighted = false;
                iterPl2.value()->setOpacity( 1 );
            }
            while ( iterAsp.hasNext() )
            {
                iterAsp.next();
                iterAsp.value()->setOpacity( 1 );
            }
        }
        else
        { // highlight our stuff
            // first we hide all planets
            while ( iterPl.hasNext() )
            {
                iterPl.next();
                iterPl.value()->highlighted = false;
                iterPl.value()->setOpacity( 0.3 );
            }
            while ( iterPl2.hasNext() )
            {
                iterPl2.next();
                iterPl2.value()->highlighted = false;
                iterPl2.value()->setOpacity( 0.3 );
            }

            while ( iterAsp.hasNext() )
            {
                iterAsp.next();

                if ( iWheel == 0 )
                { // belongs to radix
                    if ( iterAsp.key().first != plIdx )
                    {
                        iterAsp.value()->setOpacity( 0.3 );
                    }
                    else
                    {
                        iterAsp.value()->setOpacity( 1 );

                        parentChartItem->planetItems1.value(
                            iterAsp.key().first )->setOpacity( 1 );
                        parentChartItem->planetItems2.value(
                            iterAsp.key().second )->setOpacity( 1 );
                    }
                }
                else
                { // clicked on 2nd wheel
                    if ( iterAsp.key().second != plIdx )
                    {
                        iterAsp.value()->setOpacity( 0.3 );
                    }
                    else
                    {
                        iterAsp.value()->setOpacity( 1 );

                        parentChartItem->planetItems1.value(
                            iterAsp.key().first )->setOpacity( 1 );
                        parentChartItem->planetItems2.value(
                            iterAsp.key().second )->setOpacity( 1 );
                    }
                }
            }
            setOpacity( 1 ); // show unaspected planet
            highlighted = true;
        }
    }
}
