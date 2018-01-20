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

#ifndef ZODIACORE_SQLITE_H
#define ZODIACORE_SQLITE_H

#ifdef __cplusplus
extern "C" {
#endif

void sqlite_init( ZodiaCore*, char* path );

void sqlite_fini( ZodiaCore* );

Bool sqlite_exec( ZodiaCore*, const char* sql );

typedef struct _sqlite_Stmt_t sqlite_Stmt;

struct _sqlite_Stmt_t
{
    char*           _sql;
    sqlite3_stmt*   _stmt;
};

void sqlite_new( ZodiaCore*, sqlite_Stmt** stmt, const char* sql );

void sqlite_delete( sqlite_Stmt** stmt );

void sqlite_bind_int( sqlite_Stmt* stmt, int iCol, int i );

void sqlite_bind_double( sqlite_Stmt* stmt, int iCol, double d );

void sqlite_bind_charp( sqlite_Stmt* stmt, int iCol, const char* s );

#define sqlite_bind_str( stmt, iCol, s )    sqlite_bind_charp( stmt, iCol, (s)->ptr )

int sqlite_step( sqlite_Stmt* stmt );

#define sqlite_get_int( stmt, iCol )    sqlite3_column_int( (stmt)->_stmt, (iCol) )

#define sqlite_get_double( stmt, iCol ) sqlite3_column_double( (stmt)->_stmt, (iCol) )

#define sqlite_get_bool( stmt, iCol )   (sqlite3_column_int( (stmt)->_stmt, (iCol) ) ? True : False)

#define sqlite_get_charp( stmt, iCol )  (char*) sqlite3_column_text( (stmt)->_stmt, (iCol) )

void sqlite_clear( sqlite_Stmt* stmt );

int sqlite_execfile( ZodiaCore*, const char *path );

#ifndef KAMALA

int sqlite_execmany( ZodiaCore*, const char* sql );

#endif /* !KAMALA */


#ifdef __cplusplus
}
#endif

#endif /* !ZODIACORE_SQLITE_H */
