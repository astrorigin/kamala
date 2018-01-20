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

#ifndef ZODIACORE_DATETIME_H
#define ZODIACORE_DATETIME_H

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>

typedef struct _datetime_t DateTime;

enum calendar_t
{
    JulianCalendar      = 0,
    GregorianCalendar
};

struct _datetime_t
{
    int         cal;            /* calendar */
    struct tm   dt;             /* date & time */
    char        tzfile[36];     /* :tz file or "" for manual offset */

    int         isdst;          /* DST on=1, off=0, ?=-1 */
    long        utcoffset;      /* utc offset */

    double      jd;             /* julian day */
    char        tzname[36];     /* tz name */
};

void datetime_new( DateTime** );

void datetime_delete( DateTime** );

#define datetime_copy( dt, other )      (*dt) = (*other)

Bool datetime_equals( const DateTime*, const DateTime* other );

time_t datetime_now( DateTime*, const char* tzfile );

#define datetime_reset( z, dt )         datetime_now( dt, z->prefs->timezone )

int datetime_set( DateTime*, const char* date,
                    const char* tzfile, int isdst, int utcoffset );

int datetime_make( DateTime* );

void structtm_to_string( const struct tm*, char* buf );

void structtm_from_string( struct tm*, const char* date );

long timezone_offset( const char* tzfile );

#ifndef NDEBUG

void datetime_debug( const DateTime* );

#endif /* !NDEBUG */

#ifdef __cplusplus
}
#endif

#endif /* !ZODIACORE_DATETIME_H */
