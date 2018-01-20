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

#ifndef ZODIACORE_WHEEL_H
#define ZODIACORE_WHEEL_H

#include "btree.h"
#include "context.h"
#include "data.h"
#include "horoscope.h"
#include "profile.h"
#include "vector.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _wheel_t Wheel;

enum wheelType_t
{
    RadixWheelType  = 0
};

struct _wheel_t
{
    int         type;
    Horoscope*  horo;
    Context*    ctxt;
    Profile*    prfl;

    BTree*          planets;
    double          cusps[37];
    double          ascmc[10];
    Vector*         aspects;
};

void wheel_new( const ZodiaCore*, Wheel** );

void wheel_delete( Wheel** );

void wheel_clear( Wheel* );

void wheel_set_swe( const Wheel* );

void wheel_calc( ZodiaCore*, Wheel* );

void wheel_calc_houses( ZodiaCore*, Wheel* );

void wheel_calc_planets( ZodiaCore*, Wheel* );

void wheel_calc_aspects( ZodiaCore*, Wheel* );


#ifdef __cplusplus
}
#endif

#endif /* !ZODIACORE_WHEEL_H */
