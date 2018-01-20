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

/** @file preferencesdialog.cpp
 */

#include "preferencesdialog.hpp"

#include <QCheckBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPointer>
#include <QStringList>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

#include <KComboBox>
#include <KDebug>
#include <KFile>
#include <KFileDialog>
#include <KIcon>
#include <KIntSpinBox>
#include <KLineEdit>
#include <KLocalizedString>
#include <KMessageBox>
#include <KPageDialog>
#include <KStandardDirs>
#include <KSystemTimeZones>
#include <KTimeZoneWidget>
#include <KUrl>
#include <KUrlRequester>

#include "../application.hpp"
#include "../translation.hpp"
#include "../kgeonames/kgeonamesbutton.hpp"
#include "../kgeonames/kgeonamesdialog.hpp"
#include "../widgets/geocoordwidget.hpp"

#include <core.h>

PreferencesWidget_1::PreferencesWidget_1( QWidget* parent )
    : QWidget( parent )
{
    QVBoxLayout* lyt = new QVBoxLayout( this );
    setLayout( lyt );

    QGroupBox* box = new QGroupBox( i18nc( "@title:group", "Paths" ), this );
    lyt->addWidget( box );

    QGridLayout* grid = new QGridLayout( box );
    box->setLayout( grid );

    QLabel* lbl = new QLabel(
        i18nc( "@label:chooser Swisseph directory path", "Ephemeris Files" ), this );
    grid->addWidget( lbl, 0, 0 );

    _ephePathEdit = new KUrlRequester( this );
    _ephePathEdit->setMode( KFile::Directory|KFile::ExistingOnly|KFile::LocalOnly );
    _ephePathEdit->button()->setToolTip(
        i18nc( "@info:tooltip", "Select swisseph directory" ) );
    grid->addWidget( _ephePathEdit, 0, 1 );

#if 0
    lbl = new QLabel(
        i18nc( "@label:chooser Script executed when app starts", "Startup script" ), this );
    grid->addWidget( lbl, 1, 0 );

    _initScriptEdit = new KUrlRequester( this );
    _initScriptEdit->setMode(KFile::File|KFile::ExistingOnly|KFile::LocalOnly);
#if KDE_IS_VERSION(4, 3, 0)
    m_initScriptEdit->setStartDir(KUrl::fromPath(
        KStandardDirs::locateLocal("data", "kamala/scripts/", true)));
#endif
    grid->addWidget(m_initScriptEdit, 1, 1);

    lbl = new QLabel(i18nc("@label:chooser Script executed when app finishes",
        "Exit script"), this);
    grid->addWidget(lbl, 2, 0);

    m_finiScriptEdit = new KUrlRequester(this);
    m_finiScriptEdit->setMode(KFile::File|KFile::ExistingOnly|KFile::LocalOnly);
#if KDE_IS_VERSION(4, 3, 0)
    m_finiScriptEdit->setStartDir(KUrl::fromPath(
        KStandardDirs::locateLocal("data", "kamala/scripts/", true)));
#endif
    grid->addWidget(m_finiScriptEdit, 2, 1);
#endif

    QGroupBox* settingsGrpBox = new QGroupBox(
        i18nc( "@title:group", "Settings" ), this );
    lyt->addWidget( settingsGrpBox );

    grid = new QGridLayout( settingsGrpBox );
    settingsGrpBox->setLayout( grid );

    lbl = new QLabel(
        i18nc( "@label:listbox", "Default Context" ), settingsGrpBox );
    grid->addWidget( lbl, 0, 0 );

    _contextsBox = new KComboBox( false, settingsGrpBox );
    grid->addWidget( _contextsBox, 0, 1 );//Qt::AlignLeft );

    QToolButton* contextManButton = new QToolButton( settingsGrpBox );
    contextManButton->setIcon( KIcon( "configure" ) );
    contextManButton->setToolTip( i18nc( "@info:tooltip", "Edit context..." ) );
    connect( contextManButton, SIGNAL( clicked() ), this, SLOT( contextManager() ) );
    grid->addWidget( contextManButton, 0, 2 );

    lbl = new QLabel(
        i18nc( "@label:listbox", "Default Profile" ), settingsGrpBox );
    grid->addWidget( lbl, 1, 0 );

    _profilesBox = new KComboBox( false, settingsGrpBox );
    grid->addWidget( _profilesBox, 1, 1 );//Qt::AlignLeft );

    QToolButton* settingsManButton = new QToolButton( settingsGrpBox );
    settingsManButton->setIcon( KIcon( "configure" ) );
    settingsManButton->setToolTip( i18nc( "@info:tooltip", "Edit profile..." ) );
    connect( settingsManButton, SIGNAL( clicked() ), this, SLOT( settingsManager() ) );
    grid->addWidget( settingsManButton, 1, 2 );
}

void PreferencesWidget_1::contextManager()
{/*
    Context* ct = ContextCollection::dbCollection()->context(
        m_contextsBox->currentText());
    Q_ASSERT(ct != 0);

    QPointer<ContextDialog> dlg = new ContextDialog(this, ct);
    int res = dlg->exec();
    if (res == ContextDialog::Accepted)
    {
        resetContexts();
    }
    delete dlg;*/
}

void PreferencesWidget_1::settingsManager()
{/*
    Settings *set = SettingsCollection::dbCollection()->settings(
        m_profilesBox->currentText());
    Q_ASSERT(set != 0);

    QPointer<SettingsDialog> dlg = new SettingsDialog(this, set);
    int res = dlg->exec();
    if (res == SettingsDialog::Accepted)
    {
        resetSettings();
    }
    delete dlg;*/
}

void PreferencesWidget_1::resetContexts()
{
    _contextsBox->clear();
    QStringList sl = KamalaApp->contextsStringList();
    _contextsBox->addItems( sl );
    _contextsBox->setCurrentIndex( sl.indexOf( QString::fromUtf8(
        KamalaApp->core->prefs->context->name->ptr ) ) );
}

void PreferencesWidget_1::resetProfiles()
{
    _profilesBox->clear();
    QStringList sl = KamalaApp->profilesStringList();
    _profilesBox->addItems( sl );
    _profilesBox->setCurrentIndex( sl.indexOf( QString::fromUtf8(
        KamalaApp->core->prefs->profile->name->ptr ) ) );
}


PreferencesWidget_2::PreferencesWidget_2( QWidget* parent )
    : QWidget( parent )
{
    QVBoxLayout* lyt = new QVBoxLayout( this );
    setLayout( lyt );

    QGroupBox* box = new QGroupBox(
        i18nc( "@title:tab Current location", "Your site" ), this );
    lyt->addWidget( box );

    QGridLayout* grid = new QGridLayout( box );
    box->setLayout( grid );

    KGeoNamesButton* geoNamesButton = new KGeoNamesButton( this );
    connect( geoNamesButton, SIGNAL( clicked() ), this, SLOT( geoNamesQuery() ) );
    grid->addWidget( geoNamesButton, 0, 0, 1, 2 );

    QLabel* lbl = new QLabel( i18nc( "@label:textbox",
        "<a href=\"http://www.astro.com/atlas\">Location</a>"), this );
    lbl->setToolTip( i18nc( "@info:tooltip", "Go to astro.com atlas database" ) );
    grid->addWidget( lbl, 1, 0 );
    _locationEdit = new KLineEdit( this );
    grid->addWidget( _locationEdit, 1, 1 );

    lbl = new QLabel( i18nc( "@label:textbox", "Country" ), this );
    grid->addWidget( lbl, 2, 0 );
    _countryEdit = new KLineEdit( this );
    grid->addWidget( _countryEdit );

    lbl = new QLabel( i18nc( "@label:chooser", "Timezone" ), this );
    grid->addWidget( lbl, 3, 0 );
    _timezoneBox = new KTimeZoneWidget( this, KSystemTimeZones::timeZones() );
    _timezoneBox->setSelectionMode( KTimeZoneWidget::SingleSelection );
    grid->addWidget( _timezoneBox, 3, 1 );

    lbl = new QLabel( i18nc( "@label:spinbox", "Latitude" ), this );
    grid->addWidget( lbl, 4, 0 );
    _latitudeEdit = GeoCoordWidget::latitudeWidget( 0, this );
    grid->addWidget( _latitudeEdit, 4, 1 );

    lbl = new QLabel( i18nc( "@label:spinbox", "Longitude" ), this );
    grid->addWidget( lbl, 5, 0 );
    _longitudeEdit = GeoCoordWidget::longitudeWidget( 0, this );
    grid->addWidget( _longitudeEdit, 5, 1 );

    lbl = new QLabel( i18nc( "@label:spinbox", "Altitude" ), this );
    grid->addWidget( lbl, 6, 0 );
    _altitudeBox = new AltitudeWidget( 0, this );
    grid->addWidget( _altitudeBox, 6, 1 );
}

void PreferencesWidget_2::geoNamesQuery()
{
    QPointer<KGeoNamesDialog> dlg = new KGeoNamesDialog( this );
    KGeoName res = dlg->exec();
    if ( res.isValid() )
    {
        _locationEdit->setText( res.name );
        _countryEdit->setText( res.country );
        _timezoneBox->clearSelection();
        _timezoneBox->setSelected( res.timezone, true );
        _latitudeEdit->setGeoCoord( res.latitude );
        _longitudeEdit->setGeoCoord( res.longitude );
        _altitudeBox->setAltitude( res.elevation );
    }
    delete dlg;
}

PreferencesWidget_3::PreferencesWidget_3( QWidget* parent )
    : QWidget( parent )
{
    QVBoxLayout* lyt = new QVBoxLayout( this );
    setLayout( lyt );

    QGroupBox* box = new QGroupBox( i18nc( "@title:group", "Interface" ), this );
    lyt->addWidget( box, 0, 0 );

    QGridLayout* grid = new QGridLayout( box );
    box->setLayout( grid );

    QLabel* lbl = new QLabel( i18nc( "@label:listbox", "Chart background color" ), this );
    grid->addWidget( lbl, 0, 0 );
    _bgColorBox = new KComboBox( false, this );
    _bgColorBox->addItems( BackgroundColors_StringList );
    grid->addWidget( _bgColorBox, 0, 1 );

    lbl = new QLabel( i18nc( "@label:listbox", "Icons theme" ), this );
    grid->addWidget( lbl, 1, 0 );
    _themeBox = new KComboBox( false, this );
    _themeBox->addItems( Themes_StringList );
    grid->addWidget( _themeBox, 1, 1 );

    _openMaximizedBox = new QCheckBox(
        i18nc( "@option:check", "Maximize subwindows" ), this );
    grid->addWidget( _openMaximizedBox, 2, 0, 1, 2 );
}

PreferencesDialog::PreferencesDialog( QWidget* parent )
    : KPageDialog( parent )
{
    setCaption( i18nc( "@title:window", "Preferences" ) );
    setSizeGripEnabled( true );

    setButtons( KPageDialog::Ok|KPageDialog::Cancel|KPageDialog::Reset );
    connect( this, SIGNAL( resetClicked() ), this, SLOT( reset() ) );
    setEscapeButton( KPageDialog::Cancel );

    _wdt1 = new PreferencesWidget_1( this );
    KPageWidgetItem* item1 = new KPageWidgetItem( _wdt1, "General" );
    item1->setHeader(
        i18nc( "@title:group General preferences", "General" ) );
    addPage( item1 );

    _wdt2 = new PreferencesWidget_2( this );
    KPageWidgetItem* item2 = new KPageWidgetItem( _wdt2, "Default chart" );
    item2->setHeader( i18nc(
        "@title:group Default chart preferences", "Default chart" ) );
    addPage( item2 );

    _wdt3 = new PreferencesWidget_3( this );
    KPageWidgetItem* item3 = new KPageWidgetItem( _wdt3, "Interface" );
    item3->setHeader(
        i18nc( "@title:group Interface preferences", "Interface" ) );
    addPage( item3 );

    reset();
}

void PreferencesDialog::reset()
{
    const Prefs* prefs = KamalaApp->core->prefs;

    _wdt1->_ephePathEdit->setUrl( KUrl( prefs->ephePath->ptr ) );
#if 0
    _wdt1->_initScriptEdit->setUrl(KUrl(prefs->initScript()));
    _wdt1->_finiScriptEdit->setUrl(KUrl(prefs->finiScript()));
#endif
    _wdt1->resetContexts();
    _wdt1->resetProfiles();

    _wdt2->_locationEdit->setText( QString::fromUtf8( prefs->location->ptr ) );
    _wdt2->_countryEdit->setText( QString::fromUtf8( prefs->country->ptr ) );
    _wdt2->_timezoneBox->setSelected( &prefs->timezone[1], true );
    _wdt2->_latitudeEdit->setGeoCoord( prefs->latitude );
    _wdt2->_longitudeEdit->setGeoCoord( prefs->longitude );
    _wdt2->_altitudeBox->setAltitude( prefs->altitude );

    _wdt3->_bgColorBox->setCurrentIndex(
        strequ( (char*) prefs->bgcolor, (char*) "#000000" ) ? 1 : 0 );
    _wdt3->_themeBox->setCurrentIndex(
        Themes_StringList.indexOf( QString::fromUtf8( prefs->theme->ptr ) ) );
    _wdt3->_openMaximizedBox->setChecked( prefs->openMaximized );
}

void PreferencesDialog::accept()
{
    if ( _wdt1->_ephePathEdit->text().isEmpty() )
    {
        KMessageBox::error( this,
            i18nc( "@info", "<warning>Missing swisseph files path !</warning>" ),
            i18nc( "@title:window", "Error" ) );
        _wdt1->_ephePathEdit->setFocus( Qt::OtherFocusReason );
        return;
    }
    if ( _wdt2->_timezoneBox->selection().isEmpty() )
    {
        KMessageBox::error( this,
            i18nc( "@info", "<warning>Missing timezone !</warning>" ),
            i18nc( "@title:window", "Error" ) );
        _wdt2->_timezoneBox->setFocus( Qt::OtherFocusReason );
        return;
    }

    Prefs* prefs = KamalaApp->core->prefs;

    prefs_set_ephe_path( KamalaApp->core,
        (char*)_wdt1->_ephePathEdit->text().toUtf8().constData() );
    prefs->context = context_whose_name( KamalaApp->core,
        _wdt1->_contextsBox->currentText().toUtf8().constData() );
    prefs->profile = profile_whose_name( KamalaApp->core,
        _wdt1->_profilesBox->currentText().toUtf8().constData() );

    str_set( prefs->location,
        (char*)_wdt2->_locationEdit->text().toUtf8().constData(), 0 );
    str_set( prefs->country,
        (char*)_wdt2->_countryEdit->text().toUtf8().constData(), 0 );
    sprintf( prefs->timezone, ":%s",
        _wdt2->_timezoneBox->selection().at( 0 ).toAscii().constData() );
    prefs->latitude = _wdt2->_latitudeEdit->geoCoord();
    prefs->longitude = _wdt2->_longitudeEdit->geoCoord();
    prefs->altitude = _wdt2->_altitudeBox->altitude();

    strcpy( prefs->bgcolor,
        _wdt3->_bgColorBox->currentIndex() == 0 ? "#ffffff" : "#000000" );
    str_set( prefs->theme, (char*)Themes_StringList.value(
        _wdt3->_themeBox->currentIndex() ).toUtf8().constData(), 0 );
    prefs->openMaximized = (Bool)_wdt3->_openMaximizedBox->isChecked();

    prefs_save( KamalaApp->core );

    KMessageBox::information( this,
        i18nc( "@info", "Preferences successfully saved." ),
        i18nc( "@title:window", "Preferences Saved" ),
        "PreferencesSuccessfullySaved" );

    done( KPageDialog::Accepted );
}
