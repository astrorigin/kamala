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

#ifndef ZODIACORE_ASPECT_H
#define ZODIACORE_ASPECT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "orb.h"
#include "sqlite.h"
#include "str.h"

typedef struct _aspect_t Aspect;

struct _aspect_t
{
    idx_t   _idx;
    Str*    name;
    int     family;
    Str*    comments;

    Bool    isAbs;
    int     signStrict;
    double  angle;

    Bool    defaultUse;
    Orb*    defaultOrb;

    char    color[8];
    Str*    glyph;
    int     zValue;
};

void aspect_init( ZodiaCore* );

void aspect_fini( ZodiaCore* );

void aspect_new( Aspect** );

void aspect_delete( Aspect** );

void aspect_set_row( Aspect*, const sqlite_Stmt* );

void aspect_copy( Aspect*, const Aspect* other );

idx_t aspect_insert( ZodiaCore*, Aspect* );

idx_t aspect_update( ZodiaCore*, const Aspect* );

idx_t aspect_erase( ZodiaCore*, Aspect* );


#ifdef __cplusplus
}
#endif

#endif /* !ZODIACORE_ASPECT_H */
