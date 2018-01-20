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

#include "planet.h"

void planet_init( ZodiaCore* z )
{
    Verbose( z, printf( "----- Loading planets:\n" ); )

    Debug( Bool b; )
    Planet* pl;

    sqlite_Stmt* stmt = NULL;
    sqlite_new( z, &stmt, "select * from Planets" );

    while ( sqlite_step( stmt ) == SQLITE_ROW )
    {
        pl = NULL;
        planet_new( &pl );
        planet_set_row( pl, stmt );
        Verbose( z, printf( "-- %s\n", pl->name->ptr ); )

        Debug( b = ) btree_insert( &z->planetCollection, pl->_idx, pl, NULL );
        assert( b );
        btree_reroot( z->planetCollection );
    }

    sqlite_delete( &stmt );

    Verbose( z, printf( "----- end loading planets\n" ); )
}

void planet_fini( ZodiaCore* z )
{
    btree_traverse( z->planetCollection, (void(*)(void*))&planet_delete );
    btree_delete( &z->planetCollection );
}

void planet_new( Planet** pl )
{
    assert( *pl == NULL );
    Trace( printf( "-- New planet\n" ); )
    *pl = Malloc( sizeof( Planet ) );

    (*pl)->_idx =
    (*pl)->num =
    (*pl)->family =
    (*pl)->zValue = 0;

    (*pl)->defaultUse =
    (*pl)->defaultAspect = False;

#ifndef NDEBUG
    (*pl)->name =
    (*pl)->comments =
    (*pl)->glyph = NULL;

    (*pl)->orbModifier = NULL;
#endif /* !NDEBUG */

    str_new( &(*pl)->name, "-?-" );
    str_new( &(*pl)->comments, NULL );
    str_new( &(*pl)->glyph, "glyph.svg" );

    orbmodifier_new( &(*pl)->orbModifier );

    (*pl)->color[0] = '\0';
}

void planet_delete( Planet** pl )
{
    assert( *pl );

    str_delete( &(*pl)->name );
    str_delete( &(*pl)->comments );
    str_delete( &(*pl)->glyph );
    orbmodifier_delete( &(*pl)->orbModifier );

    Trace( printf( "-- Delete planet\n" ); )
    Free( *pl, sizeof( Planet ) );
    *pl = NULL;
}

void planet_copy( Planet* pl, const Planet* other )
{
    assert( pl && other );
    assert( pl != other );

    pl->num = other->num;
    str_copy( pl->name, other->name );
    pl->family = other->family;
    str_copy( pl->comments, other->comments );
    pl->defaultUse = other->defaultUse;
    pl->defaultAspect = other->defaultAspect;
    orbmodifier_copy( pl->orbModifier, other->orbModifier );
    strcpy( pl->color, other->color );
    str_copy( pl->glyph, other->glyph );
    pl->zValue = other->zValue;
}

void planet_set_row( Planet* pl, const sqlite_Stmt* stmt )
{
    assert( pl && stmt );

    pl->_idx = sqlite_get_int( stmt, 0 );
    pl->num = sqlite_get_int( stmt, 1 );
    str_set( pl->name, sqlite_get_charp( stmt, 2 ), 0 );
    pl->family = sqlite_get_int( stmt, 3 );
    str_set( pl->comments, sqlite_get_charp( stmt, 4 ), 0 );

    pl->defaultUse = sqlite_get_int( stmt, 5 );
    pl->defaultAspect = sqlite_get_int( stmt, 6 );

    pl->orbModifier->applying = sqlite_get_double( stmt, 7 );
    pl->orbModifier->separating = sqlite_get_double( stmt, 8 );
    pl->orbModifier->stable = sqlite_get_double( stmt, 9 );

    strcpy( pl->color, sqlite_get_charp( stmt, 10 ) );
    str_set( pl->glyph, sqlite_get_charp( stmt, 11 ), 0 );
    pl->zValue = sqlite_get_int( stmt, 12 );
}

idx_t planet_insert( ZodiaCore* z, Planet* pl )
{
    assert( pl );
    assert( pl->_idx == 0 );

    Verbose( z, printf( "-- Inserting planet %s\n", pl->name->ptr ); )

    sqlite_Stmt* stmt = NULL;
    sqlite_new( z, &stmt,
        "insert into Planets ( num, name, family, comments, "
        "dftUse, dftAspect, dftAppOrbMod, dftSepOrbMod, dftStaOrbMod, "
        "color, glyph, zValue ) values ( ?,?,?,?,?,?,?,?,?,?,?,? )" );
    sqlite_bind_int( stmt, 0, pl->num );
    sqlite_bind_str( stmt, 1, pl->name );
    sqlite_bind_int( stmt, 2, pl->family );
    sqlite_bind_str( stmt, 3, pl->comments );
    sqlite_bind_int( stmt, 4, pl->defaultUse );
    sqlite_bind_int( stmt, 5, pl->defaultAspect );
    sqlite_bind_double( stmt, 6, pl->orbModifier->applying );
    sqlite_bind_double( stmt, 7, pl->orbModifier->separating );
    sqlite_bind_double( stmt, 8, pl->orbModifier->stable );
    sqlite_bind_charp( stmt, 9, pl->color );
    sqlite_bind_str( stmt, 10, pl->glyph );
    sqlite_bind_int( stmt, 11, pl->zValue );
    int i = sqlite_step( stmt );

    if ( i != SQLITE_DONE )
    {
        Verbose( z, printf( "Error duplicate planet %s\n", pl->name->ptr ); )
        sqlite_delete( &stmt );
        return 0;
    }

    sqlite_Stmt* stmt2 = NULL;
    sqlite_new( z, &stmt2, "select _idx from Planets where name = ?" );
    sqlite_bind_str( stmt2, 0, pl->name );
    Debug( i = ) sqlite_step( stmt2 );

    Debug
    (
        if ( i != SQLITE_ROW )
            Fatal( printf( "Error unable to get planet idx for %s\n", pl->name->ptr ); )
    )

    pl->_idx = sqlite_get_int( stmt2, 0 );

    Debug( Bool b = ) btree_insert( &z->planetCollection, pl->_idx, pl, NULL );
    assert( b );
    btree_reroot( z->planetCollection );

    sqlite_delete( &stmt );
    sqlite_delete( &stmt2 );
    return pl->_idx;
}

idx_t planet_update( ZodiaCore* z, const Planet* pl )
{
    assert( pl );
    assert( pl->_idx != 0 );

    Verbose( z, printf( "-- Updating planet %s\n", pl->name->ptr ); )

    sqlite_Stmt* stmt = NULL;
    sqlite_new( z, &stmt,
        "update Planets set num=?, name=?, family=?, comments=?, "
        "dftUse=?, dftAspect=?, dftAppOrbMod=?, dftSepOrbMod=?, dftStaOrbMod=?, "
        "color=?, glyph=?, zValue=? where _idx=?" );
    sqlite_bind_int( stmt, 0, pl->num );
    sqlite_bind_str( stmt, 1, pl->name );
    sqlite_bind_int( stmt, 2, pl->family );
    sqlite_bind_str( stmt, 3, pl->comments );
    sqlite_bind_int( stmt, 4, pl->defaultUse );
    sqlite_bind_int( stmt, 5, pl->defaultAspect );
    sqlite_bind_double( stmt, 6, pl->orbModifier->applying );
    sqlite_bind_double( stmt, 7, pl->orbModifier->separating );
    sqlite_bind_double( stmt, 8, pl->orbModifier->stable );
    sqlite_bind_charp( stmt, 9, pl->color );
    sqlite_bind_str( stmt, 10, pl->glyph );
    sqlite_bind_int( stmt, 11, pl->zValue );
    sqlite_bind_int( stmt, 12, pl->_idx );
    int i = sqlite_step( stmt );

    if ( i != SQLITE_DONE )
    {
        Verbose( z, printf( "Error duplicate planet %s\n", pl->name->ptr ); )
        sqlite_delete( &stmt );
        return 0;
    }

    sqlite_delete( &stmt );
    return pl->_idx;
}

idx_t planet_erase( ZodiaCore* z, Planet* pl )
{
    assert( pl );
    assert( pl->_idx != 0 );

    Verbose( z, printf( "-- Erasing planet %s\n", pl->name->ptr ); )

    sqlite_Stmt* stmt = NULL;
    sqlite_new( z, &stmt, "delete from Planets where _idx = ?" );
    sqlite_bind_int( stmt, 0, pl->_idx );
    Debug( int i = ) sqlite_step( stmt );

    Debug
    (
        if ( i != SQLITE_DONE )
            Fatal( printf( "Error unable to erase planet with idx %d\n", pl->_idx ); )
    )

    idx_t tmp = pl->_idx;
    btree_reremove( z->planetCollection, tmp );
    pl->_idx = 0;

    sqlite_delete( &stmt );
    return tmp;
}

int planet_calc( const Planet* pl, const double jd, const int flag, double* res )
{
    int i;
    char err[256];

    if ( pl->family == MainFamily
        || pl->family == FictitiousFamily
        || pl->family == AsteroidsFamily )
    {
        i = swe_calc_ut( jd, pl->num, flag, res, err );
    }
    else if ( pl->family == StarsFamily )
    {
        char star[64];
        strcpy( star, pl->name->ptr );
        i = swe_fixstar_ut( star, jd, flag, res, err );
    }
    else
    {
        printf( "planet_calc TODO\n" );/*TODO*/
        return -1;
    }

#ifndef NDEBUG
    if ( i == flag )
        return i;

    else if ( flag >= 0 )
    { /* usually not critical */
        printf( "Planet calc warning %s\nJD=%f flag=%d ret=%d\n%s",
            pl->name->ptr, jd, flag, i, err );
        return i;
    }
    else
    { /* critical */
        Fatal
        (
            printf( "Planet calc error %s\nJD=%f flag=%d ret=%d\n%s",
                pl->name->ptr, jd, flag, i, err );
        )
    }
#else
    return i;
#endif /* !NDEBUG */
}
