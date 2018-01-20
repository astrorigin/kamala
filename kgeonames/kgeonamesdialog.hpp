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

/** @file kgeonamesdialog.hpp
 */

#ifndef KGEONAMESDIALOG_HPP
#define KGEONAMESDIALOG_HPP

class QWidget;
#include <KDialog>
#include "kgeoname.hpp"
#include "kgeonameswidget.hpp"
#include "kgeonames_export.hpp"

/** @class KGeoNamesDialog
 *  @brief Dialog to query GeoNames.org
 */
class GEONAMES_EXPORT KGeoNamesDialog
    : public KDialog
{
    Q_OBJECT

  public:

    /** @brief Constructor
     */
    explicit KGeoNamesDialog( QWidget* parent=0 );

  public Q_SLOTS:

    /** @brief Execute the dialog
     *  @return GeoName object chosen (or invalid)
     */
    KGeoName exec();

  private:

    /** @brief Internal widget
     */
    KGeoNamesWidget*        _widget;

};

#endif // KGEONAMESDIALOG_HPP
