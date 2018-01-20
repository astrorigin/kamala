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

#include "geocoord.h"

#if 0
void geocoord_new( GeoCoord** s )
{
    assert( *s == NULL );
    *s = malloc( sizeof( GeoCoord ) );
    assert( *s );

    (*s)->dir = True;
    (*s)->deg = (*s)->min = (*s)->sec = 0;
}

void geocoord_delete( GeoCoord** s )
{
    assert( *s );
    free( *s );
    *s = NULL;
}
#endif

void geocoord_from_double( GeoCoord* s, double d )
{
    s->dir = d >= 0 ? True : False;
    d = fabs( d );
    s->deg = (int) floor( d );
    d -= s->deg;
    s->min = (int) round( d * 60 );
    d -= s->min / 60.0;
    s->sec = (int) round( d * 3600 );
    if ( s->sec < 0 )
        s->sec = 0;
}

