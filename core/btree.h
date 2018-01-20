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

#ifndef ZODIACORE_BTREE_H
#define ZODIACORE_BTREE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _btree_t BTree;

struct _btree_t
{
    idx_t   key;
    void*   val;

    BTree*  less;
    BTree*  more;
    BTree*  parent;
};

void btree_new( BTree** );

void btree_delete( BTree** );

Bool btree_insert( BTree**, const idx_t key, const void* val, const BTree* parent );

Bool btree_remove( BTree*, const idx_t key );

BTree* btree_safe_remove( BTree*, const idx_t key );

#define btree_reremove( bt, k )     bt = btree_safe_remove( bt, k )

BTree* btree_node( const BTree*, const idx_t key );

void* btree_value( const BTree*, const idx_t key );

Bool btree_set_value( const BTree*, const idx_t key, const void* val );

void btree_num_nodes( const BTree*, uint* i );

uint btree_count( const BTree* );

uint btree_num_levels( const BTree* );

void btree_traverse( BTree*, void (*func)(void*) );

BTree* btree_root( BTree* );

#define btree_reroot( bt )      bt = btree_root( bt )

BTree* btree_least( BTree* );

BTree* btree_most( BTree* );

BTree* btree_next( BTree* );

BTree* btree_prev( BTree* );

#define btree_min( bt )     (btree_least( bt )->key)

#define btree_max( bt )     (btree_most( bt )->key)

void btree_balance( BTree* );

size_t btree_vectorize( const BTree*, void** vec );


#ifndef NDEBUG

int btree_balance_factor( const BTree* );

Bool btree_is_unbalanced( const BTree* );

#endif /* !NDEBUG */


#ifdef __cplusplus
}
#endif

#endif /* !ZODIACORE_BTREE_H */
