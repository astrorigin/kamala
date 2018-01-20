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

#include "aspect.h"

#include "sqlite.h"

void aspect_init( ZodiaCore* z )
{
    Verbose( z, printf( "----- Loading aspects:\n" ); )

    Debug( Bool b; )
    Aspect* asp;

    sqlite_Stmt* stmt = NULL;
    sqlite_new( z, &stmt, "select * from Aspects" );

    while ( sqlite_step( stmt ) == SQLITE_ROW )
    {
        asp = NULL;
        aspect_new( &asp );
        aspect_set_row( asp, stmt );
        Verbose( z, printf( "-- %s\n", asp->name->ptr ); )

        Debug( b = ) btree_insert( &z->aspectCollection, asp->_idx, asp, NULL );
        assert( b );
        btree_reroot( z->aspectCollection );
    }

    sqlite_delete( &stmt );

    Verbose( z, printf( "----- end loading aspects\n" ); )
}

void aspect_fini( ZodiaCore* z )
{
    btree_traverse( z->aspectCollection, (void(*)(void*))&aspect_delete );
    btree_delete( &z->aspectCollection );
}

void aspect_new( Aspect** asp )
{
    assert( *asp == NULL );
    Trace( printf( "-- New aspect\n" ); )
    *asp = Malloc( sizeof( Aspect ) );

#ifndef NDEBUG
    (*asp)->name =
    (*asp)->comments =
    (*asp)->glyph = NULL;

    (*asp)->defaultOrb = NULL;
#endif /* !NDEBUG */

    str_new( &(*asp)->name, "-?-" );
    str_new( &(*asp)->comments, NULL );
    strcpy( (*asp)->color, "#000000" );
    str_new( &(*asp)->glyph, "glyph.svg" );

    orb_new( &(*asp)->defaultOrb );
}

void aspect_delete( Aspect** asp )
{
    assert( *asp );

    str_delete( &(*asp)->name );
    str_delete( &(*asp)->comments );
    str_delete( &(*asp)->glyph );

    orb_delete( &(*asp)->defaultOrb );

    Trace( printf( "-- Delete aspect\n" ); )
    Free( *asp, sizeof( Aspect ) );
    *asp = NULL;
}

void aspect_set_row( Aspect* asp, const sqlite_Stmt* stmt )
{
    asp->_idx = sqlite_get_int( stmt, 0 );
    str_set( asp->name, sqlite_get_charp( stmt, 1 ), 0 );
    asp->family = sqlite_get_int( stmt, 2 );
    str_set( asp->comments, sqlite_get_charp( stmt, 3 ), 0 );

    asp->isAbs = sqlite_get_int( stmt, 4 );
    asp->signStrict = sqlite_get_int( stmt, 5 );
    asp->angle = sqlite_get_double( stmt, 6 );

    asp->defaultUse = sqlite_get_int( stmt, 7 );
    asp->defaultOrb->applying = sqlite_get_double( stmt, 8 );
    asp->defaultOrb->separating = sqlite_get_double( stmt, 9 );
    asp->defaultOrb->stable = sqlite_get_double( stmt, 10 );

    strcpy( asp->color, sqlite_get_charp( stmt, 11 ) );
    str_set( asp->glyph, sqlite_get_charp( stmt, 12 ), 0 );
    asp->zValue = sqlite_get_int( stmt, 13 );
}

void aspect_copy( Aspect* asp, const Aspect* other )
{
    assert( asp && other );
    assert( asp != other );

    asp->_idx = other->_idx;
    str_copy( asp->name, other->name );
    asp->family = other->family;
    str_copy( asp->comments, other->comments );
    asp->isAbs = other->isAbs;
    asp->signStrict = other->signStrict;
    asp->angle = other->angle;
    asp->defaultUse = other->defaultUse;
    orb_copy( asp->defaultOrb, other->defaultOrb );
    strcpy( asp->color, other->color );
    str_copy( asp->glyph, other->glyph );
    asp->zValue = other->zValue;
}

idx_t aspect_insert( ZodiaCore* z, Aspect* asp )
{
    assert( asp );
    assert( asp->_idx == 0 );

    Verbose( z, printf( "-- Inserting aspect %s\n", asp->name->ptr ); )

    sqlite_Stmt* stmt = NULL;
    sqlite_new( z, &stmt,
        "insert into Aspects ( name, family, comments, "
        "isAbs, signStrict, angle, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, "
        "color, glyph, zValue ) values (?,?,?,?,?,?,?,?,?,?,?,?,?)" );
    sqlite_bind_str( stmt, 0, asp->name );
    sqlite_bind_int( stmt, 1, asp->family );
    sqlite_bind_str( stmt, 2, asp->comments );
    sqlite_bind_int( stmt, 3, asp->isAbs );
    sqlite_bind_int( stmt, 4, asp->signStrict );
    sqlite_bind_double( stmt, 5, asp->angle );
    sqlite_bind_int( stmt, 6, asp->defaultUse );
    sqlite_bind_double( stmt, 7, asp->defaultOrb->applying );
    sqlite_bind_double( stmt, 8, asp->defaultOrb->separating );
    sqlite_bind_double( stmt, 9, asp->defaultOrb->stable );
    sqlite_bind_charp( stmt, 10, asp->color );
    sqlite_bind_str( stmt, 11, asp->glyph );
    sqlite_bind_int( stmt, 12, asp->zValue );
    int i = sqlite_step( stmt );

    if ( i != SQLITE_DONE )
    {
        Verbose( z, printf( "Error duplicate aspect %s\n", asp->name->ptr ); )
        sqlite_delete( &stmt );
        return 0;
    }

    sqlite_Stmt* stmt2 = NULL;
    sqlite_new( z, &stmt2, "select _idx from Aspects where name = ?" );
    sqlite_bind_str( stmt2, 0, asp->name );
    Debug( i = ) sqlite_step( stmt2 );

    Debug
    (
        if ( i != SQLITE_ROW )
            Fatal( printf( "Error unable to get aspect idx for %s\n", asp->name->ptr ); )
    )

    asp->_idx = sqlite_get_int( stmt2, 0 );

    sqlite_delete( &stmt );
    sqlite_delete( &stmt2 );

    Debug( Bool b = ) btree_insert( &z->aspectCollection, asp->_idx, asp, NULL );
    assert( b );
    btree_reroot( z->aspectCollection );

    return asp->_idx;
}

idx_t aspect_update( ZodiaCore* z, const Aspect* asp )
{
    assert( asp );
    assert( asp->_idx != 0 );

    Verbose( z, printf( "-- Updating aspect %s\n", asp->name->ptr ); )

    sqlite_Stmt* stmt = NULL;
    sqlite_new( z, &stmt,
        "update Aspects set name=?, family=?, comments=?, "
        "isAbs=?, signStrict=?, angle=?, dftUse=?, "
        "dftAppOrb=?, dftSepOrb=?, dftStaOrb=?, "
        "color=?, glyph=?, zValue=? where _idx=?" );
    sqlite_bind_str( stmt, 0, asp->name );
    sqlite_bind_int( stmt, 1, asp->family );
    sqlite_bind_str( stmt, 2, asp->comments );
    sqlite_bind_int( stmt, 3, asp->isAbs );
    sqlite_bind_int( stmt, 4, asp->signStrict );
    sqlite_bind_double( stmt, 5, asp->angle );
    sqlite_bind_int( stmt, 6, asp->defaultUse );
    sqlite_bind_double( stmt, 7, asp->defaultOrb->applying );
    sqlite_bind_double( stmt, 8, asp->defaultOrb->separating );
    sqlite_bind_double( stmt, 9, asp->defaultOrb->stable );
    sqlite_bind_charp( stmt, 10, asp->color );
    sqlite_bind_str( stmt, 11, asp->glyph );
    sqlite_bind_int( stmt, 12, asp->zValue );
    sqlite_bind_int( stmt, 13, asp->_idx );
    int i = sqlite_step( stmt );

    if ( i != SQLITE_DONE )
    {
        Verbose( z, printf( "Error duplicate aspect %s\n", asp->name->ptr ); )
        sqlite_delete( &stmt );
        return 0;
    }

    sqlite_delete( &stmt );
    return asp->_idx;
}

idx_t aspect_erase( ZodiaCore* z, Aspect* asp )
{
    assert( asp );
    assert( asp->_idx != 0 );

    Verbose( z, printf( "-- Erasing aspect %s\n", asp->name->ptr ); )

    sqlite_Stmt* stmt = NULL;
    sqlite_new( z, &stmt, "delete from Aspects where _idx = ?" );
    sqlite_bind_int( stmt, 0, asp->_idx );
    Debug( int i = ) sqlite_step( stmt );

    Debug
    (
        if ( i != SQLITE_DONE )
            Fatal( printf( "Error unable to erase aspect with idx %d\n", asp->_idx ); )
    )

    idx_t tmp = asp->_idx;
    btree_reremove( z->aspectCollection, tmp );
    asp->_idx = 0;

    sqlite_delete( &stmt );
    return tmp;
}
