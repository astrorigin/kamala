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

#include "datetime.h"

#include "prefs.h"
#include "str.h"
#include <swephexp.h>

void datetime_new( DateTime** dt )
{
    assert( *dt == NULL );
    Trace( printf( "-- New datetime\n" ); )
    *dt = Malloc( sizeof( DateTime ) );

    (*dt)->cal = GregorianCalendar;
    (*dt)->tzfile[0] = '\0';
    (*dt)->isdst = -1;
    (*dt)->utcoffset = 0;
    (*dt)->jd = -1;
    (*dt)->tzname[0] = '\0';
}

void datetime_delete( DateTime** dt )
{
    assert( *dt );
    Trace( printf( "-- Delete datetime\n" ); )
    Free( *dt, sizeof( DateTime ) );
    *dt = NULL;
}

Bool datetime_equals( const DateTime* dt, const DateTime* other )
{
    assert( dt && other );
    if ( dt == other ) return True;

    if ( dt->cal == other->cal
        && dt->dt.tm_year == other->dt.tm_year
        && dt->dt.tm_mon == other->dt.tm_mon
        && dt->dt.tm_mday == other->dt.tm_mday
        && dt->dt.tm_hour == other->dt.tm_hour
        && dt->dt.tm_min == other->dt.tm_min
        && dt->dt.tm_sec == other->dt.tm_sec
        && strequ( (char*) dt->tzfile, (char*) other->tzfile )
        && dt->isdst == other->isdst
        && dt->utcoffset == other->utcoffset
        && dt->jd == other->jd
        && strequ( (char*) dt->tzname, (char*) other->tzname ) )
        return True;

    return False;
}

time_t datetime_now( DateTime* dt, const char* tzfile )
{
    assert( dt );
    assert( tzfile[0] == ':' );

    dt->cal = GregorianCalendar;

#ifdef __unix
    Debug( int i = ) setenv( "TZ", tzfile, 1 );
#else
    char tz[50];
    sprintf( tz, "TZ=%s", tzfile );
    Debug( int i = ) _putenv( tz );
#endif /* __unix */
    assert( !i );
    tzset();

    const time_t t = time( NULL );

#ifdef __unix
    struct tm tmp;
    gmtime_r( &t, &tmp );

    dt->jd = swe_julday( tmp.tm_year + 1900, tmp.tm_mon + 1, tmp.tm_mday,
        tmp.tm_hour + ( tmp.tm_min / 60.0 ) + ( tmp.tm_sec / 3600.0 ), SE_GREG_CAL );

    localtime_r( &t, &dt->dt );
#else
    struct tm *tmp = gmtime( &t );

    dt->jd = swe_julday( tmp->tm_year + 1900, tmp->tm_mon + 1, tmp->tm_mday,
        tmp->tm_hour + ( tmp->tm_min / 60.0 ) + ( tmp->tm_sec / 3600.0 ), SE_GREG_CAL );

    tmp = localtime( &t );
    dt->dt = *tmp;
#endif /* __unix */

    if ( dt->dt.tm_isdst == 1 )
        strcpy( dt->tzname, tzname[1] );
    else
        strcpy( dt->tzname, tzname[0] );

    strcpy( dt->tzfile, tzfile );
    dt->utcoffset = timezone;
    dt->isdst = -1;

    return t;
}

int datetime_set( DateTime* dt, const char* date,
                    const char* tzfile, int isdst, int utcoffset )
{
    assert( date && tzfile );

    structtm_from_string( &dt->dt, date );
    strcpy( dt->tzfile, tzfile );
    dt->isdst = isdst;
    dt->utcoffset = utcoffset;

    return datetime_make( dt );
}

int datetime_make( DateTime* dt )
{
    assert( dt );

    time_t t;
    Debug( int i; )

    const Bool usetz = ( dt->dt.tm_year >= 1 && dt->tzfile[0] == ':' );

    if ( usetz )
    {
        assert( dt->cal == GregorianCalendar );

        dt->dt.tm_isdst = dt->isdst;
#ifdef __unix
        Debug( i = ) setenv( "TZ", dt->tzfile, 1 );
#else
        char tz[50];
        sprintf( tz, "TZ=%s", dt->tzfile );
        Debug( i = ) _putenv( tz );
#endif /* __unix */
        assert( !i );
        tzset();

        t = mktime( &dt->dt );
        if ( t == -1 ) return -1;

#ifdef __unix
        struct tm tmp;
        gmtime_r( &t, &tmp );

        dt->jd = swe_julday( tmp.tm_year + 1900, tmp.tm_mon + 1, tmp.tm_mday,
            tmp.tm_hour + ( tmp.tm_min / 60.0 ) + ( tmp.tm_sec / 3600.0 ), SE_GREG_CAL );
#else
        struct tm *tmp = gmtime( &t );

        dt->jd = swe_julday( tmp->tm_year + 1900, tmp->tm_mon + 1, tmp->tm_mday,
            tmp->tm_hour + ( tmp->tm_min / 60.0 ) + ( tmp->tm_sec / 3600.0 ), SE_GREG_CAL );
#endif /* __unix */

        dt->utcoffset = timezone;
    }
    else
    {
        dt->dt.tm_isdst = 0;
        t = 0;

        swe_date_conversion( dt->dt.tm_year + 1900, dt->dt.tm_mon + 1, dt->dt.tm_mday,
            ( dt->dt.tm_hour + ( dt->dt.tm_min / 60.0 )
            + ( ( dt->dt.tm_sec + dt->utcoffset ) / 3600.0 ) ),
            dt->cal == GregorianCalendar ? 'g' : 'j', &dt->jd );
    }

    if ( usetz )
    {
        if ( dt->dt.tm_isdst )
            strcpy( dt->tzname, tzname[1] );
        else
            strcpy( dt->tzname, tzname[0] );
    }
    else strcpy( dt->tzname, "-" );

    return t;
}

void structtm_to_string( const struct tm* dt, char* buf )
{
    sprintf( buf, "%d-%.2d-%.2d %.2d:%.2d:%.2d", dt->tm_year + 1900, dt->tm_mon + 1,
        dt->tm_mday, dt->tm_hour, dt->tm_min, dt->tm_sec );
}

void structtm_from_string( struct tm* dt, const char* date )
{
    char buf[22];
    strcpy( buf, date );
    char* tmp = buf;

    char* tok = notadigit( tmp );
    assert( tok );
    *tok = '\0';
    dt->tm_year = atoi( tmp ) - 1900;
    tmp = tok + 1;

    tok = notadigit( tmp );
    assert( tok );
    *tok = '\0';
    dt->tm_mon = atoi( tmp ) - 1;
    tmp = tok + 1;

    tok = notadigit( tmp );
    assert( tok );
    *tok = '\0';
    dt->tm_mday = atoi( tmp );
    tmp = tok + 1;

    tok = notadigit( tmp );
    assert( tok );
    *tok = '\0';
    dt->tm_hour = atoi( tmp );
    tmp = tok + 1;

    tok = notadigit( tmp );
    assert( tok );
    *tok = '\0';
    dt->tm_min = atoi( tmp );
    tmp = tok + 1;

    dt->tm_sec = atoi( tmp );
}

long timezone_offset( const char* tzfile )
{
    assert( tzfile && tzfile[0] == ':' );
#ifdef __unix
    Debug( int i = ) setenv( "TZ", tzfile, 1 );
#else
    char tz[50];
    sprintf( tz, "TZ=%s", dt->tzfile );
    Debug( int i = ) _putenv( tz );
#endif /* __unix */
    assert( !i );
    tzset();
    return timezone;
}

#ifndef NDEBUG

void datetime_debug( const DateTime* dt )
{
    assert( dt );

    printf( "----- DateTime:\n"
            "-- Calendar    = %d\n"
            "-- Dt  = %d/%d/%d %d:%d:%d (isdst = %d)\n"
            "-- TzFile  = %s\n"
            "-- IsDst   = %d\n"
            "-- UtcOffset   = %ld\n"
            "-- JD  = %f\n"
            "-- TzName  = %s\n"
            "----- end datetime\n",
        dt->cal,
        dt->dt.tm_year + 1900, dt->dt.tm_mon + 1, dt->dt.tm_mday,
        dt->dt.tm_hour, dt->dt.tm_min, dt->dt.tm_sec, dt->dt.tm_isdst,
        dt->tzfile, dt->isdst, dt->utcoffset, dt->jd, dt->tzname );
}

#endif /* !NDEBUG */
