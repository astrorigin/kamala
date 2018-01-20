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

#include "vector.h"

const size_t VECTOR_BUF_SZ = 128; /* chunk of memory allocated */

void vector_new( Vector** v, const size_t len )
{
    assert( *v == NULL );
    Trace( printf( "-- New vector\n" ); )
    *v = Malloc( sizeof( Vector ) );

    (*v)->ptr = NULL;
    (*v)->len = len;
    (*v)->buflen = 0;

    Debug( Bool b = ) vector_resize( *v );
    assert( b );
}

void vector_delete( Vector** v )
{
    assert( *v );
    Trace( printf( "-- Delete vector\n" ); )

    if ( (*v)->ptr )
        Free( (*v)->ptr, sizeof( void* ) * (*v)->buflen );

    Free( *v, sizeof( Vector ) );
    *v = NULL;
}

Bool vector_resize( Vector* v )
{
    if ( ( v->len < v->buflen )
        && ( v->len >= ( VECTOR_BUF_SZ * 2 > v->buflen ?
            0 : ( v->buflen - ( VECTOR_BUF_SZ * 2 ) ) ) ) ) return True;

    Trace( printf( "-- Resize vector\n" ); )
    if ( v->ptr )
        v->ptr = Realloc( v->ptr, sizeof( void* ) * ( v->len + VECTOR_BUF_SZ ),
            ( sizeof( void* ) * v->buflen ) );
    else
        v->ptr = Malloc( sizeof( void* ) * ( v->len + VECTOR_BUF_SZ ) );

    v->buflen = v->len + VECTOR_BUF_SZ;
    return True;
}

void vector_append( Vector* v, void* val )
{
    Debug( Bool b = ) vector_resize( v );
    assert( b );
    v->ptr[v->len] = val;
    v->len += 1;
}

void vector_remove( Vector* v, uint idx )
{
    assert( idx < v->len );

    if ( idx != v->len - 1 )
    {
        const size_t sz = sizeof( void* ) * ( ( v->len - 1 ) - idx );
        assert( sz );
        memmove( &v->ptr[idx], &v->ptr[idx + 1], sz );
    }
    v->len -= 1;
    Debug( Bool b = ) vector_resize( v );
    assert( b );
}

void vector_sort( Vector* v, int (*compar)(const void*, const void*) )
{
    qsort( (void*) v->ptr, v->len, sizeof( void* ), compar );
}

void vector_traverse( const Vector* v, void (*func)(void*) )
{
    if ( !v ) return;

    size_t i = 0;
    const size_t cnt = v->len;
    for ( ; i < cnt; ++i )
        (*func)( &v->ptr[i] );
}

size_t vector_index( const Vector* v, const void* val )
{
    size_t i = 0;
    const size_t cnt = v->len;
    for ( ; i < cnt; ++i )
    {
        if ( v->ptr[i] == val )
            return i;
    }
#ifndef NDEBUG
    assert( 0 );
#else
    Fatal( printf( "Fatal: invalid vector index search\n" ); )
#endif /* !NDEBUG */
}
