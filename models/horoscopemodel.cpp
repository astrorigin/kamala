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

/** @file horoscopemodel.cpp
 */

#include "horoscopemodel.hpp"

#include <QAbstractTableModel>
#include <QModelIndex>
#include <QString>
#include <QVariant>

#include <KDebug>
#include <KIcon>
#include <KLocalizedString>

#include <core.h>

#include "../translation.hpp"

HoroscopeModel::HoroscopeModel( ZodiaCore* z, QObject* parent )
    : QAbstractTableModel( parent ),
    core( z ),
    rowIcon( KIcon( "system-file-manager" ) ) {}

QModelIndex HoroscopeModel::index( int row, int column, const QModelIndex& ) const
{
    if ( row < 0 || row >= core->sortedHoroscopes->len )
        return QModelIndex();
    return createIndex( row, column,
        (void*) ((Horoscope**)core->sortedHoroscopes->ptr)[row] );
}

QModelIndex HoroscopeModel::parent( const QModelIndex& ) const
{
    return QModelIndex();
}

int HoroscopeModel::rowCount( const QModelIndex& ) const
{
    return core->sortedHoroscopes->len;
}

int HoroscopeModel::columnCount( const QModelIndex& ) const
{
    return 8;
}

QVariant HoroscopeModel::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() || index.row() >= core->sortedHoroscopes->len )
        return QVariant();

    if ( role == Qt::DisplayRole )
    {
        Horoscope* h = (Horoscope*)index.internalPointer();

        switch ( index.column() )
        {
            case 0:
                return QString::fromUtf8( h->name->ptr );
            case 1:
                char buf[22];
                structtm_to_string( &h->datetime->dt, buf );
                return QString( buf );
            case 2:
                return QString::fromUtf8( h->location->ptr );
            case 3:
                return QString::fromUtf8( h->country->ptr );
            case 4:
                return GeoLatToString( h->latitude );
            case 5:
                return GeoLonToString( h->longitude );
            case 6:
                return GeoAltToString( h->altitude );
            case 7:
                return QString::fromUtf8( h->comments->ptr );
            default:
                return QVariant();
        }
    }
    else if ( role == Qt::DecorationRole )
    {
        if ( index.column() != 0 )
            return QVariant();
        return rowIcon;
    }
    else
    {
        return QVariant();
    }
}

QVariant HoroscopeModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if ( orientation == Qt::Horizontal )
    {
        if ( role != Qt::DisplayRole )
            return QVariant();

        switch ( section )
        {
            case 0: return i18nc( "@title:column Horoscope property", "Name" );
            case 1: return i18nc( "@title:column Horoscope property", "DateTime" );
            case 2: return i18nc( "@title:column Horoscope property", "Location" );
            case 3: return i18nc( "@title:column Horoscope property", "Country" );
            case 4: return i18nc( "@title:column Horoscope property", "Latitude" );
            case 5: return i18nc( "@title:column Horoscope property", "Longitude" );
            case 6: return i18nc( "@title:column Horoscope property", "Altitude" );
            case 7: return i18nc( "@title:column Horoscope property", "Comments" );
            default: return QString( "-?-" );
        }
    }
    else
    { // vertical
        return QVariant();
    }
}

void HoroscopeModel::horoscopeAboutToBeAdded( uint iRow )
{
    emit layoutAboutToBeChanged();
    beginInsertRows( QModelIndex(), iRow, iRow );
}

void HoroscopeModel::horoscopeAdded()
{
    endInsertRows();
    emit layoutChanged();
}

void HoroscopeModel::horoscopeAboutToBeRemoved( uint iRow )
{
    emit layoutAboutToBeChanged();
    beginRemoveRows( QModelIndex(), iRow, iRow );
}

void HoroscopeModel::horoscopeRemoved()
{
    endRemoveRows();
    emit layoutChanged();
}

void HoroscopeModel::horoscopeChanged( uint iRow )
{
    emit dataChanged( index( iRow, 0 ), index( iRow, 7 ) );
}
