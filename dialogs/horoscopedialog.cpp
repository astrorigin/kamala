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

/** @file horoscopedialog.cpp
 */

#include "horoscopedialog.hpp"

#include <QCheckBox>
#include <QDate>
#include <QDateTime>
#include <QDateTimeEdit>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QList>
#include <QModelIndex>
#include <QPointer>
#include <QTime>
#include <QTreeWidgetItem>
#include <QWidget>

#include <KComboBox>
#include <KDialog>
#include <KIcon>
#include <KLineEdit>
#include <KDebug>
#include <KDoubleNumInput>
#include <KLocalizedString>
#include <KMessageBox>
#include <KSystemTimeZones>
#include <KTabWidget>
#include <KTextEdit>
#include <KTimeZoneWidget>

#include "../application.hpp"
#include "../translation.hpp"
#include "../kgeonames/kgeonamesbutton.hpp"
#include "../kgeonames/kgeonamesdialog.hpp"
#include "../widgets/geocoordwidget.hpp"

#include <core.h>


QDateTime structtm_to_QDateTime( const struct tm & dt )
{
    return QDateTime( QDate( dt.tm_year + 1900, dt.tm_mon + 1, dt.tm_mday ),
        QTime( dt.tm_hour, dt.tm_min, dt.tm_sec ) );
}

void structtm_from_QDateTime( struct tm & dt, const QDateTime& qdt )
{
    const QDate date = qdt.date();
    const QTime time = qdt.time();
    dt.tm_year = date.year() - 1900;
    dt.tm_mon = date.month() - 1;
    dt.tm_mday = date.day();
    dt.tm_hour = time.hour();
    dt.tm_min = time.minute();
    dt.tm_sec = time.second();
}


HoroscopeDialog::HoroscopeDialog( QWidget* parent, Horoscope* horo, bool doSave )
    : KDialog( parent ),
    _ref( horo ),
    _horoscope( NULL ),
    _doSave( doSave )
{
    horoscope_new( KamalaApp->core, &_horoscope );

    if ( _ref )
    { // edit horoscope
        horoscope_copy( _horoscope, _ref );
        setCaption( i18nc( "@title:window",
            "Edit Horoscope <resource>%1</resource>", QString::fromUtf8( _ref->name->ptr ) ) );
    }
    else
    { // create new horoscope
        horoscope_now( KamalaApp->core, _horoscope );
        setCaption( i18nc( "@title:window", "New Horoscope" ) );
    }

    setSizeGripEnabled( true );

    setButtons( KDialog::Cancel|KDialog::Reset|KDialog::Ok );
    if ( _doSave )
        setButtonText( KDialog::Ok, i18nc( "@action:button", "Save" ) );
    else
        setButtonText( KDialog::Ok, i18nc( "@action:button", "Accept" ) );
    setButtonToolTip( KDialog::Ok, i18nc( "@info:tooltip", "Save horoscope" ) );
    setButtonToolTip( KDialog::Reset, i18nc( "@info:tooltip", "Reset horoscope" ) );
    connect( this, SIGNAL( cancelClicked() ), this, SLOT( close() ) );
    connect( this, SIGNAL( resetClicked() ), this, SLOT( reset() ) );

    KTabWidget* tabs = new KTabWidget( this );
    connect( tabs, SIGNAL( currentChanged( int ) ), this, SLOT( currentTabChanged( int ) ) );
    setMainWidget( tabs );

    /* meta info tab */
    QWidget* wdt = new QWidget( tabs );
    tabs->addTab( wdt, i18nc( "@title:tab Meta information", "Meta" ) );

    QGridLayout* grid = new QGridLayout( wdt );
    wdt->setLayout( grid );

    QLabel* lbl = new QLabel( i18nc( "@label:textbox Horoscope", "Name" ), wdt );
    grid->addWidget( lbl, 0, 0 );
    _nameEdit = new KLineEdit( wdt );
    grid->addWidget( _nameEdit, 0, 1 );

    lbl = new QLabel( i18nc( "@label:textbox", "Comments" ), wdt );
    grid->addWidget( lbl, 1, 0 );
    _commentsEdit = new KTextEdit( wdt );
    grid->addWidget( _commentsEdit, 1, 1 );

    /* time info tab */
    wdt = new QWidget( tabs );
    tabs->addTab( wdt, i18nc( "@title:tab Not space", "Time" ) );

    grid = new QGridLayout( wdt );
    wdt->setLayout( grid );

    lbl = new QLabel( i18nc( "@label:chooser", "Date & Time" ), wdt );
    grid->addWidget( lbl, 0, 0 );
    _dateTimeEdit = new QDateTimeEdit( wdt );
    _dateTimeEdit->setDisplayFormat( i18nc(
        "@info/plain Datetime display format: Year-Month-Day Hour:Min:Sec",
        "yyyy-MM-dd hh:mm:ss") );
    _dateTimeEdit->setCalendarPopup( true );
    _dateTimeEdit->setDateRange( QDate( -4713, 1, 2 ), QDate( 5400, 1, 1 ) );
    grid->addWidget( _dateTimeEdit, 0, 1 );

    lbl = new QLabel( i18nc( "@label:listbox", "Calendar" ), wdt );
    grid->addWidget( lbl, 1, 0 );
    _calendarBox = new KComboBox( false, wdt );
    _calendarBox->addItems( Calendars_StringList );
    grid->addWidget( _calendarBox, 1, 1 );

    /* location info tab */
    wdt = new QWidget( tabs );
    tabs->addTab( wdt, i18nc( "@title:tab Not time", "Space" ) );

    grid = new QGridLayout( wdt );
    wdt->setLayout( grid );

    KGeoNamesButton* geoNamesButton = new KGeoNamesButton( wdt );
    connect( geoNamesButton, SIGNAL( clicked() ), this, SLOT( geoNamesQuery() ) );
    grid->addWidget( geoNamesButton, 0, 0, 1, 2 );

    lbl = new QLabel( i18nc( "@label:textbox",
        "<a href=\"http://www.astro.com/atlas\">Location</a>"), wdt );
    lbl->setOpenExternalLinks( true );
    lbl->setToolTip( i18nc( "@info:tooltip", "Go to astro.com atlas database" ) );
    grid->addWidget( lbl, 1, 0 );
    _locationEdit = new KLineEdit( wdt );
    grid->addWidget( _locationEdit, 1, 1 );

    lbl = new QLabel( i18nc( "@label:textbox", "Country" ), wdt );
    grid->addWidget( lbl, 2, 0 );
    _countryEdit = new KLineEdit( wdt );
    grid->addWidget( _countryEdit, 2, 1 );

    lbl = new QLabel( i18nc( "@label:spinbox", "Latitude" ), wdt );
    grid->addWidget( lbl, 3, 0 );
    _latitudeWidget = GeoCoordWidget::latitudeWidget( 0, wdt );
    grid->addWidget( _latitudeWidget, 3, 1 );

    lbl = new QLabel( i18nc( "@label:spinbox", "Longitude" ), wdt );
    grid->addWidget( lbl, 4, 0 );
    _longitudeWidget = GeoCoordWidget::longitudeWidget( 0, wdt );
    grid->addWidget( _longitudeWidget, 4, 1 );

    lbl = new QLabel( i18nc( "@label:spinbox", "Altitude" ), wdt );
    grid->addWidget( lbl, 5, 0 );

    _altitudeWidget = new AltitudeWidget( 0, wdt );
    grid->addWidget( _altitudeWidget, 5, 1 );

    /* timezone info tab */
    wdt = new QWidget( tabs );
    tabs->addTab( wdt, i18nc( "@title:tab", "Timezone" ) );

    grid = new QGridLayout( wdt );
    wdt->setLayout( grid );

    lbl = new QLabel( i18nc( "@label:chooser", "Timezone" ), wdt );
    grid->addWidget( lbl, 0, 0 );
    _timezoneWidget = new KTimeZoneWidget( wdt, KSystemTimeZones::timeZones() );
    _timezoneWidget->setSelectionMode( KTimeZoneWidget::SingleSelection );
    connect( _timezoneWidget, SIGNAL( clicked( const QModelIndex& ) ),
        this, SLOT( tzFileClicked( const QModelIndex& ) ) );
    grid->addWidget( _timezoneWidget, 0, 1 );

    lbl = new QLabel( i18nc( "@label:listbox", "Daylight Savings Time" ), wdt );
    grid->addWidget( lbl, 1, 0 );
    _dstBox = new KComboBox( false, wdt );
    _dstBox->addItems( DST_StringList );
    grid->addWidget( _dstBox, 1, 1 );

    _utcOffsetNeeded = new QCheckBox( i18nc( "@label:spinbox", "UTC Offset" ), wdt );
    _utcOffsetNeeded->setToolTip(
        i18nc( "@info:tooltip UTC offset units", "hours to UTC" ) );
    connect( _utcOffsetNeeded, SIGNAL( stateChanged( int ) ),
        this, SLOT( utcOffsetChecked( int ) ) );
    grid->addWidget( _utcOffsetNeeded, 2, 0 );
    _utcOffsetInput = new KDoubleNumInput( -13, 13, 0, wdt, 0.5, 1 );
    _utcOffsetInput->setSuffix(
        i18nc( "@info/plain Hours suffix for UTC offset", " h." ) );
    grid->addWidget( _utcOffsetInput, 2, 1 );

    reset();
    _nameEdit->setFocus( Qt::OtherFocusReason );
}

HoroscopeDialog::~HoroscopeDialog()
{
    if ( _ref || !_horoscope->_idx )
        horoscope_delete( &_horoscope );
}

void HoroscopeDialog::reset()
{
    const Horoscope* h = _ref ? _ref : _horoscope;

    _nameEdit->setText( QString::fromUtf8( h->name->ptr ) );
    _commentsEdit->setPlainText( QString::fromUtf8( h->comments->ptr ) );
    _dateTimeEdit->setDateTime( structtm_to_QDateTime( h->datetime->dt ) );
    _calendarBox->setCurrentIndex( h->datetime->cal );
    _locationEdit->setText( QString::fromUtf8( h->location->ptr ) );
    _countryEdit->setText( QString::fromUtf8( h->country->ptr ) );
    _latitudeWidget->setGeoCoord( h->latitude );
    _longitudeWidget->setGeoCoord( h->longitude );
    _altitudeWidget->setAltitude( h->altitude );

    _timezoneWidget->clearSelection();
    if ( h->datetime->tzfile[0] != '\0' )
    {
        _timezoneWidget->setSelected( &h->datetime->tzfile[1], true );
        utcOffsetChecked( 0 );
    }
    else utcOffsetChecked( 2 );

    _dstBox->setCurrentIndex( h->datetime->isdst + 1 );
    _utcOffsetInput->setValue( h->datetime->utcoffset / 3600 );
}

void HoroscopeDialog::geoNamesQuery()
{
    QPointer<KGeoNamesDialog> dlg = new KGeoNamesDialog( this );
    const KGeoName res = dlg->exec();
    if ( res.isValid() )
    {
        _locationEdit->setText( res.name );
        _countryEdit->setText( res.country );
        _timezoneWidget->clearSelection();
        _timezoneWidget->setSelected( res.timezone, true );
        _latitudeWidget->setGeoCoord( res.latitude );
        _longitudeWidget->setGeoCoord( res.longitude );
        _altitudeWidget->setAltitude( res.elevation );
    }
    delete dlg;
}

void HoroscopeDialog::utcOffsetChecked( int state )
{
    if ( state == Qt::Checked )
    {
        _timezoneWidget->setEnabled( false );
        _dstBox->setEnabled( false );
        _utcOffsetInput->setEnabled( true );
    }
    else
    {
        _timezoneWidget->setEnabled( true );
        _dstBox->setEnabled( true );
        _utcOffsetInput->setEnabled( false );
    }
}

void HoroscopeDialog::currentTabChanged( int index )
{
    if ( index != 3 ) return;

    // ensure selected timezone is visible
    const QList<QTreeWidgetItem*> selected = _timezoneWidget->selectedItems();
    if ( !selected.isEmpty() )
    {
        _timezoneWidget->setCurrentItem( selected.at( 0 ) );
        _timezoneWidget->scrollTo( _timezoneWidget->currentIndex() );
    }
}

void HoroscopeDialog::tzFileClicked( const QModelIndex& index )
{
    if ( !index.isValid() ) return;

    assert( !_timezoneWidget->selection().isEmpty() );

    char buf[50];
    sprintf( buf, ":%s",
        _timezoneWidget->selection().at( 0 ).toAscii().constData() );
    const long utcOffset = timezone_offset( buf );
    _utcOffsetInput->setValue( utcOffset / 3600 );
}

void HoroscopeDialog::accept()
{
    if ( _nameEdit->text().isEmpty() )
    {
        KMessageBox::error( this,
            i18nc( "@info", "<warning>Missing name !</warning>" ),
            i18nc( "@title:window", "Error" ) );
        _nameEdit->setFocus( Qt::OtherFocusReason );
        return;
    }

    str_set( _horoscope->name, (char*)_nameEdit->text().toUtf8().constData(), 0 );
    str_set( _horoscope->comments, (char*)_commentsEdit->toPlainText().toUtf8().constData(), 0 );
    _horoscope->datetime->cal = _calendarBox->currentIndex();
    str_set( _horoscope->location, (char*)_locationEdit->text().toUtf8().constData(), 0 );
    str_set( _horoscope->country, (char*)_countryEdit->text().toUtf8().constData(), 0 );
    _horoscope->latitude = _latitudeWidget->geoCoord();
    _horoscope->longitude = _longitudeWidget->geoCoord();
    _horoscope->altitude = _altitudeWidget->altitude();

    if ( !_utcOffsetNeeded->isChecked() )
    {
        if ( _timezoneWidget->selection().isEmpty() )
        {
            KMessageBox::error( this,
                i18nc( "@info", "<warning>Missing timezone !</warning>" ),
                i18nc( "@title:window", "Error" ) );
            _timezoneWidget->setFocus( Qt::OtherFocusReason );
            return;
        }
        datetime_set( _horoscope->datetime,
            _dateTimeEdit->dateTime().toString( "yyyy/MM/dd hh:mm:ss" ).toAscii().constData(),
            ( QString( ":" ) + _timezoneWidget->selection().at( 0 ) ).toAscii().constData(),
            _dstBox->currentIndex() - 1,
            _utcOffsetInput->value() * 3600 );//todo:test for needed dst
    }
    else
    {
        structtm_from_QDateTime( _horoscope->datetime->dt, _dateTimeEdit->dateTime() );
        strcpy( _horoscope->datetime->tzfile, "" );
        _horoscope->datetime->isdst = -1;
        _horoscope->datetime->utcoffset = _utcOffsetInput->value() * 3600;
        datetime_make( _horoscope->datetime );
    }

    if ( !_doSave )
    { // only editing, just modify the ref
        assert( _ref );
        if ( !horoscope_equals( _ref, _horoscope ) )
        {
            horoscope_copy( _ref, _horoscope );
            _ref->changed = True;
        }
        KDialog::done( KDialog::Accepted );
        return;
    }

    const idx_t res = _horoscope->_idx ?
        horoscope_update( KamalaApp->core, _horoscope )
        : horoscope_insert( KamalaApp->core, _horoscope );

    if ( res )
    {
        if ( _ref )
            horoscope_copy( _ref, _horoscope );

        KMessageBox::information( this,
            i18nc( "@info", "Horoscope successfully saved as <resource>%1</resource>.",
                QString::fromUtf8( _horoscope->name->ptr ) ),
            i18nc( "@title:window", "Horoscope Saved" ),
            "HoroscopeSuccessfullySaved" );
        KDialog::done( KDialog::Accepted );
    }
    else
    {
        KMessageBox::error( this,
            i18nc( "@info", "<warning>Horoscope <resource>%1</resource> already "
                   "exists !</warning>", QString::fromUtf8( _horoscope->name->ptr ) ),
            i18nc( "@title:window", "Error" ) );

        if ( _ref )
            horoscope_copy( _horoscope, _ref );

        _nameEdit->setFocus( Qt::OtherFocusReason );
        return;
    }
}
