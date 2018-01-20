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

#ifndef ZODIACORE_ASPECTRESTR_H
#define ZODIACORE_ASPECTRESTR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "btree.h"
#include "str.h"

typedef struct _aspectrestr_t AspectRestr;

struct _aspectrestr_t
{
    idx_t   _idx;
    Str*    name;
    Str*    comments;
    BTree*  bt;
};

void aspectrestr_init( ZodiaCore* );

void aspectrestr_fini( ZodiaCore* );

void aspectrestr_new( AspectRestr** );

void aspectrestr_delete( AspectRestr** );

#define aspectrestr_insert( f, i, b )  btree_insert( &(f->bt), i, b, NULL )

#define aspectrestr_value( f, i )      btree_value( f->bt, i )

#define aspectrestr_set_value( f, i, b )   btree_set_value( f->bt, i, b )

#define aspectrestr_remove( f, i )     btree_reremove( f->bt, i )


#ifdef __cplusplus
}
#endif

#endif /* !ZODIACORE_ASPECTRESTR_H */
