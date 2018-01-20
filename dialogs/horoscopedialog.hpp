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

/** @file horoscopedialog.hpp
 */

#ifndef KAMALA_HOROSCOPEDIALOG_HPP
#define KAMALA_HOROSCOPEDIALOG_HPP

class QCheckBox;
class QDateTimeEdit;
class QModelIndex;
class KComboBox;
#include <KDialog>
class KDoubleNumInput;
class KLineEdit;
class KTextEdit;
class KTimeZoneWidget;
#include "../kamala_export.hpp"

class AltitudeWidget;
class GeoCoordWidget;

#include <core.h>

/** @class HoroscopeDialog
 *  @brief Dialog to create, edit, and save horoscope data
 */
class KAMALA_EXPORT HoroscopeDialog
    : public KDialog
{
    Q_OBJECT

  public:

    /** @brief Constructor
     *  @param parent Parent widget
     *  @param horo Horoscope to edit, or null to create a new one
     *  @param doSave Do save horoscope if dialog is accepted
     */
    explicit HoroscopeDialog( QWidget* parent=0, Horoscope* horo=0, bool doSave=false );

    /** @brief Destructor
     */
    virtual ~HoroscopeDialog();

    /** @brief Get internal horoscope
     */
    Horoscope* horoscope() const { return _ref ? _ref : _horoscope; }

  public Q_SLOTS:

    /** @brief Reset dialog entries to horoscope initial values
     */
    void reset();

    /** @brief Accept dialog (and save horoscope as needed)
     */
    void accept();

    /** @brief Query GeoNames.org
     */
    void geoNamesQuery();

    /** @brief Utc offset checkbox signal handler
     */
    void utcOffsetChecked( int checkState );

    /** @brief Tab change handler
     *  Make the timezone widget scroll to the selected row.
     *  @param index Tab index
     */
    void currentTabChanged( int index );

    /** @brief TZ item click handler
     *  Update the UTC offset input line.
     *  @param index Item model index
     */
    void tzFileClicked( const QModelIndex& index );

  private:

    /** @brief Horoscope passed in ctor and kept for reference
     */
    Horoscope*      _ref;

    /** @brief Horoscope we can modify
     */
    Horoscope*      _horoscope;

    /** @brief Do save horoscope on dialog accept
     */
    bool            _doSave;

    /* Internal widgets */

    KLineEdit*          _nameEdit;
    QDateTimeEdit*      _dateTimeEdit;
    KComboBox*          _calendarBox;
    KLineEdit*          _locationEdit;
    KLineEdit*          _countryEdit;
    GeoCoordWidget*     _latitudeWidget;
    GeoCoordWidget*     _longitudeWidget;
    AltitudeWidget*     _altitudeWidget;
    KTimeZoneWidget*    _timezoneWidget;
    KComboBox*          _dstBox;
    QCheckBox*          _utcOffsetNeeded;
    KDoubleNumInput*    _utcOffsetInput;
    KTextEdit*          _commentsEdit;

};

#endif // KAMALA_HOROSCOPEDIALOG_HPP
