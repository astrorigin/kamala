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

#include "context.h"

#include <swephexp.h>

void context_init( ZodiaCore* z )
{
    Verbose( z, printf( "-- Loading contexts:\n" ); )

    Debug( Bool b; )
    Context* c;

    sqlite_Stmt* stmt = NULL;
    sqlite_new( z, &stmt, "select * from Contexts" );

    while ( sqlite_step( stmt ) == SQLITE_ROW )
    {
        c = NULL;
        context_new( &c );
        context_set_row( c, stmt );
        Verbose( z, printf( "-- %s\n", c->name->ptr ); )

        Debug( b = ) btree_insert( &z->contextCollection, c->_idx, c, NULL );
        assert( b );
        btree_reroot( z->contextCollection );
    }

    sqlite_delete( &stmt );

    Verbose( z, printf( "----- end loading contexts\n" ); )
}

void context_fini( ZodiaCore* z )
{
    btree_traverse( z->contextCollection, (void(*)(void*))&context_delete );
    btree_delete( &z->contextCollection );
}

void context_new( Context** c )
{
    assert( *c == NULL );
    Trace( printf( "-- New context\n" ); )
    *c = Malloc( sizeof( Context ) );

#ifndef NDEBUG
    (*c)->name = (*c)->comments = NULL;
#endif /* !NDEBUG */

    str_new( &(*c)->name, "-?-" );
    str_new( &(*c)->comments, NULL );

    (*c)->_idx = 0;
    (*c)->xCentric = GeoCentric;
    (*c)->hSys = PlacidusHouseSystem;
    (*c)->sidMode = NoSiderealMode;
    (*c)->sidT0 =
    (*c)->sidAyanT0 = 0;
    (*c)->truePos = False;
}

void context_delete( Context** c )
{
    assert( *c );

    str_delete( &(*c)->name );
    str_delete( &(*c)->comments );

    Trace( printf( "-- Delete context\n" ); )
    Free( *c, sizeof( Context ) );
    *c = NULL;
}

void context_set_row( Context* c, const sqlite_Stmt* stmt )
{
    assert( c && stmt );

    c->_idx = sqlite_get_int( stmt, 0 );
    str_set( c->name, sqlite_get_charp( stmt, 1 ), 0 );
    str_set( c->comments, sqlite_get_charp( stmt, 2 ), 0 );
    c->xCentric = sqlite_get_int( stmt, 3 );
    c->hSys = *sqlite_get_charp( stmt, 4 );
    c->sidMode = sqlite_get_int( stmt, 5 );
    c->sidT0 = sqlite_get_double( stmt, 6 );
    c->sidAyanT0 = sqlite_get_double( stmt, 7 );
    c->truePos = sqlite_get_int( stmt, 8 );
}

void context_copy( Context* c, const Context* other )
{
    assert( c && other );
    assert( c != other );

    c->_idx = other->_idx;
    str_copy( c->name, other->name );
    str_copy( c->comments, other->comments );
    c->xCentric = other->xCentric;
    c->hSys = other->hSys;
    c->sidMode = other->sidMode;
    c->sidT0 = other->sidT0;
    c->sidAyanT0 = other->sidAyanT0;
    c->truePos = other->truePos;
}

idx_t context_insert( ZodiaCore* z, Context* c )
{
    assert( c );
    assert( c->_idx == 0 );

    Verbose( z, printf( "-- Inserting context %s\n", c->name->ptr ); )

    sqlite_Stmt* stmt = NULL;
    sqlite_new( z, &stmt,
        "insert into Contexts ( name, comments, xCentric, hSys, sidMode, sidT0, "
        "sidAyanT0, truePos ) values ( ?,?,?,?,?,?,?,? )" );
    sqlite_bind_str( stmt, 0, c->name );
    sqlite_bind_str( stmt, 1, c->comments );
    sqlite_bind_int( stmt, 2, c->xCentric );
    sqlite_bind_int( stmt, 3, c->hSys );
    sqlite_bind_int( stmt, 4, c->sidMode );
    sqlite_bind_double( stmt, 5, c->sidT0 );
    sqlite_bind_double( stmt, 6, c->sidAyanT0 );
    sqlite_bind_int( stmt, 7, c->truePos );
    int i = sqlite_step( stmt );

    if ( i != SQLITE_DONE )
    {
        Verbose( z, printf( "Error duplicate context %s\n", c->name->ptr ); )
        sqlite_delete( &stmt );
        return 0;
    }

    sqlite_Stmt* stmt2 = NULL;
    sqlite_new( z, &stmt, "select _idx from Contexts where name = ?" );
    sqlite_bind_str( stmt, 0, c->name );
    Debug( i = ) sqlite_step( stmt );

    Debug
    (
        if ( i != SQLITE_ROW )
            Fatal( printf( "Error unable to get context idx for %s\n", c->name->ptr ); )
    )

    c->_idx = sqlite_get_int( stmt2, 0 );

    sqlite_delete( &stmt );
    sqlite_delete( &stmt2 );

    Debug( Bool b = ) btree_insert( &z->contextCollection, c->_idx, c, NULL );
    assert( b );
    btree_reroot( z->contextCollection );

    return c->_idx;
}

idx_t context_update( ZodiaCore* z, Context* c )
{
    assert( c );
    assert( c->_idx != 0 );

    Verbose( z, printf( "-- Updating context %s\n", c->name->ptr ); )

    sqlite_Stmt* stmt = NULL;
    sqlite_new( z, &stmt,
        "update Contexts set name=?, comments=?, xCentric=?, hSys=?, sidMode=? "
        "sidT0=?, sidAyanT0=?, truePos=? where _idx=?" );
    sqlite_bind_str( stmt, 0, c->name );
    sqlite_bind_str( stmt, 1, c->comments );
    sqlite_bind_int( stmt, 2, c->xCentric );
    sqlite_bind_int( stmt, 3, c->hSys );
    sqlite_bind_int( stmt, 4, c->sidMode );
    sqlite_bind_double( stmt, 5, c->sidT0 );
    sqlite_bind_double( stmt, 6, c->sidAyanT0 );
    sqlite_bind_int( stmt, 7, c->truePos );
    sqlite_bind_int( stmt, 8, c->_idx );
    int i = sqlite_step( stmt );

    if ( i != SQLITE_DONE )
    {
        Verbose( z, printf( "Error duplicate context %s\n", c->name->ptr ); )
        sqlite_delete( &stmt );
        return 0;
    }

    sqlite_delete( &stmt );
    return c->_idx;
}

idx_t context_erase( ZodiaCore* z, Context* c )
{
    assert( c );
    assert( c->_idx != 0 );

    Verbose( z, printf( "-- Erasing context %s\n", c->name->ptr ); )

    sqlite_Stmt* stmt = NULL;
    sqlite_new( z, &stmt, "delete from Contexts where _idx = ?" );
    sqlite_bind_int( stmt, 0, c->_idx );
    Debug( int i = ) sqlite_step( stmt );

    Debug
    (
        if ( i != SQLITE_DONE )
            Fatal( printf( "Error unable to erase context with idx %d\n", c->_idx ); )
    )

    idx_t tmp = c->_idx;
    btree_reremove( z->contextCollection, tmp );
    c->_idx = 0;

    sqlite_delete( &stmt );
    return tmp;
}

int context_swe_flags( const Context* c )
{
    int flag = 0;
    /* speed */
    flag |= SEFLG_SPEED;
    /* ephemeris type */
    flag |= SEFLG_SWIEPH;
    /* sidereal mode */
    if ( c->sidMode != NoSiderealMode )
        flag |= SEFLG_SIDEREAL;
    /* true positions */
    if ( c->truePos )
        flag |= SEFLG_TRUEPOS;
    /* xcentric */
    if ( c->xCentric == TopoCentric )
        flag |= SEFLG_TOPOCTR;
    else if ( c->xCentric == HelioCentric )
        flag |= SEFLG_HELCTR;
    else if ( c->xCentric == BaryCentric )
        flag |= SEFLG_BARYCTR;
    return flag;
}

Context* context_whose_name( const ZodiaCore* z, const char* s )
{
    BTree* it = btree_least( z->contextCollection );
    for ( ; it; it = btree_next( it ) )
    {
        if ( strequ( (char*) s, ((Context*)it->val)->name->ptr ) )
            return (Context*) it->val;
    }
    return NULL;
}
