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

#ifndef ZODIACORE_HOROSCOPE_H
#define ZODIACORE_HOROSCOPE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "datetime.h"
#include "geocoord.h"
#include "sqlite.h"
#include "str.h"

typedef struct _horoscope_t Horoscope;

struct _horoscope_t
{
    idx_t   _idx;
    Str*    name;
    Str*    comments;

    DateTime*   datetime;

    Str*    location;
    Str*    country;

    GeoLat  latitude;
    GeoLon  longitude;
    GeoAlt  altitude;

#ifdef KAMALA
    Bool    changed;
#endif /* KAMALA */
};

void horoscope_init( ZodiaCore* );

void horoscope_fini( ZodiaCore* );

void horoscope_register( ZodiaCore*, const Horoscope* );

void horoscope_unregister( ZodiaCore*, const Horoscope* );

void horoscope_new( const ZodiaCore*, Horoscope** );

void horoscope_delete( Horoscope** );

void horoscope_copy( Horoscope*, const Horoscope* other );

Bool horoscope_equals( const Horoscope*, const Horoscope* other );

void horoscope_set_row( Horoscope*, const sqlite_Stmt* );

idx_t horoscope_insert( ZodiaCore*, Horoscope* );

idx_t horoscope_update( ZodiaCore*, Horoscope* );

idx_t horoscope_erase( ZodiaCore*, Horoscope* );

int horoscope_alphasort( const Horoscope**, const Horoscope** );

void horoscope_now( const ZodiaCore*, Horoscope* );

Horoscope* horoscope_whose_name( const ZodiaCore*, const char* name );

size_t horoscope_fake_insert( const ZodiaCore*, const char* name );

#define horoscope_index( z, h )     vector_index( z->sortedHoroscopes, h )

#ifndef NDEBUG

void horoscope_debug( const Horoscope* );

#endif /* !NDEBUG */

#ifdef __cplusplus
}
#endif

#endif /* !ZODIACORE_HOROSCOPE_H */
