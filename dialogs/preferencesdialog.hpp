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

/** @file preferencesdialog.hpp
 */

#ifndef KAMALA_PREFERENCESDIALOG_HPP
#define KAMALA_PREFERENCESDIALOG_HPP

class QCheckBox;
#include <QWidget>
class KComboBox;
class KIntSpinBox;
class KLineEdit;
#include <KPageDialog>
class KTimeZoneWidget;
class KUrlRequester;
#include "../kamala_export.hpp"

class AltitudeWidget;
class GeoCoordWidget;


/** @class PreferencesWidget_1
 *  @brief First tab of the preferences dialog
 *  Contains entries for the epheemris files path, the default context
 *  and default profile.
 *  @see PreferencesWidget
 */
class KAMALA_EXPORT PreferencesWidget_1
    : public QWidget
{
    Q_OBJECT

  public:

    /** @brief Constructor
     *  @param parent Parent widget
     */
    explicit PreferencesWidget_1( QWidget* parent );

    /** @brief Pointer to ephemeris files path requester
     */
    KUrlRequester*      _ephePathEdit;

    /** @brief Pointer to default context combo box
     */
    KComboBox*      _contextsBox;

    /** @brief Pointer to default profile combo box
     */
    KComboBox*      _profilesBox;

  public Q_SLOTS:

    /** @brief Launch context manager
     */
    void contextManager();

    /** @brief Reset list of contexts
     */
    void resetContexts();

    /** @brief Launch profile manager
     */
    void settingsManager();

    /** @brief Reset list of profiles
     */
    void resetProfiles();

};


/** @class PreferencesWidget_2
 *  @brief Second tab of the preferences dialog
 *  Contains information about the current location.
 *  @see PreferencesWidget
 */
class KAMALA_EXPORT PreferencesWidget_2
    : public QWidget
{
    Q_OBJECT

  public:

    /** @brief Constructor
     *  @param parent Parent widget
     */
    explicit PreferencesWidget_2( QWidget* parent );

    /** @brief Pointer to location line edit
     */
    KLineEdit*      _locationEdit;

    /** @brief Pointer to country line edit
     */
    KLineEdit*      _countryEdit;

    /** @brief Pointer to timezone widget
     */
    KTimeZoneWidget*    _timezoneBox;

    /** @brief Pointer to latitude widget
     */
    GeoCoordWidget*     _latitudeEdit;

    /** @brief Pointer to longitude widget
     */
    GeoCoordWidget*     _longitudeEdit;

    /** @brief Pointer to altitude widget
     */
    AltitudeWidget*     _altitudeBox;

  public Q_SLOTS:

    /** @brief Query GeoNames.org
     */
    void geoNamesQuery();

};


/** @class PreferencesWidget_3
 *  @brief Third tab of the preferences dialog
 *  Contains the graphical options, colors, etc.
 *  @see PreferencesWidget
 */
class KAMALA_EXPORT PreferencesWidget_3
    : public QWidget
{
    Q_OBJECT

  public:

    /** @brief Constructor
     *  @param parent Parent widget
     */
    explicit PreferencesWidget_3( QWidget* parent );

    /** @brief Background color for charts
     */
    KComboBox*      _bgColorBox;

    /** @brief SVG theme for charts
     */
    KComboBox*      _themeBox;

    /** @brief Open subwindows maximized option
     */
    QCheckBox*      _openMaximizedBox;

};


/** @class PreferencesDialog
 *  @brief Dialog to view, edit, and save preferences
 *  @see PreferencesWidget_1
 *  @see PreferencesWidget_2
 *  @see PreferencesWidget_3
 */
class KAMALA_EXPORT PreferencesDialog
    : public KPageDialog
{
    Q_OBJECT

  public:

    /** @brief Constructor
     *  @param parent Parent widget
     */
    explicit PreferencesDialog( QWidget* parent );

  public Q_SLOTS:

    /** @brief Reset all dialog entries
     */
    void reset();

    /** @brief Save preferences
     */
    void accept();

  private:

    /* Internal widgets */

    PreferencesWidget_1*        _wdt1;
    PreferencesWidget_2*        _wdt2;
    PreferencesWidget_3*        _wdt3;

};

#endif // KAMALA_PREFERENCESDIALOG_HPP
