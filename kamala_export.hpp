/*
    Kamala Astrology Software

    Copyright 2009 Stanislas Marquis <smarquis@chaosorigin.com>

    Kamala is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of 
    the License, or (at your option) any later version.

    Kamala is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Kamala.  If not, see <http://www.gnu.org/licenses/>.
*/

/** @file kamala_export.hpp
 */

#ifndef KAMALA_EXPORT_HPP
#define KAMALA_EXPORT_HPP

// needed for KDE_KAMALA_EXPORT and KDE_IMPORT macros
#include <kdemacros.h>

#ifndef KAMALA_EXPORT

#if defined(MAKE_LIB)
// We are building this library
#define KAMALA_EXPORT KDE_EXPORT
#else
// We are using this library
#define KAMALA_EXPORT KDE_IMPORT
#endif

#endif

#ifndef KAMALA_EXPORT_DEPRECATED
#define KAMALA_EXPORT_DEPRECATED KDE_DEPRECATED KAMALA_EXPORT
#endif

#endif // KAMALA_EXPORT_HPP
