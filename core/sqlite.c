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

#include "sqlite.h"

#ifndef KAMALA
#   include "../../bld/sqlite_creates.sql.c"
#   include "../../bld/sqlite_inserts.sql.c"
#   ifndef NDEBUG
#       include "../../bld/sqlite_test.sql.c"
#   endif /* !NDEBUG */
#endif /* !KAMALA */

void sqlite_init( ZodiaCore* z, char* path )
{
    char tmp[256];

    if ( !path )
    {
        path = getenv( "ZODIACORE_DB" );
        if ( !path )
        {
            assert( z->dataDir );

            size_t sz = strlen( z->dataDir );
            strncpy( tmp, z->dataDir, sz );
#ifndef KAMALA
            strcpy( &tmp[sz], "/zodiacore.db" );
#else
            strcpy( &tmp[sz], "/kamala.db" );
#endif /* !KAMALA */
            path = tmp;
        }
    }
    assert( path );

    Verbose( z, printf( "-- Opening database %s\n", path ); )

    int i = sqlite3_open( path, &z->dataCnx );
    if ( i != SQLITE_OK )
    {
        Fatal( printf( "Error %d unable to open database %s\n", i, path ); )
    }

#ifndef NDEBUG
    if ( strequ( path, (char*) ":memory:" ) )
        return;
#endif /* !NDEBUG */

    sqlite_Stmt* stmt = NULL;
    sqlite_new( z, &stmt,
        "select count(name) from sqlite_master where type='table'" );
    Debug( i = ) sqlite_step( stmt );
    assert( i == SQLITE_ROW );

    if ( sqlite_get_int( stmt, 0 ) == 0 )
    {
        const char* creates = getenv( "ZODIACORE_DB_CREATES" );
        const char* inserts = getenv( "ZODIACORE_DB_INSERTS" );
#ifndef KAMALA
        if ( creates )
            sqlite_execfile( z, creates );
        else
            sqlite_execmany( z, (char*) sqlite_creates_c );

        if ( inserts )
            sqlite_execfile( z, inserts );
        else
            sqlite_execmany( z, (char*) sqlite_inserts_c );
#else
        assert( creates && inserts );
        sqlite_execfile( z, creates );
        sqlite_execfile( z, inserts );
#endif /* !KAMALA */
    }

    sqlite_delete( &stmt );
}

void sqlite_fini( ZodiaCore* z )
{
    if ( !z->dataCnx )
        return;

    Verbose( z, printf( "-- Closing database\n" ); )

    Debug( const Bool b = ) sqlite_exec( z, "vacuum" );
    assert( b );
    sqlite3_close( z->dataCnx );
    z->dataCnx = NULL;
}

Bool sqlite_exec( ZodiaCore* z, const char* sql )
{
    char* err;
    const int i = sqlite3_exec( z->dataCnx, sql, NULL, NULL, &err );
    if ( i != SQLITE_OK
        && i != SQLITE_DONE
        && i != SQLITE_ROW )
    {
        Debug( printf( "Error %d executing SQL\n%s\n%s\n", i, sql, err ); )
        sqlite3_free( err );
        return False;
    }
    return True;
}

void sqlite_new( ZodiaCore* z, sqlite_Stmt** stmt, const char* sql )
{
    assert( *stmt == NULL );
    Trace( printf( "-- New sql stmt\n" ); )
    *stmt = Malloc( sizeof( sqlite_Stmt ) );

    (*stmt)->_sql = (char*) sql;
    const char* tail;

    Debug( const int i = )
        sqlite3_prepare_v2( z->dataCnx, sql, -1, &(*stmt)->_stmt, &tail );
#ifndef NDEBUG
    if ( i != SQLITE_OK )
    {
        printf( "Error %d preparing SQL\n%s\n%s\n",
            i, sql, sqlite3_errmsg( z->dataCnx ) );
    }
#endif /* !NDEBUG */
}

void sqlite_delete( sqlite_Stmt** stmt )
{
    assert( *stmt );
    sqlite3_finalize( (*stmt)->_stmt );
    Trace( printf( "-- Delete sql stmt\n" ); )
    Free( *stmt, sizeof( sqlite_Stmt ) );
    *stmt = NULL;
}

void sqlite_bind_int( sqlite_Stmt* stmt, int iCol, int i )
{
    Debug( const int j = ) sqlite3_bind_int( stmt->_stmt, iCol + 1, i );
    assert( j == SQLITE_OK );
}

void sqlite_bind_double( sqlite_Stmt* stmt, int iCol, double d )
{
    Debug( const int i = ) sqlite3_bind_double( stmt->_stmt, iCol + 1, d );
    assert( i == SQLITE_OK );
}

void sqlite_bind_charp( sqlite_Stmt* stmt, int iCol, const char* s )
{
    Debug( const int i = )
        sqlite3_bind_text( stmt->_stmt, iCol + 1, s, -1, SQLITE_STATIC );
    assert( i == SQLITE_OK );
}

int sqlite_step( sqlite_Stmt* stmt )
{
#ifndef NDEBUG
    const int i = sqlite3_step( stmt->_stmt );
    if ( i != SQLITE_OK
        && i != SQLITE_ROW
        && i != SQLITE_DONE )
    {
        printf( "Error %d steping SQL\n%s\n", i, stmt->_sql );
    }
    return i;
#else
    return sqlite3_step( stmt->_stmt );
#endif /* !NDEBUG */
}

void sqlite_clear( sqlite_Stmt* stmt )
{
    sqlite3_reset( stmt->_stmt );
    sqlite3_clear_bindings( stmt->_stmt );
}

int sqlite_execfile( ZodiaCore* z, const char* path )
{
    Verbose( z, printf( "-- Executing sql file %s\n", path ); )

    int i;
    Bool b;
    int cnt = 0;

    FILE *f = fopen( path, "r" );
    assert( f );

    fseek( f, 0, SEEK_END );
    const long fsz = ftell( f );
    fseek( f, 0, SEEK_SET );
    assert( ftell( f ) == 0 );

    char s[fsz + 1];
    char* ptr = s;

    Debug( b = ) sqlite_exec( z, "begin" );
    assert( b );

    for ( i = 0; i < fsz; ++i )
    {
        s[i] = fgetc( f );
        if ( s[i] == '/'
            && i > 3
            && s[i - 1] == '*'
            && s[i - 2] == '*'
            && s[i - 3] == '*'
            && s[i - 4] == '/' )
        {
            s[i - 4] = '\0';
            b = sqlite_exec( z, ptr );
            if ( !b )
                break;
            ++cnt;
            assert( cnt < 1000000 );
            ptr = &s[i + 1];
        }
    }

    Debug( b = ) sqlite_exec( z, "commit" );
    assert( b );

    Debug( i = ) fclose( f );
    assert( i == 0 );
    return cnt;
}

#ifndef KAMALA

int sqlite_execmany( ZodiaCore* z, const char* sql )
{
    Bool b;
    const size_t sz = strlen( sql );

    char* sql2 = Malloc( sizeof( char ) * ( sz + 1 ) );
    memcpy( sql2, sql, sz + 1 );

    size_t i = 0;
    int cnt = 0;
    char* ptr = sql2;

    Debug( b = ) sqlite_exec( z, "begin" );
    assert( b );

    for ( ; i < sz; ++i )
    {
        if ( sql[i] == '/'
            && i > 3
            && sql[i - 1] == '*'
            && sql[i - 2] == '*'
            && sql[i - 3] == '*'
            && sql[i - 4] == '/' )
        {
            sql2[i - 4] = '\0';
            b = sqlite_exec( z, ptr );
            if ( !b )
                break;
            ++cnt;
            assert( cnt < 1000000 );
            ptr = &sql2[i + 1];
        }
    }

    Debug( b = ) sqlite_exec( z, "commit" );
    assert( b );

    Free( sql2, sizeof( char ) * ( sz + 1 ) );
    return cnt;
}

#endif /* !KAMALA */
