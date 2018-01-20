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

#include "data.h"

#include <swephexp.h>

void posdata_new( PosData** d )
{
    assert( *d == NULL );
    Trace( printf( "-- New posdata\n" ); )
    *d = Malloc( sizeof( PosData ) );
#ifndef NDEBUG
    (*d)->planet = NULL;
    (*d)->res[0] =
    (*d)->res[1] =
    (*d)->res[2] =
    (*d)->res[3] =
    (*d)->res[4] =
    (*d)->res[5] = 0;
#endif /* !NDEBUG */
}

void posdata_delete( PosData** d )
{
    assert( *d );
    Trace( printf( "-- Delete posdata\n" ); )
    Free( *d, sizeof( PosData ) );
    *d = NULL;
}

void posdata_longitude_split( double pos, int* ret )
{
    pos = swe_degnorm( pos );
    ret[1] = (int) floor( pos / 30.0 );
    pos -= ret[1] * 30;
    ret[0] = (int) floor( pos );
    pos -= ret[0];
    ret[2] = (int) floor( pos * 60 );
    pos -= ret[2] / 60.0;
    ret[3] = (int) floor( pos * 3600 );
}

int posdata_zValuesort( const PosData** d1, const PosData** d2 )
{
    const int z1 = (*d1)->planet->zValue;
    const int z2 = (*d2)->planet->zValue;
    if ( z1 > z2 )
        return -1;
    if ( z1 < z2 )
        return 1;
    return 0;
}

void posdata_vectorize( BTree* bt, Vector** v )
{
    vector_new( v, btree_count( bt ) ); /* todo: reduce mem usage? */
    btree_vectorize( bt, (*v)->ptr );
    vector_sort( (*v), (int(*)(const void*, const void*))&posdata_zValuesort );
}

void aspectdata_new( AspectData** d )
{
    assert( *d == NULL );
    Trace( printf( "-- New aspectdata\n" ); )
    *d = Malloc( sizeof( AspectData ) );
}

void aspectdata_delete( AspectData** d )
{
    assert( *d );
    Trace( printf( "-- Delete aspectdata\n" ); )
    Free( *d, sizeof( AspectData ) );
    *d = NULL;
}

int aspectdata_deltasort( const AspectData** d1, const AspectData** d2 )
{
    const int z1 = (*d1)->delta;
    const int z2 = (*d2)->delta;
    if ( z1 < z2 )
        return -1;
    if ( z1 > z2 )
        return 1;
    return 0;
}

int aspectdata_zValuesort( const AspectData** d1, const AspectData** d2 )
{
    const int z1 = (*d1)->aspect->zValue;
    const int z2 = (*d2)->aspect->zValue;
    if ( z1 > z2 )
        return -1;
    if ( z1 < z2 )
        return 1;
    return 0;
}
