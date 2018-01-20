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

#include "str.h"

const size_t STR_BUF_SZ = 32;   /* chunk of memory allocated */

void str_new( Str** s, const char* v )
{
    assert( *s == NULL );
    Trace( printf( "-- New str\n" ); )
    *s = Malloc( sizeof( Str ) );

    const size_t vlen = v ? strlen( v ) + 1 : 1;
    const size_t blen = ( ( vlen / STR_BUF_SZ ) + 1 ) * STR_BUF_SZ;

    (*s)->ptr = Malloc( sizeof( char ) * blen );

    (*s)->len = vlen;
    (*s)->buflen = blen;

    if ( v )
        strcpy( (*s)->ptr, v );
    else
        (*s)->ptr[0] = '\0';
}

void str_delete( Str** s )
{
    assert( *s );
    Trace( printf( "-- Delete str\n" ); )

    Free( (*s)->ptr, (*s)->buflen );
    (*s)->ptr = NULL;

    Free( *s, sizeof( Str ) );
    *s = NULL;
}

void str_set( Str* s, char* v, size_t len )
{
    assert( s );

    if ( !v )
    {
        v = (char*) "";
        len = 1;
    }
    else if ( len < 1 )
        len = strlen( v ) + 1;

    if ( len != s->len )
    {
        const size_t blen = ( ( len / STR_BUF_SZ ) + 1 ) * STR_BUF_SZ;
        if ( s->buflen != blen )
        {
            Trace( printf( "-- Realloc str\n" ); )
            s->ptr = Realloc( s->ptr, sizeof( char ) * blen, s->buflen );
            s->buflen = blen;
        }
        s->len = len;
    }
    else
    if ( strequ( v, s->ptr ) ) return;

    strncpy( s->ptr, v, len );
}

Bool strequ( char* s1, char* s2 )
{
    if ( s1 == s2 ) return True;
    while ( 1 )
    {
        if ( *s1 != *s2++ ) return False;
        if ( !*s1++ ) return True;
    }
}

char* notadigit( char* s )
{
    for ( ; *s; ++s )
    {
        if ( !isdigit( *s ) )
            return s;
    }
    return NULL;
}

#if 0
Bool str_truncate( Str* s, const size_t sz )
{
    assert( s );

    if ( s->len > sz + 1 )
    {
        const size_t blen = ( ( ( sz + 1 ) / STR_BUF_SZ ) + 1 ) * STR_BUF_SZ;
        if ( blen != s->buflen )
        {
            char* tmp = s->ptr;
            s->ptr = realloc( s->ptr, sizeof( char ) * blen );
            if ( !s->ptr )
            {
                s->ptr = tmp;
                Trace( printf( "Error unable to realloc %p\n", tmp ); )
                return False;
            }
            s->buflen = blen;
        }
        s->ptr[sz] = '\0';
        s->len = sz + 1;
        return True;
    }
    return False;
}

int str_no_char( Str* s, const char c )
{
    assert( s );

    if ( s->len == 1 ) return 0;

    Bool haschar = False;
    char* cur = s->ptr;

    for ( ; *cur != '\0'; ++cur )
    {
        if ( *cur == c )
        {
            haschar = True;
            break;
        }
    }
    if ( !haschar ) return 0;

    const size_t offset = cur - s->ptr;

    Str* s2 = NULL;
    str_new( &s2, s->ptr );
    int cnt = 0;

    for ( cur = s2->ptr + offset; *cur != '\0'; ++cur )
    {
        if ( *cur == c )
        {
            *cur = '\0';
            ++cnt;
        }
    }

    const size_t blen = ( ( ( s2->len - cnt ) / STR_BUF_SZ ) + 1 ) * STR_BUF_SZ;

    if ( blen != s2->buflen )
    {
        char* tmp = s->ptr;
        s->ptr = realloc( s->ptr, sizeof( char ) * blen );
        if ( !s->ptr )
        {
            s->ptr = tmp;
            Trace( printf( "Error unable to realloc %p", tmp ); )
            str_delete( &s2 );
            return 0;
        }
        s->buflen = blen;
    }

    const char* last = &s2->ptr[s2->len - 1];
    char* ptr = s->ptr + offset;

    for ( cur = s2->ptr + offset; cur != last; ++cur )
    {
        if ( *cur != '\0' )
        {
            *ptr = *cur;
            ++ptr;
        }
    }

    s->ptr[s2->len - cnt - 1] = '\0';
    s->len = s2->len - cnt;

    str_delete( &s2 );
    return cnt;
}
#endif
