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

/** @file kgeonamesdialog.cpp
 */

#include "kgeonamesdialog.hpp"

#include <QWidget>

#include <KComboBox>
#include <KDialog>
#include <KLocalizedString>
#include <KPushButton>

#include "kgeoname.hpp"
#include "kgeonamesquery.hpp"
#include "kgeonameswidget.hpp"

KGeoNamesDialog::KGeoNamesDialog( QWidget* parent )
    : KDialog( parent )
{
    setCaption( i18nc( "@title:window", "GeoNames.org Query" ) );
    setMinimumWidth( 600 );

    setButtons( KDialog::Reset|KDialog::Try|KDialog::Cancel|KDialog::Ok );
    setButtonText( KDialog::Try, i18nc( "@action:button Query GeoNames.org", "Search" ) );
    button( KDialog::Try )->setDefault( true );
    setEscapeButton( KDialog::Cancel );
    enableButton( KDialog::Reset, false );
    enableButton( KDialog::Try, false );
    enableButton( KDialog::Ok, false );

    _widget = new KGeoNamesWidget( this );
    setMainWidget( _widget );

    connect( this, SIGNAL( resetClicked() ), _widget, SLOT( resetClicked() ) );
    connect( this, SIGNAL( tryClicked() ), _widget, SLOT( tryClicked() ) );
    connect( this, SIGNAL( cancelClicked() ), this, SLOT( reject() ) );
    connect( this, SIGNAL( okClicked() ), this, SLOT( accept() ) );
}

KGeoName KGeoNamesDialog::exec()
{
    const int res = KDialog::exec();
    if ( res != KDialog::Accepted )
        return KGeoName(); // is invalid
    else
        return _widget->_query->resultsList()->at(
            _widget->_resultsBox->currentIndex() );
}
