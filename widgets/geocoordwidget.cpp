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

/** @file geocoordwidget.cpp
 */

#include "geocoordwidget.hpp"

#include <QHBoxLayout>
#include <QSizePolicy>
#include <QWidget>

#include <KComboBox>
#include <KDebug>
#include <KIntSpinBox>
#include <KLocalizedString>

#include <core.h>

/* Latitude & longitude widget */

GeoCoordWidget::GeoCoordWidget( double c, int maxdeg, QWidget* parent )
    : QWidget( parent )
{
    setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Fixed );

    QHBoxLayout* lyt = new QHBoxLayout( this );
    setLayout( lyt );

    degBox = new KIntSpinBox( this );
    degBox->setMinimum( 0 );
    degBox->setSuffix(
        i18nc( "@info/plain Degree symbol for latitude and longitude", "°" ) );
    degBox->setAccelerated( true );
    lyt->addWidget( degBox );
    connect( degBox, SIGNAL( valueChanged( int ) ),
        this, SLOT( checkCoord( int ) ) );

    dirBox = new KComboBox( false, this );
    lyt->addWidget( dirBox );
    connect( dirBox, SIGNAL( currentIndexChanged( int ) ),
        this, SLOT( emitValueChanged() ) );

    minBox = new KIntSpinBox( this );
    minBox->setMaximum( 59 );
    minBox->setMinimum( 0 );
    minBox->setSuffix(
        i18nc( "@info/plain Minutes symbol for latitude and longitudes", "'" ) );
    minBox->setAccelerated( true );
    lyt->addWidget( minBox );
    connect( minBox, SIGNAL( valueChanged( int ) ),
        this, SLOT( emitValueChanged() ) );

    secBox = new KIntSpinBox( this );
    secBox->setMaximum( 59 );
    secBox->setMinimum( 0 );
    secBox->setSuffix(
        i18nc( "@info/plain Seconds symbol for latitude and longitude", "\"" ) );
    secBox->setAccelerated( true );
    lyt->addWidget( secBox );
    connect( secBox, SIGNAL( valueChanged( int ) ),
        this, SLOT( emitValueChanged() ) );

    if ( maxdeg == 90 )
    { // latitude
        if ( !geolat_check( c ) )
        {
            kWarning() << "Invalid latitude" << c<<geolat_check( c );
            coord = 0;
        }
        else coord = c;
        degBox->setMaximum( 90 );
        dirBox->addItems( QStringList()
            << i18nc( "@item:inlistbox North abbreviated", "N" )
            << i18nc( "@item:inlistbox South abbreviated", "S" ) );
    }
    else if ( maxdeg == 180 )
    { // longitude
        if ( !geolon_check( c ) )
        {
            kWarning() << "Invalid longitude" << c;
            coord = 0;
        }
        else coord = c;
        degBox->setMaximum( 180 );
        dirBox->addItems( QStringList()
            << i18nc( "@item:inlistbox East abbreviated", "E" )
            << i18nc( "@item:inlistbox West abbreviated", "W" ) );
    }
    else kWarning() << "Invalid maximum degrees" << maxdeg;

    reset();
}

void GeoCoordWidget::reset()
{
    GeoCoord c;
    geocoord_from_double( &c, coord );

    degBox->setValue( c.deg );
    dirBox->setCurrentIndex( c.dir ? 0 : 1 );
    minBox->setValue( c.min );
    secBox->setValue( c.sec );

    emit valueChanged( coord );
}

double GeoCoordWidget::geoCoord() const
{
    return dirBox->currentIndex() == 0 ?
    ( degBox->value() + ( minBox->value() / 60.0 ) + ( secBox->value() / 3600.0 ) )
    : ( ( - degBox->value() ) - ( minBox->value() / 60.0 ) - ( secBox->value() / 3600.0 ) );
}

void GeoCoordWidget::setGeoCoord( double c )
{
    if ( degBox->maximum() == 90 && !geolat_check( c ) )
    {
        kWarning() << "Invalid latitude" << c;
        return;
    }
    else if ( !geolon_check( c ) )
    {
        kWarning() << "Invalid longitude" << c;
        return;
    }
    GeoCoord co;
    geocoord_from_double( &co, c );
    degBox->setValue( co.deg );
    dirBox->setCurrentIndex( co.dir ? 0 : 1 );
    minBox->setValue( co.min );
    secBox->setValue( co.sec );
    emit valueChanged( c );
}

void GeoCoordWidget::checkCoord( int deg )
{
    if ( degBox->maximum() == deg )
    {
        minBox->setValue( 0 );
        minBox->setDisabled( true );
        secBox->setValue( 0 );
        secBox->setDisabled( true );
    }
    else
    {
        minBox->setEnabled( true );
        secBox->setEnabled( true );
    }
    emitValueChanged();
}

/* Altitude widget */

AltitudeWidget::AltitudeWidget( GeoAlt alt, QWidget* parent )
    : KIntSpinBox( 0, 30000, 1, 0, parent ),
    _altitude( alt )
{
    setSuffix(
        i18nc( "@info/plain Meters abbreviated, in altitude widget", " m." ) );
    setAccelerated( true );
    reset();
}
