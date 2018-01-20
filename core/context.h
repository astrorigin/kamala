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

#ifndef ZODIACORE_CONTEXT_H
#define ZODIACORE_CONTEXT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sqlite.h"
#include "str.h"

typedef struct _context_t Context;

enum xCentric_t
{
    GeoCentric      = 0,
    TopoCentric,
    HelioCentric,
    BaryCentric
};

enum hSys_t
{
    EqualHouseSystem            = 'A',
    AlcabitiusHouseSystem       = 'B',
    CampanusHouseSystem         = 'C',
    HorizonAzimutHouseSystem    = 'H',
    KochHouseSystem             = 'K',
    PorphyryHouseSystem         = 'O',
    PlacidusHouseSystem         = 'P',
    RegiomontanusHouseSystem    = 'R',
    EqualVehlowHouseSystem      = 'V',
    EqualWholeSignHouseSystem   = 'W',
    AxialRotationHouseSystem    = 'X',
    GauquelinSectors            = 'G',
    KrusinskiPisaHouseSystem    = 'U',
    PolichPageHouseSystem       = 'T'
};

const int hSysList[] =
{
    EqualHouseSystem,
    AlcabitiusHouseSystem,
    CampanusHouseSystem,
    HorizonAzimutHouseSystem,
    KochHouseSystem,
    PorphyryHouseSystem,
    PlacidusHouseSystem,
    RegiomontanusHouseSystem,
    EqualVehlowHouseSystem,
    EqualWholeSignHouseSystem,
    AxialRotationHouseSystem,
    GauquelinSectors,
    KrusinskiPisaHouseSystem,
    PolichPageHouseSystem,
    -1
};

enum sidMode_t
{
    NoSiderealMode              = 256,
    FaganBradleySiderealMode    = 0,
    LahiriSiderealMode          = 1,
    DeluceSiderealMode          = 2,
    RamanSiderealMode           = 3,
    UshashashiSiderealMode      = 4,
    KrishnamurtiSiderealMode    = 5,
    DjwhalKhulSiderealMode      = 6,
    YukteshwarSiderealMode      = 7,
    JnBhasinSiderealMode        = 8,
    BabylKugler1SiderealMode    = 9,
    BabylKugler2SiderealMode    = 10,
    BabylKugler3SiderealMode    = 11,
    BabylHuberSiderealMode      = 12,
    BabylEtpscSiderealMode      = 13,
    Aldebaran15TauSiderealMode  = 14,
    HipparchosSiderealMode      = 15,
    SassanianSiderealMode       = 16,
    GalCent0SagSiderealMode     = 17,
    J2000SiderealMode           = 18,
    J1900SiderealMode           = 19,
    B1950SiderealMode           = 20,
    UserSiderealMode            = 255
};

const int sidModeList[] =
{
    NoSiderealMode,
    FaganBradleySiderealMode,
    LahiriSiderealMode,
    DeluceSiderealMode,
    RamanSiderealMode,
    UshashashiSiderealMode,
    KrishnamurtiSiderealMode,
    DjwhalKhulSiderealMode,
    YukteshwarSiderealMode,
    JnBhasinSiderealMode,
    BabylKugler1SiderealMode,
    BabylKugler2SiderealMode,
    BabylKugler3SiderealMode,
    BabylHuberSiderealMode,
    BabylEtpscSiderealMode,
    Aldebaran15TauSiderealMode,
    HipparchosSiderealMode,
    SassanianSiderealMode,
    GalCent0SagSiderealMode,
    J2000SiderealMode,
    J1900SiderealMode,
    B1950SiderealMode,
    UserSiderealMode,
    -1
};

struct _context_t
{
    idx_t   _idx;
    Str*    name;
    Str*    comments;

    int     xCentric;
    char    hSys;
    int     sidMode;
    double  sidT0;
    double  sidAyanT0;
    Bool    truePos;
};

void context_init( ZodiaCore* );

void context_fini( ZodiaCore* );

void context_new( Context** );

void context_delete( Context** );

void context_set_row( Context*, const sqlite_Stmt* );

void context_copy( Context*, const Context* other );

idx_t context_insert( ZodiaCore*, Context* );

idx_t context_update( ZodiaCore*, Context* );

idx_t context_erase( ZodiaCore*, Context* );

int context_swe_flags( const Context* );

Context* context_whose_name( const ZodiaCore*, const char* );

#ifdef __cplusplus
}
#endif

#endif /* !ZODIACORE_CONTEXT_H */
