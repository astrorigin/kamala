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

#include "aspectrestr.h"

void aspectrestr_init( ZodiaCore* z )
{
    Verbose( z, printf( "----- Loading aspects restrs:\n" ); )

    int i;
    Bool b;
    AspectRestr* ar;
    BTree* bt;

    sqlite_Stmt* stmt = NULL;
    sqlite_new( z, &stmt, "select * from AspectRestrs" );

    sqlite_Stmt* stmt2 = NULL;
    sqlite_new( z, &stmt2, "select * from _aspectRestrs where _idx = ?" );

    while ( sqlite_step( stmt ) == SQLITE_ROW )
    {
        bt = NULL;
        ar = NULL;
        aspectrestr_new( &ar );

        ar->_idx = sqlite_get_int( stmt, 0 );
        str_set( ar->name, sqlite_get_charp( stmt, 1 ), 0 );
        str_set( ar->comments, sqlite_get_charp( stmt, 2 ), 0 );

        sqlite_clear( stmt2 );
        sqlite_bind_int( stmt2, 0, ar->_idx );

        while ( sqlite_step( stmt2 ) == SQLITE_ROW )
        {
            i = sqlite_get_int( stmt2, 1 );
            b = sqlite_get_int( stmt2, 2 );
            btree_insert( &bt, i, (void*) b, NULL );
            btree_reroot( bt );
        }
        ar->bt = bt;

        Verbose( z, printf( "-- %s\n", ar->name->ptr ); )

        Debug( b = ) btree_insert( &z->aspectRestrCollection, ar->_idx, ar, NULL );
        assert( b );
        btree_reroot( z->aspectRestrCollection );
    }

    sqlite_delete( &stmt );
    sqlite_delete( &stmt2 );

    Verbose( z, printf( "----- end loading aspects restrs\n" ); )
}

void aspectrestr_fini( ZodiaCore* z )
{
    btree_traverse( z->aspectRestrCollection, (void(*)(void*))&aspectrestr_delete );
    btree_delete( &z->aspectRestrCollection );
}

void aspectrestr_new( AspectRestr** f )
{
    assert( *f == NULL );
    Trace( printf( "-- New aspect restr\n" ); )
    *f = Malloc( sizeof( AspectRestr ) );

    (*f)->_idx = 0;

#ifndef NDEBUG
    (*f)->name = NULL;
    (*f)->comments = NULL;
#endif /* !NDEBUG */

    str_new( &(*f)->name, "-?" );
    str_new( &(*f)->comments, NULL );
    (*f)->bt = NULL;
}

void aspectrestr_delete( AspectRestr** f )
{
    assert( *f );

    str_delete( &(*f)->name );
    str_delete( &(*f)->comments );

    btree_delete( &(*f)->bt );

    Trace( printf( "-- Delete aspect restr\n" ); )
    Free( *f, sizeof( AspectRestr ) );
    *f = NULL;
}
