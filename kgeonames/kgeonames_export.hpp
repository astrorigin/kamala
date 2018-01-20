/*
    Kamala Astrology Software

    Copyright 2009 Stanislas Marquis <stnsls@gmail.com>

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

/** @file kgeonames_export.hpp
 */

#ifndef KGEONAMES_EXPORT_HPP
#define KGEONAMES_EXPORT_HPP

// needed for KDE_GEONAMES_EXPORT and KDE_IMPORT macros
#include <kdemacros.h>

#ifndef GEONAMES_EXPORT

#if defined(MAKE_LIB)
// We are building this library
#define GEONAMES_EXPORT KDE_EXPORT
#else
// We are using this library
#define GEONAMES_EXPORT KDE_IMPORT
#endif

#endif

#ifndef GEONAMES_EXPORT_DEPRECATED
#define GEONAMES_EXPORT_DEPRECATED KDE_DEPRECATED GEONAMES_EXPORT
#endif

#endif // KGEONAMES_EXPORT_HPP
