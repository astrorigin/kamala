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

#ifndef ZODIACORE_MEMUSAGE_H
#define ZODIACORE_MEMUSAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NDEBUG

void memusage_init();

#define Malloc( sz )        memusage_malloc( sz, __FILE__, __LINE__ )

void* memusage_malloc( const size_t, const char*, const int );

#define Free( p, sz )       memusage_free( p, sz, __FILE__, __LINE__ )

void memusage_free( void*, const size_t, const char*, const int );

#define Realloc( p, sz1, sz2 )      memusage_realloc( p, sz1, sz2, __FILE__, __LINE__ )

void* memusage_realloc( void*, const size_t, const size_t, const char*, const int );

void memusage_debug();

#else

#define memusage_init()
#define Malloc( sz )            malloc( sz )
#define Free( p, sz )           free( p )
#define Realloc( p, sz1, sz2 )  realloc( p, sz1 )
#define memusage_debug()

#endif /* !NDEBUG */

#ifdef __cplusplus
}
#endif

#endif /* !ZODIACORE_MEMUSAGE_H */
