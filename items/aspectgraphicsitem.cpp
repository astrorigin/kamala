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

/** @file aspectgraphicsitem.cpp
 */

#include "aspectgraphicsitem.hpp"

#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <KLocalizedString>

#include <core.h>

#include "../application.hpp"
#include "../translation.hpp"

AspectGraphicsItem::AspectGraphicsItem( const AspectData& data, QGraphicsItem* parent )
    : QGraphicsLineItem( parent )
{
    setZValue( 10000 - data.aspect->zValue ); // just works..

    setToolTip( i18nc( "@info:tooltip {aspect} {planet 1} {planet 2}",
        "<emphasis>%1</emphasis><nl/>%2 %3",
        translation( data.aspect->name->ptr ),
        translation( data.planet1->name->ptr ),
        translation( data.planet2->name->ptr ) ) );
}
