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

/** @file cuspgraphicsitem.cpp
 */

#include "cuspgraphicsitem.hpp"

#include <QGraphicsItem>
#include <QGraphicsLineItem>

#include <KLocalizedString>

#include <core.h>

#include "../translation.hpp"

CuspGraphicsItem::CuspGraphicsItem( int cusp, double longitude, QGraphicsItem* parent )
    : QGraphicsLineItem( parent )
{
    setToolTip( i18nc( "@info:tooltip {cusp} {longitude}",
        "<emphasis>%1</emphasis><nl/>%2",
        translationCusp( cusp ),
        LongitudeToString( longitude, 0 ) ) );
    setZValue( 1 );
}
