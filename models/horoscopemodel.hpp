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

/** @file horoscopemodel.hpp
 */

#ifndef KAMALA_HOROSCOPEMODEL_HPP
#define KAMALA_HOROSCOPEMODEL_HPP

#include <QAbstractTableModel>
#include <QModelIndex>
class QObject;
class QVariant;
#include <KIcon>
#include "../kamala_export.hpp"

#include <core.h>

/** @class HoroscopeModel
 *  @brief Model of the horoscope database
 */
class KAMALA_EXPORT HoroscopeModel
    : public QAbstractTableModel
{
    Q_OBJECT

  public:

    /** @brief Pointer to core
     */
    ZodiaCore*      core;

    /** @brief Row header icon
     */
    const KIcon     rowIcon;

    /** @brief Constructor
     */
    explicit HoroscopeModel( ZodiaCore*, QObject* parent );

    /** @brief Get model index
     */
    QModelIndex index( int, int, const QModelIndex& parent=QModelIndex() ) const;

    /** @brief Get parent index
     */
    QModelIndex parent( const QModelIndex& ) const;

    /** @brief Get row count
     */
    int rowCount( const QModelIndex& parent=QModelIndex() ) const;

    /** @brief Get column count
     */
    int columnCount( const QModelIndex& parent=QModelIndex() ) const;

    /** @brief Get data
     */
    QVariant data( const QModelIndex&, int role ) const;

    /** @brief Get header data
     */
    QVariant headerData( int, Qt::Orientation, int role=Qt::DisplayRole ) const;


  public Q_SLOTS:

    /** @brief Horoscope to be added handler
     */
    void horoscopeAboutToBeAdded( uint iRow );

    /** @brief Horoscope added handler
     */
    void horoscopeAdded();

    /** @brief Horoscope to be removed handler
     */
    void horoscopeAboutToBeRemoved( uint iRow );

    /** @brief Horoscope removed handler
     */
    void horoscopeRemoved();

    /** @brief Horoscope changed handler
     */
    void horoscopeChanged( uint iRow );

};

#endif // KAMALA_HOROSCOPEMODEL_HPP
