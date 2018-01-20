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

/** @file horoscopeproxymodel.cpp
 */

#include "horoscopeproxymodel.hpp"

#include <QAbstractItemModel>
#include <QList>
#include <QModelIndex>
#include <QSortFilterProxyModel>

#include <KDebug>

#include "horoscopemodel.hpp"

HoroscopeProxyModel::HoroscopeProxyModel( const HoroscopeModel* model, QObject* parent )
    : QSortFilterProxyModel( parent )
{
    setSourceModel( (QAbstractItemModel*) model );
    setFilterWildcard( "" );
    setFilterKeyColumn( 0 );
    setDynamicSortFilter( true );

    connect( model, SIGNAL( dataChanged( const QModelIndex&, const QModelIndex& ) ),
        this, SLOT( buildIndexList() ) );
    connect( model, SIGNAL( layoutChanged() ), this, SLOT( buildIndexList() ) );
}

QModelIndex HoroscopeProxyModel::mapToSource( const QModelIndex& index ) const
{
    if ( !index.isValid() || index.row() >= _indexList.count() )
        return QModelIndex();
    return sourceModel()->index( _indexList.at( index.row() ), index.column() );
}

void HoroscopeProxyModel::buildIndexList()
{ // todo: dont rebuild when data changed is not relevant to the horoscope name
    _indexList.clear();
    const HoroscopeModel* src = (HoroscopeModel*) sourceModel();
    const uint srcCount = src->core->sortedHoroscopes->len;
    uint i = 0;
    for ( ; i < srcCount; ++i )
    {
        if ( filterAcceptsRow( i, QModelIndex() ) )
            _indexList.append( src->index( i, 0 ).row() );
    }
    invalidateFilter();
}

void HoroscopeProxyModel::setFilterWildcard( const QString& pattern )
{
    QSortFilterProxyModel::setFilterWildcard( pattern );
    buildIndexList();
}
