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

#ifndef ZODIACORE_STR_H
#define ZODIACORE_STR_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _str_t Str;

struct _str_t
{
    char*   ptr;    /* pointer to null-terminated string */
    size_t  len;    /* memory used, including null */
    size_t  buflen; /* memory allocated */
};

void str_new( Str**, const char* val );

void str_delete( Str** );

void str_set( Str*, char* val, size_t len );

Bool strequ( char* s1, char* s2 );

#define str_equ( s1, s2 )       strequ( (s1)->ptr, (s2)->ptr )

#define str_copy( s1, s2 )      str_set( s1, (s2)->ptr, (s2)->len )

char* notadigit( char* );


#if 0
Bool str_truncate( Str*, const size_t sz );

int str_no_char( Str*, const char c );
#endif

#ifdef __cplusplus
}
#endif

#endif /* !ZODIACORE_STR_H */
