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

#ifndef ZODIACORE_COMMON_H
#define ZODIACORE_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif


#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include <sqlite3.h>


#ifndef NDEBUG
#   define Debug( x )       x
#else
#   define Debug( x )
#endif /* !NDEBUG */

#ifdef TRACE
#   define Trace( x )       x
#else
#   define Trace( x )
#endif /* TRACE */

#ifndef SILENT
#   define Verbose( z, x )     if ( z->verboseFlag ) { x }
#else
#   define Verbose( z, x )
#endif /* !SILENT */

#define Fatal( x )      { x exit( -1 ); }

#ifndef NULL
#   define NULL         ((void*)0)
#endif /* !NULL */

#ifdef __cplusplus
#   define INLINE       inline
#elif defined __STDC_VERSION__ && __STDC_VERSION__ < 199901L
#   define INLINE
#else
#   define INLINE       extern inline
#endif /* INLINE */

#ifdef __GNUC__
#   define inline       __inline__
#endif /* __GNUC__ */

typedef unsigned int idx_t;

typedef enum { False, True } Bool;


#ifdef __cplusplus
}
#endif

#endif /* !ZODIACORE_COMMON_H */
