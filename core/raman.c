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

#include "raman.h"

int rasi_dif( int r1, int r2 )
{
    r1 = rasi_norm( r1 );
    r2 = rasi_norm( r2 );
    if ( r1 == r2 )
        return 0;
    else if ( r1 < r2 )
        return 12 - ( r2 - r1 );
    return r1 - r2;
}

int rasi_dif2( int r1, int r2 )
{
    const int i = rasi_dif( r1, r2 );
    return ( i > 6 ) ? ( -6 + ( i - 6 )) : i;
}
