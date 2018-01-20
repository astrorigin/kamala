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

#ifndef ZODIACORE_CHART_H
#define ZODIACORE_CHART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "context.h"
#include "wheel.h"

typedef struct _chart_t Chart;

enum chartType_t
{
    RadixChartType      = 0,
    ComparedChartType
};

struct _chart_t
{
    int         type;
    Context*    ctxt;

    Wheel*      wh1;
    Wheel*      wh2;

    Vector*     interAspects;
};

void chart_init( ZodiaCore* );

void chart_fini( ZodiaCore* );

uint chart_register( ZodiaCore*, Chart* );

void chart_unregister( ZodiaCore*, uint idx );

void chart_new( ZodiaCore*, Chart** );

void chart_delete( Chart** );

void chart_calc_interaspects( ZodiaCore*, Chart* );

void chart_now( const ZodiaCore*, Chart* );

void chart_clear( Chart* );

void chart_calc( ZodiaCore*, Chart* );

#ifdef __cplusplus
}
#endif

#endif /* !ZODIACORE_CHART_H */
