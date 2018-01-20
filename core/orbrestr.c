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

#include "orbrestr.h"

#include "orb.h"

void orbrestr_init( ZodiaCore* z )
{
    Verbose( z, printf( "----- Loading orbs restrs:\n" ); )

    int i;
    Debug( Bool b; )
    OrbModifier* orb;
    OrbRestr* of;
    BTree* bt;

    sqlite_Stmt* stmt = NULL;
    sqlite_new( z, &stmt, "select * from OrbRestrs" );

    sqlite_Stmt* stmt2 = NULL;
    sqlite_new( z, &stmt2, "select * from _orbRestrs where _idx = ?" );

    while ( sqlite_step( stmt ) == SQLITE_ROW )
    {
        bt = NULL;
        of = NULL;
        orbrestr_new( &of );

        of->_idx = sqlite_get_int( stmt, 0 );
        str_set( of->name, sqlite_get_charp( stmt, 1 ), 0 );
        str_set( of->comments, sqlite_get_charp( stmt, 2 ), 0 );

        sqlite_clear( stmt2 );
        sqlite_bind_int( stmt2, 0, of->_idx );

        while ( sqlite_step( stmt2 ) == SQLITE_ROW )
        {
            orb = NULL;
            orbmodifier_new( &orb );

            i = sqlite_get_int( stmt2, 1 );
            orb->applying = sqlite_get_double( stmt2, 2 );
            orb->separating = sqlite_get_double( stmt2, 3 );
            orb->stable = sqlite_get_double( stmt2, 4 );
            btree_insert( &bt, i, (void*) orb, NULL );
            bt = btree_root( bt );
        }
        of->bt = bt;

        Verbose( z, printf( "-- %s\n", of->name->ptr ); )

        Debug( b = ) btree_insert( &z->orbRestrCollection, of->_idx, of, NULL );
        assert( b );
        btree_reroot( z->orbRestrCollection );
    }

    sqlite_delete( &stmt );
    sqlite_delete( &stmt2 );

    Verbose( z, printf( "----- end loading orbs restrs\n" ); )
}

void orbrestr_fini( ZodiaCore* z )
{
    btree_traverse( z->orbRestrCollection, (void(*)(void*))&orbrestr_delete );
    btree_delete( &z->orbRestrCollection );
}

void orbrestr_new( OrbRestr** f )
{
    assert( *f == NULL );
    Trace( printf( "-- New orb restr\n" ); )
    *f = Malloc( sizeof( OrbRestr ) );

    (*f)->_idx = 0;

#ifndef NDEBUG
    (*f)->name =
    (*f)->comments = NULL;
#endif /* !NDEBUG */

    str_new( &(*f)->name, "-?" );
    str_new( &(*f)->comments, NULL );
    (*f)->bt = NULL;
}

void orbrestr_delete( OrbRestr** f )
{
    assert( *f );

    str_delete( &(*f)->name );
    str_delete( &(*f)->comments );

    if ( (*f)->bt )
    {
        btree_traverse( (*f)->bt, (void (*)(void*)) &_orb_t_delete );
        btree_delete( &(*f)->bt );
    }

    Trace( printf( "-- Delete orb restr\n" ); )
    Free( *f, sizeof( OrbRestr ) );
    *f = NULL;
}
