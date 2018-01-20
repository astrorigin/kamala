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

#ifndef ZODIACORE_GEOCOORD_H
#define ZODIACORE_GEOCOORD_H

#ifdef __cplusplus
extern "C" {
#endif

typedef double          GeoLat;
typedef double          GeoLon;
typedef unsigned int    GeoAlt;

typedef struct _geocoord_t GeoCoord;

struct _geocoord_t
{
    Bool    dir; /* direction: N/E = 1, S/W = 0 */
    int     deg; /* degrees */
    int     min; /* minutes */
    int     sec; /* seconds */
};

#if 0
void geocoord_new( GeoCoord** g );

void geocoord_delete( GeoCoord** g );
#endif

void geocoord_from_double( GeoCoord*, double d );

#define geocoord_to_double( g )\
    ( s->dir ? (s->deg + ((1.0/60) * s->min) + ((1.0/3600) * s->sec))\
    : -(s->deg + ((1.0/60) * s->min) + ((1.0/3600) * s->sec)) )

#define geolat_check( lat )     ( lat < -90 || lat > 90 ? 0 : 1 )

#define geolon_check( lon )     ( lon < -180 || lon > 180 ? 0 : 1 )


#ifdef __cplusplus
}
#endif

#endif /* !ZODIACORE_GEOCOORD_H */
