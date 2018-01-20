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

#include "atlas.h"

void atlas_init( ZodiaCore* z, char* path )
{
    char tmp[256];

    if ( !path )
    {
        path = getenv( "ZODIACORE_ATLAS_DB" );
        if ( !path )
        {
            assert( z->shareDir );

            const size_t sz = strlen( z->shareDir );
            strncpy( tmp, z->shareDir, sz );
            strcpy( &tmp[sz], "/atlas.db" );

            struct stat st;
            const int i = stat( tmp, &st );

            if ( i || !S_ISREG( st.st_mode )
#ifdef __unix
                || !( st.st_mode & S_IROTH )
#endif /* __unix */
                )
            {
                Verbose( z, printf( "-- Invalid atlas database file %s\n", tmp ); )
                tmp[0] = '\0';
            }
            path = tmp;
        }
    }
    assert( path );

    if ( path[0] == '\0' || path[0] == '0' )
    {
        Verbose( z, printf( "-- Atlas database disabled\n" ); )
        z->atlasCnx = NULL;
        return;
    }

    Verbose( z, printf( "-- Opening atlas database %s\n", path ); )

    Debug( const int i = )
        sqlite3_open_v2( path, &z->atlasCnx, SQLITE_OPEN_READONLY, NULL );

#ifndef NDEBUG
    if ( i != SQLITE_OK )
    {
        Fatal( printf( "Error %d unable to open database %s\n", i, path ); )
    }
#endif /* !NDEBUG */
}

void atlas_fini( ZodiaCore* z )
{
    if ( !z->atlasCnx )
        return;

    Verbose( z, printf( "-- Closing atlas database\n" ); )

    sqlite3_close( z->atlasCnx );
    z->atlasCnx = NULL;
}

