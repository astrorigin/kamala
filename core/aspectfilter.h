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

#ifndef ZODIACORE_ASPECTFILTER_H
#define ZODIACORE_ASPECTFILTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "btree.h"
#include "str.h"

typedef struct _aspectfilter_t AspectFilter;

struct _aspectfilter_t
{
    idx_t   _idx;
    Str*    name;
    Str*    comments;
    BTree*  bt;
};

void aspectfilter_init( ZodiaCore* );

void aspectfilter_fini( ZodiaCore* );

void aspectfilter_new( AspectFilter** );

void aspectfilter_delete( AspectFilter** );

#define aspectfilter_insert( f, i, b )  btree_insert( &(f->bt), i, b, NULL )

#define aspectfilter_value( f, i )      btree_value( f->bt, i )

#define aspectfilter_set_value( f, i, b )   btree_set_value( f->bt, i, b )

#define aspectfilter_remove( f, i )     btree_reremove( f->bt, i )


#ifdef __cplusplus
}
#endif

#endif /* !ZODIACORE_ASPECTFILTER_H */
