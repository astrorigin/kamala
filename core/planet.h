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

#ifndef ZODIACORE_PLANET_H
#define ZODIACORE_PLANET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "orb.h"
#include "sqlite.h"
#include "str.h"

enum planetFamilies_t
{
    MainFamily          = 0,
    UranianFamily,
    FictitiousFamily,
    CuspsFamily,
    GauquelinFamily,
    StarsFamily,
    AsteroidsFamily,
    PartsFamily
};

typedef struct _planet_t Planet;

struct _planet_t
{
    idx_t   _idx;
    int     num;
    Str*    name;
    int     family;
    Str*    comments;

    Bool    defaultUse;
    Bool    defaultAspect;

    OrbModifier* orbModifier;

    char    color[8];
    Str*    glyph;
    int     zValue;
};

/* Concerning num
    -- from 0 to 39 : Default bodies
    -- from 40 to 58: Uranian + Fictitious bodies
    -- from 1000 to 9999: fixed stars.
    -- from 10000 : Asteroids.
    -- or negative values for other bodies :
    -- -1 = SE_ECL_NUT : Dont use here.
    -- from -2 to -99 : Bodies based on built-ins planets (Priapus, south nodes).
    -- from -100 to -199 : Houses cusps.
    -- from -200 to -299 : Bodies whose position is based on houses cusps only... if any
    -- from -300 to -? : "Parts" and other subtilities, based on houses cusps and planets.
*/

void planet_init( ZodiaCore* );

void planet_fini( ZodiaCore* );

void planet_new( Planet** );

void planet_delete( Planet** );

void planet_set_row( Planet*, const sqlite_Stmt* );

void planet_copy( Planet*, const Planet* other );

idx_t planet_insert( ZodiaCore*, Planet* );/*todo*/

idx_t planet_update( ZodiaCore*, const Planet* );

idx_t planet_erase( ZodiaCore*, Planet* );

int planet_calc( const Planet*, const double jd, const int flag, double* res );


#ifdef __cplusplus
}
#endif

#endif /* !ZODIACORE_PLANET_H */
