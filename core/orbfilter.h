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

#ifndef ZODIACORE_ORBFILTER_H
#define ZODIACORE_ORBFILTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "btree.h"
#include "str.h"

typedef struct _orbfilter_t OrbFilter;

struct _orbfilter_t
{
    idx_t   _idx;
    Str*    name;
    Str*    comments;
    BTree*  bt;
};

void orbfilter_init( ZodiaCore* );

void orbfilter_fini( ZodiaCore* );

void orbfilter_new( OrbFilter** f );

void orbfilter_delete( OrbFilter** f );

#define orbfilter_insert( f, i, o ) btree_insert( &(f->bt), i, o, NULL )

#define orbfilter_value( f, i )     btree_value( f->bt, i )

#define orbfilter_set_value( f, i, o )   btree_set_value( f->bt, i, o )

#define orbfilter_remove( f, i )    btree_reremove( f->bt, i )


#ifdef __cplusplus
}
#endif

#endif /* !ZODIACORE_ORBFILTER_H */
