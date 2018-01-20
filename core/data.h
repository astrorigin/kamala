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

#ifndef ZODIACORE_DATA_H
#define ZODIACORE_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "aspect.h"
#include "planet.h"
#include "vector.h"

typedef struct _posdata_t PosData;

struct _posdata_t
{
    Planet*     planet;
    double      res[6];
};

void posdata_new( PosData** );

void posdata_delete( PosData** );

void posdata_longitude_split( double pos, int* ret );

int posdata_zValuesort( const PosData**, const PosData** );

void posdata_vectorize( BTree*, Vector** );


typedef struct _aspectdata_t AspectData;

struct _aspectdata_t
{
    Planet*     planet1;
    Planet*     planet2;
    Aspect*     aspect;

    double      delta;
    int         applying;
    double      factor;
};

void aspectdata_new( AspectData** );

void aspectdata_delete( AspectData** );

int aspectdata_deltasort( const AspectData**, const AspectData** );

int aspectdata_zValuesort( const AspectData**, const AspectData** );


#ifdef __cplusplus
}
#endif

#endif /* !ZODIACORE_DATA_H */
