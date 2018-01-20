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

/** @file kgeonameswidget.hpp
 */

#ifndef KGEONAMESWIDGET_HPP
#define KGEONAMESWIDGET_HPP

#include <QWidget>
#include <QList>
class KLineEdit;
class KComboBox;
#include "kgeoname.hpp"
#include "kgeonames_export.hpp"
class KGeoNamesAsyncQuery;

/** @class KGeoNamesWidget
 *  @brief Widget exposing the search interface for GeoNames.org
 */
class GEONAMES_EXPORT KGeoNamesWidget
    : public QWidget
{
    friend class KGeoNamesDialog;

    Q_OBJECT

  public:

    /** @brief Pointer to the query object
     */
    KGeoNamesAsyncQuery*    _query;

    /** @brief Constructor
     */
    explicit KGeoNamesWidget( QWidget* parent );

    /** @brief Destructor
     */
    virtual ~KGeoNamesWidget();

  public Q_SLOTS:

    /** @brief Reset clicked handler
     */
    void resetClicked();

    /** @brief Try clicked handler
     *  Begin search.
     */
    void tryClicked();

    /** @brief Name change handler
     */
    void nameChanged( const QString& ) const;

    /** @brief Results changed handler
     */
    void resultsChanged() const;

  private:

    KLineEdit*      _nameEdit;
    KComboBox*      _resultsBox;

};

#endif // KGEONAMESWIDGET_HPP
