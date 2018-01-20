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

#include "btree.h"

void btree_new( BTree** bt )
{
    assert( *bt == NULL );
    Trace( printf( "-- New btree\n" ); )
    *bt = Malloc( sizeof( BTree ) );

    (*bt)->key = 0;
    (*bt)->val = (*bt)->less = (*bt)->more = (*bt)->parent = NULL;
}

void btree_delete( BTree** bt )
{
    if ( !(*bt) ) return;

    btree_delete( &(*bt)->less );
    btree_delete( &(*bt)->more );

    Trace( printf( "-- Delete btree\n" ); )
    Free( *bt, sizeof( BTree ) );
    *bt = NULL;
}

Bool btree_insert( BTree** bt, const idx_t key, const void* val, const BTree* parent )
{
    if ( !(*bt) )
    {
        btree_new( bt );
        (*bt)->key = key;
        (*bt)->val = (void*) val;
        (*bt)->parent = (BTree*) parent;
        if ( parent )
            btree_balance( (*bt)->parent );
        return True;
    }

    BTree* tmp = *bt;
    Bool b;

    if ( key < tmp->key )
        b = btree_insert( &tmp->less, key, val, tmp );

    else if ( key > tmp->key )
        b = btree_insert( &tmp->more, key, val, tmp );

    else
    {
        Debug( printf( "Error: btree duplicate key %d\n", key ); )
        return False;
    }

    return b;
}

Bool btree_remove( BTree* bt, const idx_t key )
{
    if ( !bt )
        return False;

    if ( key == bt->key )
    {
        BTree* root = bt->parent;

        if ( root && !bt->less && !bt->more )
        {
            Trace( printf( "-- Removing leaf k=%d\n", bt->key ); )
            if ( root->less && root->less == bt )
                root->less = NULL;
            else
                root->more = NULL;

            btree_balance( root );
        }
        else if ( root )
        {
            Trace( printf( "-- Removing node k=%d\n", bt->key ); )
            const uint i = bt->less ? btree_num_levels( bt->less ) + 1 : 0;
            const uint j = bt->more ? btree_num_levels( bt->more ) + 1 : 0;
            BTree* piv = NULL;

            if ( i >= j )
            {
                piv = btree_node( bt->less, btree_max( bt->less ) );
                Trace( printf( "-- Using less pivot k=%d\n", piv->key ); )
            }
            else
            {
                piv = btree_node( bt->more, btree_min( bt->more ) );
                Trace( printf( "-- Using more pivot k=%d\n", piv->key ); )
            }
            assert( piv );

            if ( piv->parent->less && piv->parent->less == piv )
                piv->parent->less = NULL;
            else
                piv->parent->more = NULL;

            if ( root->less && root->less == bt )
                root->less = piv;
            else
                root->more = piv;

            if ( bt->less )
            {
                piv->less = bt->less;
                bt->less->parent = piv;
            }
            if ( bt->more )
            {
                piv->more = bt->more;
                bt->more->parent = piv;
            }

            BTree* tmp = piv->parent;
            piv->parent = root;
            btree_balance( tmp );
        }
        else if ( !root && ( bt->less || bt->more ) )
        {
            Trace( printf( "-- Removing root node k=%d\n", bt->key ); )
            const uint i = bt->less ? btree_num_levels( bt->less ) + 1 : 0;
            const uint j = bt->more ? btree_num_levels( bt->more ) + 1 : 0;
            BTree* piv = NULL;

            if ( i >= j )
            {
                piv = btree_node( bt->less, btree_max( bt->less ) );
                Trace( printf( "-- Using less pivot k=%d\n", piv->key ); )
            }
            else
            {
                piv = btree_node( bt->more, btree_min( bt->more ) );
                Trace( printf( "-- Using more pivot k=%d\n", piv->key ); )
            }
            assert( piv );

            if ( piv->parent->less && piv->parent->less == piv )
                piv->parent->less = NULL;
            else
                piv->parent->more = NULL;

            if ( bt->less )
            {
                piv->less = bt->less;
                bt->less->parent = piv;
            }
            if ( bt->more )
            {
                piv->more = bt->more;
                bt->more->parent = piv;
            }

            BTree* tmp = piv->parent;
            piv->parent = NULL;
            btree_balance( tmp );
        }
        Trace( else printf( "-- Removing last node k=%d\n", bt->key ); )

        bt->less = bt->more = NULL;
        btree_delete( &bt );
        return True;
    }

    if ( key < bt->key )
    {
        if ( !bt->less )
            return False;
        return btree_remove( bt->less, key );
    }

    if ( !bt->more )
        return False;
    return btree_remove( bt->more, key );
}

BTree* btree_safe_remove( BTree* bt, const idx_t key )
{
    assert( bt );

    if ( !bt->parent && !bt->less && !bt->more )
    {
        if ( bt->key == key )
        {
            btree_delete( &bt );
            return NULL;
        }
        return bt;
    }
    else if ( !bt->parent )
    {
        BTree* tmp = bt->less ? bt->less : bt->more;

        if ( tmp->key == key )
            tmp = bt;

        if ( btree_remove( bt, key ) )
            return btree_root( tmp );
        return bt;
    }
    else
    {
        btree_remove( bt, key );
        return bt;
    }
}

BTree* btree_node( const BTree* bt, const idx_t key )
{
    if ( !bt )
        return NULL;

    if ( key == bt->key )
        return (BTree*) bt;

    if ( key < bt->key )
        return btree_node( bt->less, key );

    return btree_node( bt->more, key );
}

void* btree_value( const BTree* bt, const idx_t key )
{
    if ( !bt )
        return NULL;

    if ( key == bt->key )
        return bt->val;

    if ( key < bt->key )
        return btree_value( bt->less, key );

    return btree_value( bt->more, key );
}

Bool btree_set_value( const BTree* bt, const idx_t key, const void* val )
{
    BTree* nd = btree_node( bt, key );
    if ( !nd )
        return False;
    nd->val = (void*) val;
    return True;
}

void btree_num_nodes( const BTree* bt , uint* i )
{
    assert( bt );
    *i += 1;
    if ( bt->less )
        btree_num_nodes( bt->less, i );
    if ( bt->more )
        btree_num_nodes( bt->more, i );
}

uint btree_count( const BTree* bt )
{
    if ( !bt )
        return 0;
    uint i = 0;
    btree_num_nodes( bt, &i );
    return i;
}

uint btree_num_levels( const BTree* bt )
{
    assert( bt );

    if ( !bt->less && !bt->more )
        return 0;

    const uint lcnt = bt->less ? btree_num_levels( bt->less ) : 0;
    const uint mcnt = bt->more ? btree_num_levels( bt->more ) : 0;

    return 1 + ( mcnt >= lcnt ? mcnt : lcnt );
}

void btree_traverse( BTree* bt, void (*func)(void*) )
{
    if ( !bt )
        return;

    if ( bt->less )
        btree_traverse( bt->less, func );

    if ( bt->more )
        btree_traverse( bt->more, func );

    if ( bt->val )
        (*func)( &bt->val );
}

BTree* btree_root( BTree* bt )
{
    assert( bt );

    while ( bt->parent )
        bt = bt->parent;
    return bt;
}

BTree* btree_least( BTree* bt )
{
    assert( bt );

    while ( bt->less )
        bt = bt->less;
    return bt;
}

BTree* btree_most( BTree* bt )
{
    assert( bt );

    while ( bt->more )
        bt = bt->more;
    return bt;
}

BTree* btree_next( BTree* bt )
{
    assert( bt );

    if ( bt->more )
        return btree_least( bt->more );

    while ( bt->parent && bt->parent->key < bt->key )
        bt = bt->parent;
    return bt->parent;
}

BTree* btree_prev( BTree* bt )
{
    assert( bt );

    if ( bt->less )
        return btree_most( bt->less );

    while ( bt->parent && bt->parent->key > bt->key )
        bt = bt->parent;
    return bt->parent;
}

#if 0
int btree_min( BTree *bt )
{
    return btree_least( bt )->key;
    /*assert( bt );

    int min = bt->key;
    int tmp;

    if ( bt->less )
    {
        tmp = btree_min( bt->less );
        if ( tmp < min )
            min = tmp;
    }
    if ( bt->more )
    {
        tmp = btree_min( bt->more );
        if ( tmp < min )
            min = tmp;
    }

    return min;*/
}

int btree_max( BTree *bt )
{
    return btree_most( bt )->key;
    /*assert( bt );

    int max = bt->key;
    int tmp;

    if ( bt->less )
    {
        tmp = btree_max( bt->less );
        if ( tmp > max )
            max = tmp;
    }
    if ( bt->more )
    {
        tmp = btree_max( bt->more );
        if ( tmp > max )
            max = tmp;
    }

    return max;*/
}
#endif

void btree_balance( BTree* bt )
{
    assert( bt );

    const uint i = bt->less ? btree_num_levels( bt->less ) + 1 : 0;
    const uint j = bt->more ? btree_num_levels( bt->more ) + 1 : 0;

    if ( abs( j - i ) > 1 )
    {
        Trace( printf( "-- Balancing btree k=%d f=%d\n", bt->key, j - i ); )
        BTree* piv = NULL;
        BTree* root = bt->parent;

        if ( j > i )
            piv = btree_node( bt->more, btree_min( bt->more ) );
        else
            piv = btree_node( bt->less, btree_max( bt->less ) );
        assert( piv );
        Trace( printf( "-- Using pivot k=%d\n", piv->key ); )

        if ( piv->parent == bt )
        {
            piv->parent = root;
            if ( root )
            {
                if ( piv->key < root->key )
                    root->less = piv;
                else
                    root->more = piv;
            }
            bt->parent = piv;
            if ( bt->less == piv )
            {
                Trace( printf( "-- LL rotation\n" ); )
                bt->less = piv->more;
                if ( piv->more )
                    piv->more->parent = bt;
                piv->more = bt;
            }
            else
            {
                Trace( printf( "-- RR rotation\n" ); )
                bt->more = piv->less;
                if ( piv->less )
                    piv->less->parent = bt;
                piv->less = bt;
            }
        }
        else
        {
            BTree* tmp = piv->parent;
            if ( root )
            {
                if ( piv->key < root->key )
                    root->less = piv;
                else
                    root->more = piv;
            }
            if ( tmp->more == piv )
            {
                Trace( printf( "-- LR rotation\n" ); )
                if ( bt->less == tmp->parent )
                {
                    bt->less->more = NULL;
                    bt->less->parent = tmp;
                    tmp->less = bt->less;
                }
                bt->less = piv->more;
                bt->parent = piv;
                tmp->more = piv->less;
                if ( piv->less )
                    piv->less->parent = tmp;
                tmp->parent = piv;
                piv->less = tmp;
                piv->more = bt;
                piv->parent = (BTree*) root;
            }
            else
            {
                Trace( printf( "-- RL rotation\n" ); )
                if ( bt->more == tmp->parent )
                {
                    bt->more->less = NULL;
                    bt->more->parent = tmp;
                    tmp->more = bt->more;
                }
                bt->more = piv->less;
                bt->parent = piv;
                tmp->less = piv->more;
                if ( piv->more )
                    piv->more->parent = tmp;
                tmp->parent = piv;
                piv->more = tmp;
                piv->less = bt;
                piv->parent = (BTree*) root;
            }
        }
    }
    else if ( bt->parent )
    { /* tocheck: limit recursion? */
        btree_balance( bt->parent );
    }
}

size_t btree_vectorize( const BTree* bt, void** vec )
{
    assert( vec );

    if ( !bt )
        return 0;

    size_t i = 0;
    BTree* it = btree_least( (BTree*) bt );

    for ( ; it; it = btree_next( it ), ++i )
        vec[i] = it->val;

    return i;
}


#ifndef NDEBUG

int btree_balance_factor( const BTree* bt )
{
    const uint i = bt->less ? btree_num_levels( bt->less ) + 1 : 0;
    const uint j = bt->more ? btree_num_levels( bt->more ) + 1 : 0;
    return j - i;
}

Bool btree_is_unbalanced( const BTree* bt )
{
    return abs( btree_balance_factor( bt ) ) > 1 ? True : False;
}

#endif /* !NDEBUG */
