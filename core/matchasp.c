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

#include "matchasp.h"

/** @brief Aspect matching
**
** Check if the two given positions match the aspect within the given orb.
** This also calculates the difference between targeted aspect and distance
** between objects, and if aspect is applicating or separating, or stable due
** to equal speeds.
**
** @param pos0 First object longitude, in degrees [0;360[
** @param speed0 First object longitude speed, in degrees per day
** @param pos1 Second object longitude, in degrees [0;360[
** @param speed1 Second object longitude speed, in degrees per day
** @param aspect Aspect targeted, in degrees [0;360[
** @param orb Orb allowed, in degrees
** @param diffret Difference between aspect and objects distance, in degrees
** @param applic Aspect applicating [-1], separating [1], or stable [0]
** @param factor Aspect strength, compared to orb
** @return 0 if aspect match, else -1
*/
int match_aspect(double pos0, double speed0, double pos1, double speed1,
    double aspect, double orb, double *diffret, int *applic, double *factor)
{
    aspect = fabs(aspect);
    orb = fabs(orb);
    double diff = swe_difdegn(pos0, pos1);
    if (diff > aspect)
    {
        if (speed1 > speed0) { *applic = -1; }
        else if (speed1 < speed0) { *applic = 1; }
        else { *applic = 0; }
        *diffret = diff-aspect;
    }
    else if (diff < aspect)
    {
        if (speed1 > speed0) { *applic = 1; }
        else if (speed1 < speed0) { *applic = -1; }
        else { *applic = 0; }
        *diffret = aspect-diff;
    }
    else /* aspect is exact, cannot applic */
    {
        if (speed1 != speed0) { *applic = 1; }
        else { *applic = 0; }
        *diffret = 0;
        *factor = 0;
        return 0;
    }
    *factor = *diffret / orb;
    if (aspect-orb <= diff && diff <= aspect+orb) { return 0; } /* match */
    else { return -1; } /* no match */
}

/** @brief Aspect matching
**
** Same as match_aspect, but aspect in [0;180], instead of [0;360[
**
** @see match_aspect()
*/
int match_aspect2(double pos0, double speed0, double pos1, double speed1,
    double aspect, double orb, double *diffret, int *applic, double *factor)
{
    aspect = fabs(aspect);
    orb = fabs(orb);
    double difdeg2n = swe_difdeg2n(pos0, pos1);
    double diff = fabs(difdeg2n);
    if (difdeg2n > 0)
    {
        if (diff > aspect)
        {
            if (speed1 > speed0) { *applic = -1; }
            else if (speed1 < speed0) { *applic = 1; }
            else { *applic = 0; }
            *diffret = diff-aspect;
        }
        else if (diff < aspect)
        {
            if (speed1 > speed0) { *applic = 1; }
            else if (speed1 < speed0) { *applic = -1; }
            else { *applic = 0; }
            *diffret = aspect-diff;
        }
        else /* aspect exact */
        {
            if (speed1 != speed0) { *applic = 1; }
            else { *applic = 0; }
            *diffret = 0;
            *factor = 0;
            return 0;
        }
    }
    else if (difdeg2n > -180)
    {
        if (diff > aspect)
        {
            if (speed1 > speed0) { *applic = 1; }
            else if (speed1 < speed0) { *applic = -1; }
            else { *applic = 0; }
            *diffret = diff-aspect;
        }
        else if (diff < aspect)
        {
            if (speed1 > speed0) { *applic = -1; }
            else if (speed1 < speed0) { *applic = 1; }
            else { *applic = 0; }
            *diffret = aspect-diff;
        }
        else /* aspect exact */
        {
            if (speed1 != speed0) { *applic = 1; }
            else { *applic = 0; }
            *diffret = 0;
            *factor = 0;
            return 0;
        }
    }
    else /* exact conjunction or opposition */
    {
        if (speed1 != speed0) { *applic = 1; }
        else { *applic = 0; }
        *diffret = 0;
        *factor = 0;
        return 0;
    }
    *factor = *diffret / orb;
    if (aspect-orb <= diff && diff <= aspect+orb) { return 0; } /* match */
    else { return -1; } /* no match */
}

/** @brief Aspect matching
**
** Same as match_aspect, but with a different orb in case aspect is
** applying, separating, or stable.
**
** @see match_aspect()
*/
int match_aspect3(double pos0, double speed0, double pos1, double speed1,
    double aspect, double app_orb, double sep_orb, double def_orb,
    double *diffret, int *applic, double *factor)
{
    app_orb = fabs(app_orb);
    sep_orb = fabs(sep_orb);
    def_orb = fabs(def_orb);
    if (speed0 == speed1)
    { /* stable aspect */
        return match_aspect(pos0, speed0, pos1, speed1, aspect,
            def_orb, diffret, applic, factor);
    }
    if (app_orb == sep_orb)
    {
        return match_aspect(pos0, speed0, pos1, speed1, aspect, app_orb,
            diffret, applic, factor);
    }
    int i;
    if (app_orb > sep_orb)
    {
        i = match_aspect(pos0, speed0, pos1, speed1, aspect, app_orb,
            diffret, applic, factor);
        if (i == 0)
        {
            if (*applic == -1)
            {
                return 0;
            }
            else if (*diffret <= sep_orb)
            {
                *factor = *diffret / sep_orb;
                return 0;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            return -1;
        }
    }
    else
    {
        i = match_aspect(pos0, speed0, pos1, speed1, aspect, sep_orb,
            diffret, applic, factor);
        if (i == 0)
        {
            if (*applic == 1)
            {
                return 0;
            }
            else if (*diffret <= app_orb)
            {
                *factor = *diffret / app_orb;
                return 0;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            return -1;
        }
    }
}

/** @brief Aspect matching
**
** Same as match_aspect2, but with a different orb in case aspect is
** applying, separating, or stable.
**
** @see match_aspect2()
*/
int match_aspect4(double pos0, double speed0, double pos1, double speed1,
    double aspect, double app_orb, double sep_orb, double def_orb,
    double *diffret, int *applic, double *factor)
{
    app_orb = fabs(app_orb);
    sep_orb = fabs(sep_orb);
    def_orb = fabs(def_orb);
    if (speed0 == speed1)
    { /* stable aspect */
        return match_aspect2(pos0, speed0, pos1, speed1, aspect,
            def_orb, diffret, applic, factor);
    }
    if (app_orb == sep_orb)
    {
        return match_aspect2(pos0, speed0, pos1, speed1, aspect, app_orb,
            diffret, applic, factor);
    }
    int i;
    if (app_orb > sep_orb)
    {
        i = match_aspect2(pos0, speed0, pos1, speed1, aspect, app_orb,
            diffret, applic, factor);
        if (i == 0)
        {
            if (*applic == -1)
            {
                return 0;
            }
            else if (*diffret <= sep_orb)
            {
                *factor = *diffret / sep_orb;
                return 0;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            return -1;
        }
    }
    else
    {
        i = match_aspect2(pos0, speed0, pos1, speed1, aspect, sep_orb,
            diffret, applic, factor);
        if (i == 0)
        {
            if (*applic == 1)
            {
                return 0;
            }
            else if (*diffret <= app_orb)
            {
                *factor = *diffret / app_orb;
                return 0;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            return -1;
        }
    }
}
