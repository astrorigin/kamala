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

/** @file kgeoname.cpp
 */

#include "kgeoname.hpp"
#include <QObject>
#include <QString>

KGeoName::KGeoName( QObject* parent )
    : QObject( parent ),
    name( "" ),
    country( "" ),
    latitude( 0 ),
    longitude( 0 ),
    elevation( 0 ),
    timezone( "" ) {}

KGeoName::KGeoName( const KGeoName& other )
    : QObject(),
    name( other.name ),
    country( other.country ),
    latitude( other.latitude ),
    longitude( other.longitude ),
    elevation( other.elevation ),
    timezone( other.timezone ) {}

KGeoName& KGeoName::operator = ( const KGeoName& other )
{
    name = other.name;
    country = other.country;
    latitude = other.latitude;
    longitude = other.longitude;
    elevation = other.elevation;
    timezone = other.timezone;
    return *this;
}
