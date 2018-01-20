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

#ifndef ZODIACORE_RAMAN_H
#define ZODIACORE_RAMAN_H

#ifdef __cplusplus
extern "C" {
#endif

#define long2rasi( longitude )      ((int) (swe_degnorm( longitude ) / 30.0))

#define rasi_norm( rasi )        ((rasi) < 0 ?\
        ((rasi) + (12 * (1 + (int) ((rasi) / -12)))) % 12 : (rasi) % 12)

int rasi_dif( int r1, int r2 );

int rasi_dif2( int r1, int r2 );

#ifdef __cplusplus
}
#endif

#endif /* !ZODIACORE_RAMAN_H */
