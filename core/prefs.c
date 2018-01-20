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

#include "prefs.h"

#include "sqlite.h"
#include <swephexp.h>

void prefs_init( ZodiaCore* z )
{
    assert( z->contextCollection );
    assert( z->profileCollection );

    Verbose( z, printf( "-- Loading preferences\n" ); )

    z->prefs = Malloc( sizeof( Prefs ) );

    z->prefs->ephePath = NULL;
#ifndef NDEBUG
    z->prefs->location =
    z->prefs->country =
    z->prefs->theme = NULL;
#endif /* !NDEBUG */

    Debug( int i; )
    sqlite_Stmt* stmt = NULL;
    sqlite_new( z, &stmt, "select * from Preferences" );

    Debug( i = ) sqlite_step( stmt );
    assert( i == SQLITE_ROW );

    prefs_set_ephe_path( z, sqlite_get_charp( stmt, 0 ) );

    z->prefs->context = btree_value( z->contextCollection, sqlite_get_int( stmt, 1 ) );
    z->prefs->profile = btree_value( z->profileCollection, sqlite_get_int( stmt, 2 ) );
    str_new( &z->prefs->location, sqlite_get_charp( stmt, 3 ) );
    str_new( &z->prefs->country, sqlite_get_charp( stmt, 4 ) );
    z->prefs->latitude = sqlite_get_double( stmt, 5 );
    z->prefs->longitude = sqlite_get_double( stmt, 6 );
    z->prefs->altitude = sqlite_get_int( stmt, 7 );
    strcpy( z->prefs->timezone, sqlite_get_charp( stmt, 8 ) );
    strcpy( z->prefs->bgcolor, sqlite_get_charp( stmt, 9 ) );
    str_new( &z->prefs->theme, sqlite_get_charp( stmt, 10 ) );
    z->prefs->openMaximized = sqlite_get_int( stmt, 11 );

    sqlite_delete( &stmt );
}

void prefs_fini( ZodiaCore* z )
{
    assert( z->prefs );

    str_delete( &z->prefs->ephePath );
    str_delete( &z->prefs->location );
    str_delete( &z->prefs->country );
    str_delete( &z->prefs->theme );

    Trace( printf( "-- Delete preferences\n" ); )
    Free( z->prefs, sizeof( Prefs ) );
    z->prefs = NULL;
}

void prefs_set_ephe_path( ZodiaCore* z, char* path )
{
    if ( !path || path[0] == '\0' )
    {
        path = NULL;
        int i;
#ifdef __unix
        const char* paths[] =
        {
            "/usr/share/swisseph",
            "/usr/local/share/swisseph",
            "/share/swisseph",
            "/usr/opt/swisseph",
            "/usr/local/opt/swisseph",
            "/opt/swisseph",
            NULL
        };
#else
        const char* paths[] =
        {
            "C:/SwissEph",
            "C:/ZodiaCore/SwissEph",
            "C:/ChaosOrigin/SwissEph",
            "C:/ChaosOrigin/ZodiaCore/SwissEph",
            "C:/Program Files/ZodiaCore/SwissEph",
            "C:/Program Files/ChaosOrigin/SwissEph",
            "C:/Program Files/ChaosOrigin/ZodiaCore/SwissEph",
            NULL
        };
#endif /* __unix */
        for ( i = 0; paths[i]; ++i )
        {
            if ( !access( paths[i], R_OK ) )
            {
                path = (char*) paths[i];
                break;
            }
        }

        if ( !path )
        {
            Fatal( printf(
                "Fatal: Unable to find swisseph directory in:\n"
#ifdef __unix
                "`/usr/share/swisseph' `/usr/local/share/swisseph' `/share/swisseph'\n"
                "`/usr/opt/swisseph' `/usr/local/opt/swisseph' `/opt/swisseph'\n"
#else
                "C:/SwissEph C:/ZodiaCore/SwissEph C:/ChaosOrigin/SwissEph\n"
                "C:/ChaosOrigin/ZodiaCore/SwissEph C:/Program Files/ZodiaCore/SwissEph\n",
                "C:/Program Files/ChaosOrigin/SwissEph C:/Program Files/ChaosOrigin/ZodiaCore/SwissEph\n",
#endif /* __unix */
                "Please refer to the INSTALL file." ); )
        }
    }

    Verbose( z, printf( "-- Setting ephemeris path to %s\n", path ); )

    if ( !z->prefs->ephePath )
        str_new( &z->prefs->ephePath, path );
    else
        str_set( z->prefs->ephePath, (char*) path, 0 );

    swe_set_ephe_path( (char*) path );
}

void prefs_save( ZodiaCore* z )
{
    Verbose( z, printf( "-- Saving preferences\n" ); )

    sqlite_Stmt* stmt = NULL;
    sqlite_new( z, &stmt,
        "update Preferences set ephePath=?, contextIdx=?, profileIdx=?, "
        "location=?, country=?, latitude=?, longitude=?, altitude=?, "
        "timezone=?, bgcolor=?, theme=?, openMax=?" );
    sqlite_bind_str( stmt, 0, z->prefs->ephePath );
    sqlite_bind_int( stmt, 1, z->prefs->context->_idx );
    sqlite_bind_int( stmt, 2, z->prefs->profile->_idx );
    sqlite_bind_str( stmt, 3, z->prefs->location );
    sqlite_bind_str( stmt, 4, z->prefs->country );
    sqlite_bind_double( stmt, 5, z->prefs->latitude );
    sqlite_bind_double( stmt, 6, z->prefs->longitude );
    sqlite_bind_int( stmt, 7, z->prefs->altitude );
    sqlite_bind_charp( stmt, 8, z->prefs->timezone );
    sqlite_bind_charp( stmt, 9, z->prefs->bgcolor );
    sqlite_bind_str( stmt, 10, z->prefs->theme );
    sqlite_bind_int( stmt, 11, z->prefs->openMaximized );
    Debug( int i = ) sqlite_step( stmt );
    assert( i == SQLITE_DONE );

    sqlite_delete( &stmt );
}
