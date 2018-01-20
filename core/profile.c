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

#include "profile.h"

void profile_init( ZodiaCore* z )
{
    assert( z->planetFilterCollection );
    assert( z->aspectFilterCollection );
    assert( z->orbFilterCollection );
    assert( z->aspectRestrCollection );
    assert( z->orbRestrCollection );

    Verbose( z, printf( "----- Loading profiles:\n" ); )

    Debug( Bool b; )
    Profile* p;

    sqlite_Stmt* stmt = NULL;
    sqlite_new( z, &stmt, "select * from Profiles" );

    while ( sqlite_step( stmt ) == SQLITE_ROW )
    {
        p = NULL;
        profile_new( &p );
        profile_set_row( z, p, stmt );
        Verbose( z, printf( "-- %s\n", p->name->ptr ); )

        Debug( b = ) btree_insert( &z->profileCollection, p->_idx, p, NULL );
        assert( b );
        btree_reroot( z->profileCollection );
    }

    sqlite_delete( &stmt );

    Verbose( z, printf( "----- end loading profiles\n" ); )
}

void profile_fini( ZodiaCore* z )
{
    btree_traverse( z->profileCollection, (void(*)(void*))&profile_delete );
    btree_delete( &z->profileCollection );
}

void profile_new( Profile** p )
{
    assert( *p == NULL );
    Trace( printf( "-- New profile\n" ); )
    *p = Malloc( sizeof( Profile ) );

    (*p)->_idx = 0;

#ifndef NDEBUG
    (*p)->name =
    (*p)->comments = NULL;
#endif /* NDEBUG */

    str_new( &(*p)->name, "-?-" );
    str_new( &(*p)->comments, NULL );

    (*p)->calcMidp = (*p)->drawMidp = False;

    (*p)->planetFilter = NULL;
    (*p)->aspectFilter = NULL;
    (*p)->orbFilter = NULL;
    (*p)->aspectRestr = NULL;
    (*p)->orbRestr = NULL;
}

void profile_delete( Profile** p )
{
    assert( *p );

    str_delete( &(*p)->name );
    str_delete( &(*p)->comments );

    Trace( printf( "-- Delete profile\n" ); )
    Free( *p, sizeof ( Profile ) );
    *p = NULL;
}

void profile_set_row( ZodiaCore* z, Profile* p, const sqlite_Stmt* stmt )
{
    p->_idx = sqlite_get_int( stmt, 0 );
    str_set( p->name, sqlite_get_charp( stmt, 1 ), 0 );
    str_set( p->comments, sqlite_get_charp( stmt, 2 ), 0 );

    p->calcMidp = sqlite_get_int( stmt, 3 );
    p->drawMidp = sqlite_get_int( stmt, 4 );

    p->planetFilter = btree_value( z->planetFilterCollection, sqlite_get_int( stmt, 5 ) );
    p->aspectFilter = btree_value( z->aspectFilterCollection, sqlite_get_int( stmt, 6 ) );
    p->orbFilter = btree_value( z->orbFilterCollection, sqlite_get_int( stmt, 7 ) );
    p->aspectRestr = btree_value( z->aspectRestrCollection, sqlite_get_int( stmt, 8 ) );
    p->orbRestr = btree_value( z->orbRestrCollection, sqlite_get_int( stmt, 9 ) );

    assert( p->planetFilter );
    assert( p->aspectFilter );
    assert( p->orbFilter );
    assert( p->aspectRestr );
    assert( p->orbRestr );
}

void profile_copy( Profile* p, const Profile* other )
{
    assert( p && other );
    assert( p != other );

    p->_idx = other->_idx;
    str_copy( p->name, other->name );
    str_copy( p->comments, other->comments );
    p->calcMidp = other->calcMidp;
    p->drawMidp = other->drawMidp;
    p->planetFilter = other->planetFilter;
    p->aspectFilter = other->aspectFilter;
    p->orbFilter = other->orbFilter;
    p->aspectRestr = other->aspectRestr;
    p->orbRestr = other->orbRestr;
}

idx_t profile_insert( ZodiaCore* z, Profile* p )
{
    assert( p );
    assert( p->_idx == 0 );

    Verbose( z, printf( "-- Inserting profile %s\n", p->name->ptr ); )

    sqlite_Stmt* stmt = NULL;
    sqlite_new( z, &stmt,
        "insert into Profiles ( name, comments, calcMidp, drawMidp, "
        "plFiltIdx, aspFiltIdx, orbFiltIdx, aspRestrIdx, orbRestrIdx "
        "values ( ?,?,?,?,?,?,?,?,? )" );
    sqlite_bind_str( stmt, 0, p->name );
    sqlite_bind_str( stmt, 1, p->comments );
    sqlite_bind_int( stmt, 2, p->calcMidp );
    sqlite_bind_int( stmt, 3, p->drawMidp );
    sqlite_bind_int( stmt, 4, p->planetFilter->_idx );
    sqlite_bind_int( stmt, 5, p->aspectFilter->_idx );
    sqlite_bind_int( stmt, 6, p->orbFilter->_idx );
    sqlite_bind_int( stmt, 7, p->aspectRestr->_idx );
    sqlite_bind_int( stmt, 8, p->orbRestr->_idx );
    int i = sqlite_step( stmt );

    if ( i != SQLITE_DONE )
    {
        Verbose( z, printf( "Error duplicate profile %s\n", p->name->ptr ); )
        sqlite_delete( &stmt );
        return 0;
    }

    sqlite_Stmt* stmt2 = NULL;
    sqlite_new( z, &stmt2, "select _idx from Profiles where name = ?" );
    sqlite_bind_str( stmt2, 0, p->name );
    Debug( i = ) sqlite_step( stmt2 );

    Debug
    (
        if ( i != SQLITE_ROW )
            Fatal( printf( "Error unable to get profile idx for %s\n", p->name->ptr ); )
    )

    p->_idx = sqlite_get_int( stmt2, 0 );

    sqlite_delete( &stmt );
    sqlite_delete( &stmt2 );

    Debug( Bool b = ) btree_insert( &z->profileCollection, p->_idx, p, NULL );
    assert( b );
    btree_reroot( z->profileCollection );

    return p->_idx;
}

idx_t profile_update( ZodiaCore* z, const Profile* p )
{
    assert( p );
    assert( p->_idx != 0 );

    Verbose( z, printf( "-- Updating profile %s\n", p->name->ptr ); )

    sqlite_Stmt* stmt = NULL;
    sqlite_new( z, &stmt,
        "update Profiles set name=?, comments=?, calcMidp=?, drawMidp=?, "
        "plFiltIdx=?, aspFiltIdx=?, orbFiltIdx=?, aspRestrIdx=?, orbRestrIdx=? "
        "where _idx=?" );
    sqlite_bind_str( stmt, 0, p->name );
    sqlite_bind_str( stmt, 1, p->comments );
    sqlite_bind_int( stmt, 2, p->calcMidp );
    sqlite_bind_int( stmt, 3, p->drawMidp );
    sqlite_bind_int( stmt, 4, p->planetFilter->_idx );
    sqlite_bind_int( stmt, 5, p->aspectFilter->_idx );
    sqlite_bind_int( stmt, 6, p->orbFilter->_idx );
    sqlite_bind_int( stmt, 7, p->aspectRestr->_idx );
    sqlite_bind_int( stmt, 8, p->orbRestr->_idx );
    sqlite_bind_int( stmt, 9, p->_idx );
    int i = sqlite_step( stmt );

    if ( i != SQLITE_DONE )
    {
        Verbose( z, printf( "Error duplicate profile %s\n", p->name->ptr ); )
        sqlite_delete( &stmt );
        return 0;
    }

    sqlite_delete( &stmt );
    return p->_idx;
}

idx_t profile_erase( ZodiaCore* z, Profile* p )
{
    assert( p );
    assert( p->_idx != 0 );

    Verbose( z, printf( "-- Erasing profile %s\n", p->name->ptr ); )

    sqlite_Stmt* stmt = NULL;
    sqlite_new( z, &stmt, "delete from Profiles where _idx = ?" );
    sqlite_bind_int( stmt, 0, p->_idx );
    Debug( int i = ) sqlite_step( stmt );

    Debug
    (
        if ( i != SQLITE_DONE )
            Fatal( printf( "Error unable to erase profile with idx %d\n", p->_idx ); )
    )

    idx_t tmp = p->_idx;
    btree_reremove( z->profileCollection, tmp );
    p->_idx = 0;

    sqlite_delete( &stmt );
    return tmp;
}

Profile* profile_whose_name( const ZodiaCore* z, const char* s )
{
    BTree* it = btree_least( z->profileCollection );
    for ( ; it; it = btree_next( it ) )
    {
        if ( strequ( (char*) s, ((Profile*)it->val)->name->ptr ) )
            return (Profile*) it->val;
    }
    return NULL;
}
