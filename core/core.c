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

#include "core.h"

#include "memusage.c"

#include "atlas.c"
#include "aspect.c"
#include "aspectfilter.c"
#include "aspectrestr.c"
#include "btree.c"
#include "chart.c"
#include "context.c"
#include "data.c"
#include "datetime.c"
#include "geocoord.c"
#include "horoscope.c"
#include "matchasp.c"
#include "orb.c"
#include "orbfilter.c"
#include "orbrestr.c"
#include "planet.c"
#include "planetfilter.c"
#include "prefs.c"
#include "profile.c"
#include "raman.c"
#include "sqlite.c"
#include "str.c"
#include "vector.c"
#include "wheel.c"


void zodiacore_new( ZodiaCore** z )
{
    Trace( printf( "-- New ZodiaCore\n" ); )

    memusage_init();

    assert( *z == NULL );
    *z = Malloc( sizeof( ZodiaCore ) );

#ifndef SILENT
    (*z)->verboseFlag = True;
#endif /* !SILENT */

    (*z)->dataDir =
    (*z)->shareDir = NULL;

    (*z)->dataCnx =
    (*z)->atlasCnx = NULL;

    (*z)->prefs = NULL;

    (*z)->aspectCollection =
    (*z)->aspectFilterCollection =
    (*z)->aspectRestrCollection =
    (*z)->orbFilterCollection =
    (*z)->orbRestrCollection =
    (*z)->planetCollection =
    (*z)->planetFilterCollection =
    (*z)->profileCollection =
    (*z)->contextCollection =
    (*z)->horoscopeCollection = NULL;

    (*z)->sortedHoroscopes =
    (*z)->chartCollection = NULL;

    zodiacore_init_data_dir( *z );
    zodiacore_init_share_dir( *z );

    sqlite_init( *z, NULL );
    atlas_init( *z, NULL );

    aspect_init( *z );
    planet_init( *z );
    aspectfilter_init( *z );
    planetfilter_init( *z );
    orbfilter_init( *z );
    aspectrestr_init( *z );
    orbrestr_init( *z );
    profile_init( *z );
    context_init( *z );
    prefs_init( *z );
    horoscope_init( *z );
    chart_init( *z );

    memusage_debug();
}

void zodiacore_delete( ZodiaCore** z, Bool freeSwe )
{
    assert( *z );

    Free( (*z)->dataDir, sizeof( char ) * ( strlen( (*z)->dataDir ) + 1 ) );
    Free( (*z)->shareDir, sizeof( char ) * ( strlen( (*z)->shareDir ) + 1 ) );

    sqlite_fini( *z );
    atlas_fini( *z );

    aspect_fini( *z );
    planet_fini( *z );
    aspectfilter_fini( *z );
    planetfilter_fini( *z );
    orbfilter_fini( *z );
    aspectrestr_fini( *z );
    orbrestr_fini( *z );
    profile_fini( *z );
    context_fini( *z );
    prefs_fini( *z );
    horoscope_fini( *z );
    chart_fini( *z );

    Trace( printf( "-- Delete ZodiaCore\n" ); )
    Free( *z, sizeof( ZodiaCore ) );
    *z = NULL;

    if ( freeSwe ) swe_close();

    memusage_debug();
}


void zodiacore_init_data_dir( ZodiaCore* z )
{
    int i;
    char* home = getenv( "ZODIACORE_HOME_DIR" );

#ifdef KAMALA
    assert( home );
#else
    if ( !home )
    {
#ifdef __unix
        home = getenv( "HOME" );
#else
        home = getenv( "HOMEPATH" );
#endif /* __unix */
        assert( home );
        const size_t sz = strlen( home );

        z->dataDir = Malloc( sizeof( char ) * ( sz + 12 ) );

        strncpy( z->dataDir, home, sz );
        strcpy( &z->dataDir[sz], "/.zodiacore" );
    }
    else
    {
#endif /* KAMALA */
        z->dataDir = Malloc( sizeof( char ) * ( strlen( home ) + 1 ) );
        strcpy( z->dataDir, home );
#ifndef KAMALA
    }
#endif /* !KAMALA */

    Verbose( z, printf( "-- Checking home directory %s\n", z->dataDir ); )

    struct stat st;
    i = stat( z->dataDir, &st );
    if ( i )
    {
        Verbose( z, printf( "-- Creating home directory %s\n", z->dataDir ); )
#ifdef __unix
        Debug( i = ) mkdir( z->dataDir, S_IRWXU );
#else
        Debug( i = ) mkdir( z->dataDir );
#endif /* __unix */
        assert( !i );
    }
    else
    {
        assert( S_ISDIR( st.st_mode ) );
        assert( st.st_mode & S_IRWXU );
    }
}

void zodiacore_init_share_dir( ZodiaCore* z )
{
    int i;
    struct stat st;
    char* path = getenv( "ZODIACORE_SHARE_DIR" );

#ifndef KAMALA
    if ( !path )
    {
#ifdef __unix
        const char* const paths[] =
        {
            "/usr/share/zodiacore",
            "/usr/local/share/zodiacore",
            "/share/zodiacore",
            "/usr/opt/zodiacore",
            "/usr/local/opt/zodiacore",
            "/opt/zodiacore",
            NULL
        };
#else
        const char* const paths[] =
        {
            "C:/ZodiaCore",
            "C:/ChaosOrigin",
            "C:/ChaosOrigin/ZodiaCore",
            "C:/Program Files/ZodiaCore",
            "C:/Program Files/ChaosOrigin",
            "C:/Program Files/ChaosOrigin/ZodiaCore",
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
    }
#else
    assert( path );
#endif /* !KAMALA */

    if ( path )
    {
        Verbose( z, printf( "-- Checking shared directory %s\n", path ); )
        i = stat( path, &st );
    }
    else
    {
        path = (char*) "?";
        i = 1;
    }

    if ( i )
    {
        Fatal
        (
            printf( "-- Fatal %d unable to stat shared directory %s\n", i, path );
            printf( "-- Check your installation\n" );
        )
    }
    assert( S_ISDIR( st.st_mode ) );
#ifdef __unix
    assert( st.st_mode & ( S_IROTH | S_IXOTH ) );
#endif /* __unix */

    z->shareDir = Malloc( sizeof( char ) * ( strlen( path ) + 1 ) );
    strcpy( z->shareDir, path );
}
