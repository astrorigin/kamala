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

#ifndef ZODIACORE_PROFILE_H
#define ZODIACORE_PROFILE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "aspectfilter.h"
#include "aspectrestr.h"
#include "orbfilter.h"
#include "orbrestr.h"
#include "planetfilter.h"

typedef struct _profile_t Profile;

struct _profile_t
{
    idx_t   _idx;
    Str*    name;
    Str*    comments;

    Bool    calcMidp;
    Bool    drawMidp;

    PlanetFilter*       planetFilter;
    AspectFilter*       aspectFilter;
    OrbFilter*          orbFilter;
    AspectRestr*        aspectRestr;
    OrbRestr*           orbRestr;
};

void profile_init( ZodiaCore* );

void profile_fini( ZodiaCore* );

void profile_new( Profile** );

void profile_delete( Profile** );

void profile_set_row( ZodiaCore*, Profile*, const sqlite_Stmt* );

void profile_copy( Profile*, const Profile* other );

idx_t profile_insert( ZodiaCore*, Profile* );

idx_t profile_update( ZodiaCore*, const Profile* );

idx_t profile_erase( ZodiaCore*, Profile* );

Profile* profile_whose_name( const ZodiaCore*, const char* );

#ifdef __cplusplus
}
#endif

#endif /* !ZODIACORE_PROFILE_H */
