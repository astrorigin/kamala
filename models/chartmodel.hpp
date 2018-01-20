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

/** @file chartmodel.hpp
 */

#ifndef KAMALA_CHARTMODEL_HPP
#define KAMALA_CHARTMODEL_HPP

#include <QAbstractTableModel>
#include <QModelIndex>
class QObject;
class QVariant;
#include <KIcon>
#include <KLocalizedString>
#include "../kamala_export.hpp"

#include <core.h>

const QString CHARTTYPE_RADIX_STR       = i18nc( "@item Chart type", "Radix" );
const QString CHARTTYPE_COMPARED_STR    = i18nc( "@item Chart type", "Comparison" );
const QString CHARTTYPE_INVALID_STR     = i18nc( "@item Chart type", "Invalid" );

/** @class ChartModel
 *  @brief Model of currently opened charts
 */
class KAMALA_EXPORT ChartModel
    : public QAbstractTableModel
{
    Q_OBJECT

  public:

    /** @brief Pointer to core
     */
    ZodiaCore*      core;

    /** @brief Icon for saved and unmodified data
     */
    const KIcon     savedDataIcon;

    /** @brief Icon for unsaved data
     */
    const KIcon     unsavedDataIcon;

    /** @brief Icon for saved but modified data
     */
    const KIcon     modifiedDataIcon;

    /** @brief Constructor
     */
    explicit ChartModel( ZodiaCore*, QObject* parent );

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
    QVariant data( const QModelIndex&, int ) const;

    /** @brief Get header data
     */
    QVariant headerData( int, Qt::Orientation, int role=Qt::DisplayRole ) const;

  public Q_SLOTS:

    /** @brief Chart to be added handler
     */
    void chartAboutToBeAdded( uint iRow );

    /** @brief Chart added handler
     */
    void chartAdded();

    /** @brief Chart to be removed handler
     */
    void chartAboutToBeRemoved( uint iRow );

    /** @brief Chart removed handler
     */
    void chartRemoved();

    /** @brief Chart changed handler
     */
    void chartChanged( uint iRow );

};

#endif // KAMALA_CHARTMODEL_HPP
