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

#include "horoscope.h"

void horoscope_init( ZodiaCore* z )
{
    Verbose( z, printf( "----- Loading horoscopes:\n" ); )

    Debug( Bool b; )
    Horoscope* h;

    sqlite_Stmt* stmt = NULL;
    sqlite_new( z, &stmt, "select * from Horoscopes" );

    size_t cnt = 0;

    for ( ; sqlite_step( stmt ) == SQLITE_ROW; ++cnt )
    {
        h = NULL;
        horoscope_new( z, &h );
        horoscope_set_row( h, stmt );
        Verbose( z, printf( "-- %s\n", h->name->ptr ); )

        Debug( b = ) btree_insert( &z->horoscopeCollection, h->_idx, h, NULL );
        assert( b );
        btree_reroot( z->horoscopeCollection );
    }

    sqlite_delete( &stmt );

    assert( !z->sortedHoroscopes );
    vector_new( &z->sortedHoroscopes, cnt );
    btree_vectorize( z->horoscopeCollection, z->sortedHoroscopes->ptr );
    vector_sort( z->sortedHoroscopes,
        (int (*)(const void*, const void*))&horoscope_alphasort );

    Verbose( z, printf( "----- end loading horoscopes (total: %d)\n", cnt ); )
}

void horoscope_fini( ZodiaCore* z )
{
    if ( z->horoscopeCollection )
    {
        vector_traverse( z->sortedHoroscopes, (void(*)(void*))&horoscope_delete );
        btree_delete( &z->horoscopeCollection );
    }
    vector_delete( &z->sortedHoroscopes );
}

void horoscope_register( ZodiaCore* z, const Horoscope* h )
{
    assert( h && h->_idx );
    Debug( Bool b = ) btree_insert( &z->horoscopeCollection, h->_idx, h, NULL );
    assert( b );
    btree_reroot( z->horoscopeCollection );

    vector_append( z->sortedHoroscopes, (void*) h );
    vector_sort( z->sortedHoroscopes,
        (int (*)(const void*, const void*))&horoscope_alphasort );
}

void horoscope_unregister( ZodiaCore* z, const Horoscope* h )
{
    assert( h && h->_idx );
    btree_reremove( z->horoscopeCollection, h->_idx );
    vector_remove( z->sortedHoroscopes, vector_index( z->sortedHoroscopes, h ) );
}

void horoscope_new( const ZodiaCore* z, Horoscope** h )
{
    assert( *h == NULL );
    Trace( printf( "-- New horoscope\n" ); )
    *h = Malloc( sizeof( Horoscope ) );

    (*h)->_idx = 0;
#ifndef NDEBUG
    (*h)->name =
    (*h)->comments =
    (*h)->location =
    (*h)->country = NULL;
#endif /* !NDEBUG */

    str_new( &(*h)->name, "-?-" );
    str_new( &(*h)->comments, NULL );
    str_new( &(*h)->location, z->prefs->location->ptr );
    str_new( &(*h)->country, z->prefs->country->ptr );

    Debug( (*h)->datetime = NULL; )
    datetime_new( &(*h)->datetime );

    (*h)->latitude = z->prefs->latitude;
    (*h)->longitude = z->prefs->longitude;
    (*h)->altitude = z->prefs->altitude;

#ifdef KAMALA
    (*h)->changed = False;
#endif /* KAMALA */
}

void horoscope_delete( Horoscope** h )
{
    assert( *h );

    str_delete( &(*h)->name );
    str_delete( &(*h)->comments );
    str_delete( &(*h)->location );
    str_delete( &(*h)->country );

    datetime_delete( &(*h)->datetime );

    Trace( printf( "-- Delete horoscope\n" ); )
    Free( *h, sizeof( Horoscope ) );
    *h = NULL;
}

void horoscope_copy( Horoscope* h, const Horoscope* other )
{
    assert( h && other );
    if ( h == other ) return;

    h->_idx = other->_idx;
    str_copy( h->name, other->name );
    str_copy( h->comments, other->comments );
    datetime_copy( h->datetime, other->datetime );
    str_copy( h->location, other->location );
    str_copy( h->country, other->country );
    h->latitude = other->latitude;
    h->longitude = other->longitude;
    h->altitude = other->altitude;
#ifdef KAMALA
    h->changed = other->changed;
#endif /* KAMALA */
}

Bool horoscope_equals( const Horoscope* h, const Horoscope* other )
{
    assert( h && other );
    if ( h == other ) return True;

    if ( h->_idx == other->_idx
        && str_equ( h->name, other->name )
        && str_equ( h->comments, other->comments )
        && str_equ( h->location, other->location )
        && str_equ( h->country, other->country )
        && h->latitude == other->latitude
        && h->longitude == other->longitude
        && h->altitude == other->altitude
        && datetime_equals( h->datetime, other->datetime ) )
        return True;

    return False;
}

void horoscope_set_row( Horoscope* h, const sqlite_Stmt* stmt )
{
    assert( h && stmt );

    h->_idx = sqlite_get_int( stmt, 0 );
    str_set( h->name, sqlite_get_charp( stmt, 1 ), 0 );
    str_set( h->comments, sqlite_get_charp( stmt, 2 ), 0 );

    datetime_set( h->datetime, sqlite_get_charp( stmt, 3 ),
        sqlite_get_charp( stmt, 4 ), sqlite_get_int( stmt, 5 ),
        sqlite_get_int( stmt, 6 ) );

    str_set( h->location, sqlite_get_charp( stmt, 7 ), 0 );
    str_set( h->country, sqlite_get_charp( stmt, 8 ), 0 );

    h->latitude = sqlite_get_double( stmt, 9 );
    h->longitude = sqlite_get_double( stmt, 10 );
    h->altitude = sqlite_get_int( stmt, 11 );
}

idx_t horoscope_insert( ZodiaCore* z, Horoscope* h )
{
    assert( h );
    assert( h->_idx == 0 );

    char dt[22];
    structtm_to_string( &h->datetime->dt, dt );

    sqlite_Stmt* stmt = NULL;
    sqlite_new( z, &stmt,
        "insert into Horoscopes ( name, comments, datetime, timezone, "
        "location, country, latitude, longitude, altitude ) "
        "values ( ?,?,?,?,?,?,?,?,? )" );
    sqlite_bind_str( stmt, 0, h->name );
    sqlite_bind_str( stmt, 1, h->comments );
    sqlite_bind_charp( stmt, 2, dt );
    sqlite_bind_charp( stmt, 3, h->datetime->tzfile );
    sqlite_bind_str( stmt, 4, h->location );
    sqlite_bind_str( stmt, 5, h->country );
    sqlite_bind_double( stmt, 6, h->latitude );
    sqlite_bind_double( stmt, 7, h->longitude );
    sqlite_bind_int( stmt, 8, h->altitude );
    int i = sqlite_step( stmt );

    if ( i != SQLITE_DONE )
    {
        Verbose( z, printf( "Error duplicate horoscope %s\n", h->name->ptr ); )
        sqlite_delete( &stmt );
        return 0;
    }

    sqlite_Stmt* stmt2 = NULL;
    sqlite_new( z, &stmt2, "select _idx from Horoscopes where name = ?" );
    sqlite_bind_str( stmt2, 0, h->name );
    Debug( i = ) sqlite_step( stmt2 );

    Debug
    (
        if ( i != SQLITE_ROW )
            Fatal( printf( "Error unable to get horoscope idx for %s\n", h->name->ptr ); )
    )

    h->_idx = sqlite_get_int( stmt2, 0 );
#ifdef KAMALA
    h->changed = False;
#endif /* KAMALA */

    Horoscope* h2 = NULL;
    horoscope_new( z, &h2 );
    horoscope_copy( h2, h );
    horoscope_register( z, h2 );

    sqlite_delete( &stmt );
    sqlite_delete( &stmt2 );
    return h->_idx;
}

idx_t horoscope_update( ZodiaCore* z, Horoscope* h )
{
    assert( h );
    assert( h->_idx != 0 );

    Verbose( z, printf( "-- Updating horoscope %s\n", h->name->ptr ); )

    char dt[22];
    structtm_to_string( &h->datetime->dt, dt );

    sqlite_Stmt* stmt = NULL;
    sqlite_new( z, &stmt,
        "update Horoscopes set name=?, comments=?, datetime=?, timezone=?, "
        "location=?, country=?, latitude=?, longitude=?, altitude=? where _idx=?" );
    sqlite_bind_str( stmt, 0, h->name );
    sqlite_bind_str( stmt, 1, h->comments );
    sqlite_bind_charp( stmt, 2, dt );
    sqlite_bind_charp( stmt, 3, h->datetime->tzfile );
    sqlite_bind_str( stmt, 4, h->location );
    sqlite_bind_str( stmt, 5, h->country );
    sqlite_bind_double( stmt, 6, h->latitude );
    sqlite_bind_double( stmt, 7, h->longitude );
    sqlite_bind_int( stmt, 8, h->altitude );
    sqlite_bind_int( stmt, 9, h->_idx );
    const int i = sqlite_step( stmt );

    if ( i != SQLITE_DONE )
    {
        Verbose( z, printf( "Error duplicate horoscope %s\n", h->name->ptr ); )
        sqlite_delete( &stmt );
        return 0;
    }

#ifdef KAMALA
    h->changed = False;
#endif /* KAMALA */

    Horoscope* h2 = (Horoscope*)btree_value( z->horoscopeCollection, h->_idx );
    assert( h2 );
    horoscope_copy( h2, h );
    vector_sort( z->sortedHoroscopes,
        (int (*)(const void*, const void*))&horoscope_alphasort );

    uint j = 0;
    for ( ; j < z->chartCollection->len; ++j )
    {
        h2 = ((Chart**)z->chartCollection->ptr)[j]->wh1->horo;
        if ( h2->_idx == h->_idx )
            horoscope_copy( h2, h );
    }

    sqlite_delete( &stmt );
    return h->_idx;
}

idx_t horoscope_erase( ZodiaCore* z, Horoscope* h )
{
    assert( h );
    assert( h->_idx != 0 );

    Verbose( z, printf( "-- Erasing horoscope %s\n", h->name->ptr ); )

    sqlite_Stmt* stmt = NULL;
    sqlite_new( z, &stmt, "delete from Horoscopes where _idx = ?" );
    sqlite_bind_int( stmt, 0, h->_idx );
    Debug( int i = ) sqlite_step( stmt );

    Debug
    (
        if ( i != SQLITE_DONE )
            Fatal( printf( "Error unable to erase horoscope with idx %d\n", h->_idx ); )
    )

    Horoscope* h2 = (Horoscope*) btree_value( z->horoscopeCollection, h->_idx );
    assert( h2 );
    horoscope_unregister( z, h2 );
    if ( h2 != h )
        horoscope_delete( &h2 );

    uint j = 0;
    for ( ; j < z->chartCollection->len; ++j )
    {
        h2 = ((Chart**)z->chartCollection->ptr)[j]->wh1->horo;
        if ( h2->_idx == h->_idx )
        {
            h2->_idx = 0;
            h2->changed = False;
        }
    }

    idx_t tmp = h->_idx;
    h->_idx = 0;
#ifdef KAMALA
    h->changed = False;
#endif /* KAMALA */

    sqlite_delete( &stmt );
    return tmp;
}

int horoscope_alphasort( const Horoscope** h1, const Horoscope** h2 )
{
    return strcoll( (*h1)->name->ptr, (*h2)->name->ptr );
}

void horoscope_now( const ZodiaCore* z, Horoscope* h )
{
    assert( h );
    datetime_reset( z, h->datetime );
    str_copy( h->location, z->prefs->location );
    str_copy( h->country, z->prefs->country );
    h->latitude = z->prefs->latitude;
    h->longitude = z->prefs->longitude;
    h->altitude = z->prefs->altitude;
}

Horoscope* horoscope_whose_name( const ZodiaCore* z, const char* name )
{
    const size_t cnt = z->sortedHoroscopes->len;
    if ( !cnt )
        return NULL;

    Horoscope* tmp;
    size_t i = 0;

    for ( ; i < cnt; ++i )
    {
        tmp = ((Horoscope**)z->sortedHoroscopes->ptr)[i];
        if ( strequ( tmp->name->ptr, (char*) name ) )
            return tmp;
    }
    return NULL;
}

size_t horoscope_fake_insert( const ZodiaCore* z, const char* name )
{
    const size_t cnt = z->sortedHoroscopes->len;
    if ( !cnt )
        return 0;

    size_t i = 0;
    for ( ; i < cnt; ++i )
    {
        if ( strcoll(
            ((Horoscope**)z->sortedHoroscopes->ptr)[i]->name->ptr, name ) > 0 )
            return i;
    }
    return cnt;
}

#ifndef NDEBUG

void horoscope_debug( const Horoscope* h )
{
    assert( h );

    printf( "----- Horoscope:\n"
            "-- idx     = %d\n"
            "-- name    = %s\n"
            "-- comments= %s\n"
            "-- Location= %s\n"
            "-- Country = %s\n"
            "-- Latitude= %f\n"
            "-- Longitude=%f\n"
            "-- Altitude= %d\n",
        h->_idx, h->name->ptr, h->comments->ptr,
        h->location->ptr, h->country->ptr,
        h->latitude, h->longitude, h->altitude );

    datetime_debug( h->datetime );

    printf( "----- end horoscope\n" );
}

#endif /* !NDEBUG */
