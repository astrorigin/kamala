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

#ifndef ZODIACORE_CORE_H
#define ZODIACORE_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

#define ZODIACORE_IVERSION      20090722
#define ZODIACORE_CVERSION      "20090722"

#include "common.h"
#include "memusage.h"

typedef struct _zodiacore_t ZodiaCore;

#include "atlas.h"
#include "aspect.h"
#include "aspectfilter.h"
#include "aspectrestr.h"
#include "btree.h"
#include "chart.h"
#include "context.h"
#include "data.h"
#include "datetime.h"
#include "geocoord.h"
#include "horoscope.h"
#include "matchasp.h"
#include "orb.h"
#include "orbfilter.h"
#include "orbrestr.h"
#include "planet.h"
#include "planetfilter.h"
#include "prefs.h"
#include "profile.h"
#include "raman.h"
#include "sqlite.h"
#include "str.h"
#include "vector.h"
#include "wheel.h"


struct _zodiacore_t
{
#ifndef SILENT
    Bool        verboseFlag;    /* output to stdout */
#endif /* !SILENT */

    char*       dataDir;        /* user data dir */
    char*       shareDir;       /* system shared dir */

    sqlite3*    dataCnx;        /* personal database */
    sqlite3*    atlasCnx;       /* atlas database */

    Prefs*      prefs;          /* preferences */

    BTree*      aspectCollection;           /* aspects */
    BTree*      planetCollection;           /* planets */
    BTree*      aspectFilterCollection;     /* aspects filters */
    BTree*      aspectRestrCollection;      /* aspects restrictions */
    BTree*      orbFilterCollection;        /* orbs filters */
    BTree*      orbRestrCollection;         /* orbs restrictions */
    BTree*      planetFilterCollection;     /* planets filters */
    BTree*      profileCollection;          /* profiles */
    BTree*      contextCollection;          /* contexts */
    BTree*      horoscopeCollection;        /* horoscopes, by indexes */

    Vector*     chartCollection;            /* charts, by opening order */
    Vector*     sortedHoroscopes;           /* horoscopes, sorted by name */

};


void zodiacore_new( ZodiaCore** );

void zodiacore_delete( ZodiaCore**, Bool freeSwe );

void zodiacore_init_data_dir( ZodiaCore* );

void zodiacore_init_share_dir( ZodiaCore* );



#ifdef __cplusplus
}
#endif

#endif /* !ZODIACORE_CORE_H */
