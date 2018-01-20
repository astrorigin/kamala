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

#ifndef ZODIACORE_VECTOR_H
#define ZODIACORE_VECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _vector_t Vector;

struct _vector_t
{
    void**  ptr;
    size_t  len;
    size_t  buflen;
};

void vector_new( Vector**, const size_t len );

void vector_delete( Vector** );

Bool vector_resize( Vector* );

void vector_append( Vector*, void* val );

void vector_remove( Vector*, uint idx );

void vector_sort( Vector*, int (*compar)(const void*, const void*) );

void vector_traverse( const Vector*, void (*func)(void*) );

size_t vector_index( const Vector*, const void* val );

#ifdef __cplusplus
}
#endif

#endif /* !ZODIACORE_VECTOR_H */
