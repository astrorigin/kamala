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

/** @file geocoordwidget.hpp
 */

#ifndef KAMALA_GEOCOORDWIDGET_HPP
#define KAMALA_GEOCOORDWIDGET_HPP

#include <QWidget>
#include <KIntSpinBox>
class KComboBox;
#include "../kamala_export.hpp"

#include <core.h>

/** @class GeoCoordWidget
 *  @brief Widget for latitude or longitude
 */
class KAMALA_EXPORT GeoCoordWidget
    : public QWidget
{
    Q_OBJECT

  public:

    /** @brief Static constructor for latitude widgets
     *  @param lat Initial latitude
     *  @param parent Parent widget
     */
    static GeoCoordWidget* latitudeWidget( GeoLat lat, QWidget* parent=0 )
    {
        return new GeoCoordWidget( lat, 90, parent );
    }

    /** @brief Static constructor for longitude widgets
     *  @param lon Initial longitude
     *  @param parent Parent widget
     */
    static GeoCoordWidget* longitudeWidget( GeoLon lon, QWidget* parent=0 )
    {
        return new GeoCoordWidget( lon, 180, parent );
    }

    /** @brief Get widget current geocoord value
     */
    double geoCoord() const;

    /** @brief Set widget current geocoord value
     *  @param coord The current value
     */
    void setGeoCoord( double coord );

  public Q_SLOTS:

    /** @brief Reset the widget current geocoord value to initial value
     */
    void reset();

  Q_SIGNALS:

    /** @brief Signal value change
     *  @param val Latitude or longitude value
     */
    void valueChanged( double val );

  private Q_SLOTS:

    /** @brief Check values when degree maximum limit is reached
     *  @param deg Degrees spinbox value
     */
    void checkCoord( int deg );

    /** @brief Emit valueChanged
     */
    void emitValueChanged() { emit valueChanged( geoCoord() ); }

  private:

    /** @brief Private constructor
     *  @param coord Latitude or longitude initial value
     *  @param maxdeg Maximum degrees, 90 for latitude, 180 for longitude
     *  @param parent Parent widget
     */
    explicit GeoCoordWidget( double coord, int maxdeg, QWidget* parent=0 );

    /** @brief Value kept for reference
     */
    double          coord;

    /** @brief Degrees box
     */
    KIntSpinBox*    degBox;

    /** @brief Direction box
     */
    KComboBox*      dirBox;

    /** @brief Minutes box
     */
    KIntSpinBox*    minBox;

    /** @brief Seconds box
     */
    KIntSpinBox*    secBox;

};


/** @class AltitudeWidget
 *  @brief Widget for altitude
 *  Reminder: altitudes may not be less than 0 (swisseph limitation).
 */
class KAMALA_EXPORT AltitudeWidget
    : public KIntSpinBox
{
    Q_OBJECT

  public:

    /** @brief Constructor
     *  @param alt Initial altitude value
     */
    explicit AltitudeWidget( GeoAlt alt=0, QWidget* parent=0 );

    /** @brief Get widget current altitude value
     */
    GeoAlt altitude() const { return value(); }

    /** @brief Set widget current altitude value
     *  @param alt Altitude value
     */
    void setAltitude( GeoAlt alt ) { setValue( alt ); }

  public Q_SLOTS:

    /** @brief Reset widget to initial value
     */
    void reset() { setValue( _altitude ); }

  private:

    /** @brief Value kept for reference
     */
    GeoAlt      _altitude;

};

#endif // KAMALA_GEOCOORDWIDGET_HPP
