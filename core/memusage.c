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

#include "memusage.h"

#include "common.h"

#ifndef NDEBUG

static struct _memusage_t
{
    size_t  cnt;
    size_t  used;
} MemUsage;

void memusage_init()
{
    MemUsage.cnt = 0;
    MemUsage.used = 0;
}

void* memusage_malloc( const size_t sz, const char* file, const int line )
{
    Trace( printf( "-- Allocating %d bytes from %s at line %d\n", sz, file, line ); )
    void* ptr = malloc( sz );
    if ( !ptr )
    {
        Fatal( printf( "Error: Alloc failed\n" ); )
    }
    MemUsage.cnt += 1;
    MemUsage.used += sz;
    return ptr;
}

void memusage_free( void* p, const size_t sz, const char* file, const int line )
{
    Trace( printf( "-- Freeing %d bytes from %s at line %d\n", sz, file, line ); )
    free( p );
    MemUsage.cnt -= 1;
    MemUsage.used -= sz;
}

void* memusage_realloc( void* p, const size_t sz1, const size_t sz2, const char* file, const int line )
{
    Trace( printf( "-- Reallocating %d/%d bytes from %s at line %d\n", sz1, sz2, file, line ); )
    void* ptr = realloc( p, sz1 );
    if ( !ptr )
    {
        Fatal( printf( "Error: Realloc failed\n" ); )
    }
    MemUsage.used -= sz2;
    MemUsage.used += sz1;
    return ptr;
}

void memusage_debug()
{
    printf( "----- Memory usage:\n"
            "-- Count:  %d\n"
            "-- Used:   %d\n"
            "----- end memusage\n",
        MemUsage.cnt, MemUsage.used );
}

#endif /* NDEBUG */
