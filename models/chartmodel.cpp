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

/** @file chartmodel.cpp
 */

#include "chartmodel.hpp"

#include <QAbstractTableModel>
#include <QBrush>
#include <QColor>
#include <QModelIndex>
#include <QString>
#include <QVariant>

#include <KDebug>
#include <KIcon>
#include <KLocalizedString>

#include <core.h>

ChartModel::ChartModel( ZodiaCore* z, QObject* parent )
    : QAbstractTableModel( parent ),
    core( z ),
    savedDataIcon( KIcon( "security-high" ) ),
    unsavedDataIcon( KIcon( "security-medium" ) ),
    modifiedDataIcon( KIcon( "security-low" ) ) {}

QModelIndex ChartModel::index( int row, int column, const QModelIndex& ) const
{
    if ( row < 0 || row >= core->chartCollection->len )
        return QModelIndex();
    return createIndex( row, column,
        (void*) ((Chart**)core->chartCollection->ptr)[ row ] );
}

QModelIndex ChartModel::parent( const QModelIndex& ) const
{
    return QModelIndex();
}

int ChartModel::rowCount( const QModelIndex& ) const
{
    return core->chartCollection->len;
}

int ChartModel::columnCount( const QModelIndex& ) const
{
    return 5;
}

QVariant ChartModel::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() || index.row() >= core->chartCollection->len )
        return QVariant();

    if ( role == Qt::DisplayRole )
    {
        const Chart* ch = (Chart*) index.internalPointer();
        const Wheel* wh = ch->wh1;

        switch ( index.column() )
        {
            case 0:
                return QString::fromUtf8( wh->horo->name->ptr );
            case 1:
                switch ( ch->type )
                {
                    case RadixChartType: return CHARTTYPE_RADIX_STR;
                    case ComparedChartType: return CHARTTYPE_COMPARED_STR;
                    default: return CHARTTYPE_INVALID_STR;
                }
            case 2:
                char buf[22];//localizeme
                structtm_to_string( &wh->horo->datetime->dt, buf );
                return QString( buf );
            case 3:
                return QString::fromUtf8( wh->horo->location->ptr );
            case 4:
                return QString::fromUtf8( wh->horo->country->ptr );
            default:
                return QVariant();
        }
    }
    else if ( role == Qt::DecorationRole )
    {
        if ( index.column() != 0 )
            return QVariant();

        const Chart* ch = (Chart*) index.internalPointer();
        const Wheel* wh = ch->wh1;

        if ( wh->horo->_idx > 0 )
        {
            if ( wh->horo->changed )
                return modifiedDataIcon;
            else
                return savedDataIcon;
        }
        else return unsavedDataIcon;
    }
    else return QVariant();
}

QVariant ChartModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if ( orientation == Qt::Horizontal )
    {
        if ( role != Qt::DisplayRole )
            return QVariant();

        switch ( section )
        {
            case 0: return i18nc( "@title:column Chart property", "Name" );
            case 1: return i18nc( "@title:column Chart property", "Type" );
            case 2: return i18nc( "@title:column Chart property", "DateTime" );
            case 3: return i18nc( "@title:column Chart property", "Location" );
            case 4: return i18nc( "@title:column Chart property", "Country" );
            default: return QString( "-?-" );
        }
    }
    else return QVariant();
}

void ChartModel::chartAboutToBeAdded( uint iRow )
{
    emit layoutAboutToBeChanged();
    beginInsertRows( QModelIndex(), iRow, iRow );
}

void ChartModel::chartAdded()
{
    endInsertRows();
    emit layoutChanged();
}

void ChartModel::chartAboutToBeRemoved( uint iRow )
{
    emit layoutAboutToBeChanged();
    beginRemoveRows( QModelIndex(), iRow, iRow );
}

void ChartModel::chartRemoved()
{
    endRemoveRows();
    emit layoutChanged();
}

void ChartModel::chartChanged( uint iRow )
{
    emit dataChanged( index( iRow, 0 ), index( iRow, 4 ) );
}
