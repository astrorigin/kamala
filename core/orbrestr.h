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

#ifndef ZODIACORE_ORBRESTR_H
#define ZODIACORE_ORBRESTR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "btree.h"
#include "str.h"

typedef struct _orbrestr_t OrbRestr;

struct _orbrestr_t
{
    idx_t   _idx;
    Str*    name;
    Str*    comments;
    BTree*  bt;
};

void orbrestr_init( ZodiaCore* );

void orbrestr_fini( ZodiaCore* );

void orbrestr_new( OrbRestr** f );

void orbrestr_delete( OrbRestr** f );

#define orbrestr_insert( f, i, o )  btree_insert( &(f->bt), i, o, NULL )

#define orbrestr_value( f, i )      btree_value( f->bt, i )

#define orbrestr_set_value( f, i, o )   btree_set_value( f->bt, i, o )

#define orbrestr_remove( f, i )     btree_reremove( f->bt, i )


#ifdef __cplusplus
}
#endif

#endif /* !ZODIACORE_ORBRESTR_H */
