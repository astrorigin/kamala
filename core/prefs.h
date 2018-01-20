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

#ifndef ZODIACORE_PREFS_H
#define ZODIACORE_PREFS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "context.h"
#include "geocoord.h"
#include "profile.h"
#include "str.h"

typedef struct _prefs_t Prefs;

struct _prefs_t
{
    Str*        ephePath;           /* ephemeris files path */

    Context*    context;            /* default context */
    Profile*    profile;            /* default profile */

    Str*        location;           /* current location */
    Str*        country;            /* country */
    GeoLat      latitude;           /* latitude */
    GeoLon      longitude;          /* longitude */
    GeoAlt      altitude;           /* altitude */
    char        timezone[36];       /* tz file */

    char        bgcolor[8];         /* chart background color */
    Str*        theme;              /* svg theme */
    Bool        openMaximized;      /* open charts windows maximized */
};

void prefs_init( ZodiaCore* );

void prefs_fini( ZodiaCore* );

void prefs_save( ZodiaCore* );

void prefs_set_ephe_path( ZodiaCore*, char* path );

#ifdef __cplusplus
}
#endif

#endif /* !ZODIACORE_PREFS_H */
