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

/** @file kgeoname.hpp
 */

#ifndef KGEONAME_HPP
#define KGEONAME_HPP

#include <QObject>
#include <QString>
#include "kgeonames_export.hpp"

/** @class KGeoName
 *  @brief A "row" of GeoNames.org data (for Kamala)
 */
class GEONAMES_EXPORT KGeoName
    : public QObject
{
    Q_OBJECT

  public:

    /** @brief Name
     */
    QString     name;

    /** @brief Country
     */
    QString     country;

    /** @brief Latitude
     */
    double      latitude;

    /** @brief Longitude
     */
    double      longitude;

    /** @brief Elevation
     */
    int         elevation;

    /** @brief Timezone
     */
    QString     timezone;

    /** @brief Constructor
     */
    explicit KGeoName( QObject* parent=0 );

    /** @brief Copy constructor
     */
    KGeoName( const KGeoName& other );

    /** @brief Assignment operator
     */
    KGeoName& operator = ( const KGeoName& other );

    /** @brief Check if data is valid
     */
    bool isValid() const { return !name.isEmpty(); }

};

#endif // KGEONAME_HPP
