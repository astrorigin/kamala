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

/** @file horoscopeproxymodel.hpp
 */

#ifndef KAMALA_HOROSCOPEPROXYMODEL_HPP
#define KAMALA_HOROSCOPEPROXYMODEL_HPP

class QObject;
#include <QList>
#include <QModelIndex>
#include <QSortFilterProxyModel>
#include "../kamala_export.hpp"

class HoroscopeModel;

/** @class HoroscopeProxyModel
 *  @brief Proxy model of the horoscope database model, with a name filter
 */
class KAMALA_EXPORT HoroscopeProxyModel
    : public QSortFilterProxyModel
{
    Q_OBJECT

  public:

    /** @brief Constructor
     */
    explicit HoroscopeProxyModel( const HoroscopeModel*, QObject* parent );

    /** @brief Get parent index
     */
    QModelIndex parent( const QModelIndex& ) const { return QModelIndex(); }

    /** @brief Get a source index
     */
    QModelIndex mapToSource( const QModelIndex& ) const;

  public Q_SLOTS:

    /** @brief Build the pre-filtered index list
     */
    void buildIndexList();

    /** @brief Reset the pre-filtered index list when changing wildcard
     *  @param pattern String pattern
     */
    void setFilterWildcard( const QString& pattern );

  private:

    /** @brief Pre-filtered index list
     */
    QList<int>      _indexList;

};

#endif // KAMALA_HOROSCOPEPROXYMODEL_HPP
