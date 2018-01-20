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

/** @file kgeonamesbutton.hpp
 */

#ifndef KGEONAMESBUTTON_HPP
#define KGEONAMESBUTTON_HPP

#include <QToolButton>
#include "kgeonames_export.hpp"

class QWidget;

/** @class KGeoNamesButton
 *  @brief A tool button representing GeoNames.org
 */
class GEONAMES_EXPORT KGeoNamesButton
    : public QToolButton
{
    Q_OBJECT

  public:

    /** @brief Constructor
     */
    explicit KGeoNamesButton( QWidget* parent=0 );

};

#endif // KGEONAMESBUTTON_HPP
