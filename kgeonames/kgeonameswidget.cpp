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

/** @file kgeonameswidget.cpp
 */

#include "kgeonameswidget.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QList>
#include <QListIterator>
#include <QStringList>
#include <QWidget>

#include <KComboBox>
#include <KDialog>
#include <KLineEdit>
#include <KLocalizedString>
#include <KMessageBox>
#include <KProgressDialog>
#include <KPushButton>

#include "kgeoname.hpp"
#include "kgeonamesquery.hpp"
#include "kgeonamesdialog.hpp"

KGeoNamesWidget::KGeoNamesWidget( QWidget* parent )
    : QWidget( parent ),
    _query( 0 )
{
    QGridLayout* grid = new QGridLayout( this );
    setLayout( grid );

    QLabel* lbl = new QLabel( i18nc(
        "@label:textbox GeoNames search", "Search for" ), this );
    grid->addWidget( lbl, 0, 0 );
    _nameEdit = new KLineEdit( this );
    grid->addWidget( _nameEdit, 0, 1 );

    lbl = new QLabel( i18nc(
        "@label:listbox GeoNames.org results", "Results" ), this );
    grid->addWidget( lbl, 1, 0 );
    _resultsBox = new KComboBox( false, this );
    grid->addWidget( _resultsBox, 1, 1 );

    connect( _nameEdit, SIGNAL( textChanged( const QString& ) ),
        this, SLOT( nameChanged( const QString& ) ) );

    _nameEdit->setFocus( Qt::OtherFocusReason );
}

KGeoNamesWidget::~KGeoNamesWidget()
{
    if ( _query ) delete _query;
}

void KGeoNamesWidget::nameChanged( const QString& s ) const
{
    KGeoNamesDialog* parent = (KGeoNamesDialog*) parentWidget();
    if ( s.isEmpty() )
        parent->enableButton( KDialog::Try, false );
    else
        parent->enableButton( KDialog::Try, true );
}

void KGeoNamesWidget::resultsChanged() const
{
    KGeoNamesDialog* parent = (KGeoNamesDialog*) parentWidget();
    if ( !_resultsBox->count() )
    {
        parent->enableButton( KDialog::Reset, false );
        parent->enableButton( KDialog::Ok, false );
    }
    else
    {
        parent->enableButton( KDialog::Reset, true );
        parent->enableButton( KDialog::Ok, true );
    }
}

void KGeoNamesWidget::resetClicked()
{
    if ( _query )
    {
        delete _query;
        _query = 0;
    }
    _nameEdit->setText( "" ); // emits nameChanged
    _resultsBox->clear();
    resultsChanged(); // updates parent's buttons
    _nameEdit->setFocus( Qt::OtherFocusReason );
}

void KGeoNamesWidget::tryClicked()
{
    bool fail = true;

    KGeoNamesAsyncQuery* th = new KGeoNamesAsyncQuery( _nameEdit->text(), this );

    KProgressDialog* progDlg = new KProgressDialog( this,
        i18nc( "@title:window", "Querying GeoNames.org" ),
        i18nc( "@info", "Please wait while querying GeoNames.org..." ) );
    progDlg->setAutoClose( false );
    progDlg->progressBar()->setRange( 0, 0 );
    progDlg->setButtonText( i18nc(
        "@action:button Waiting for GeoNames.org search to finish", "Abort" ) );

    connect( th, SIGNAL( finished() ), progDlg, SLOT( accept() ) );
    connect( th, SIGNAL( terminated() ), progDlg, SLOT( reject() ) );
    connect( progDlg, SIGNAL( rejected() ), th, SLOT( quit() ) );

    progDlg->show();
    th->start();
    int ok = progDlg->exec();

    if ( ok == KDialog::Accepted )
    {
        QListIterator<KGeoName> iter( *th->resultsList() );
        KGeoName* n;
        QStringList strList;

        while ( iter.hasNext() )
        {
            n = (KGeoName*) &iter.next();
            strList << i18nc(
                "City short description {name, country, latitude, longitude, altitude, timezone}",
                "%1 (%2), lat=%3 lon=%4 alt=%5 tz=%6",
                n->name, n->country, n->latitude, n->longitude, n->elevation, n->timezone );
        }

        if ( strList.count() )
        {
            if ( _query )
                delete _query;
            _query = th;
            _resultsBox->clear();
            _resultsBox->addItems( strList );
            resultsChanged();
            fail = false;
        }
        else
        {
            delete th;
            KMessageBox::sorry( this, i18nc(
                "@info GeoNames.org fail", "Found no city matching \"%1\"",
                _nameEdit->text() ) );
            resetClicked(); // clear everything
        }
    }
    else delete th;

    delete progDlg;

    KGeoNamesDialog* parent = (KGeoNamesDialog*) parentWidget();
    if ( !fail ) // give focus back to parent's ok button
        parent->button( KDialog::Ok )->setFocus( Qt::OtherFocusReason );
    else // focus to name edit
        _nameEdit->setFocus( Qt::OtherFocusReason );
}
