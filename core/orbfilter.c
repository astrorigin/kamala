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

#include "orbfilter.h"

#include "orb.h"

void orbfilter_init( ZodiaCore* z )
{
    Verbose( z, printf( "----- Loading orbs filters:\n" ); )

    int i;
    Debug( Bool b; )
    Orb* orb;
    OrbFilter* of;
    BTree* bt;

    sqlite_Stmt* stmt = NULL;
    sqlite_new( z, &stmt, "select * from OrbFilters" );

    sqlite_Stmt* stmt2 = NULL;
    sqlite_new( z, &stmt2, "select * from _orbFilters where _idx = ?" );

    while ( sqlite_step( stmt ) == SQLITE_ROW )
    {
        bt = NULL;
        of = NULL;
        orbfilter_new( &of );

        of->_idx = sqlite_get_int( stmt, 0 );
        str_set( of->name, sqlite_get_charp( stmt, 1 ), 0 );
        str_set( of->comments, sqlite_get_charp( stmt, 2 ), 0 );

        sqlite_clear( stmt2 );
        sqlite_bind_int( stmt2, 0, of->_idx );

        while ( sqlite_step( stmt2 ) == SQLITE_ROW )
        {
            orb = NULL;
            orb_new( &orb );

            i = sqlite_get_int( stmt2, 1 );
            orb->applying = sqlite_get_double( stmt2, 2 );
            orb->separating = sqlite_get_double( stmt2, 3 );
            orb->stable = sqlite_get_double( stmt2, 4 );
            btree_insert( &bt, i, (void*) orb, NULL );
            btree_reroot( bt );
        }
        of->bt = bt;

        Verbose( z, printf( "-- %s\n", of->name->ptr ); )

        Debug( b = ) btree_insert( &z->orbFilterCollection, of->_idx, of, NULL );
        assert( b );
        btree_reroot( z->orbFilterCollection );
    }

    sqlite_delete( &stmt );
    sqlite_delete( &stmt2 );

    Verbose( z, printf( "----- end loading orbs filters\n" ); )
}

void orbfilter_fini( ZodiaCore* z )
{
    btree_traverse( z->orbFilterCollection, (void(*)(void*))&orbfilter_delete );
    btree_delete( &z->orbFilterCollection );
}

void orbfilter_new( OrbFilter** f )
{
    assert( *f == NULL );
    Trace( printf( "-- New orb filter\n" ); )
    *f = Malloc( sizeof( OrbFilter ) );

    (*f)->_idx = 0;

#ifndef NDEBUG
    (*f)->name =
    (*f)->comments = NULL;
#endif /* !NDEBUG */

    str_new( &(*f)->name, "-?" );
    str_new( &(*f)->comments, NULL );
    (*f)->bt = NULL;
}

void orbfilter_delete( OrbFilter** f )
{
    assert( *f );

    str_delete( &(*f)->name );
    str_delete( &(*f)->comments );

    if ( (*f)->bt )
    {
        btree_traverse( (*f)->bt, (void (*)(void*)) &_orb_t_delete );
        btree_delete( &(*f)->bt );
    }

    Trace( printf( "-- Delete orb filter\n" ); )
    Free( *f, sizeof( OrbFilter ) );
    *f = NULL;
}
