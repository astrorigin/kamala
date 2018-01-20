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

/** @file searchwidget.cpp
 */

#include "searchwidget.hpp"

#include <QDrag>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QGridLayout>
#include <QMimeData>
#include <QModelIndex>
#include <QMouseEvent>
#include <QPointer>
#include <QToolBar>
#include <QWidget>

#include <KActionCollection>
#include <KDebug>
#include <KLineEdit>
#include <KLocalizedString>

#include "../application.hpp"
#include "../mainwindow.hpp"
#include "../models/horoscopeproxymodel.hpp"
#include "../views/horoscopeview.hpp"


SearchWidget::SearchWidget( QWidget* parent )
    : QWidget( parent )
{
    setAcceptDrops( true );

    QGridLayout* grid = new QGridLayout( this );
    setLayout( grid );

    // create the line edit
    searchLineEdit = new KLineEdit( this );
    searchLineEdit->setClearButtonShown( true );
    searchLineEdit->setAcceptDrops( false );
    searchLineEdit->setClickMessage( i18nc( "@info/plain Click message", "Search" ) );
    grid->addWidget( searchLineEdit, 0, 0 );

    if ( KamalaApp->core->sortedHoroscopes->len < MaxDynamicHoroscopeFilter )
    { // allow dynamic filtering for little databases
        connect( searchLineEdit, SIGNAL( textChanged( const QString& ) ),
            KamalaApp->horoscopeProxyModel, SLOT( setFilterWildcard( const QString& ) ) );
    }
    else
    { // filter only when return is pressed
        connect( searchLineEdit, SIGNAL( returnPressed() ),
            this, SLOT( resetSearchPattern() ) );
    }

    // create the tool bar
    const KActionCollection* acts = KamalaApp->mainWindow->actionCollection();
    toolBar = new QToolBar( this );
    toolBar->addAction( acts->action( "openChart" ) );
    toolBar->addAction( acts->action( "deleteChart" ) );
    grid->addWidget( toolBar, 1, 0 );

    // create the horoscope view
    horoscopeView = new HoroscopeView( KamalaApp->horoscopeProxyModel, this );
    grid->addWidget( horoscopeView, 2, 0 );

    searchLineEdit->setText( "*" ); // shows all horoscopes
}

void SearchWidget::dragEnterEvent( QDragEnterEvent* ev )
{
    if ( ev->source()
        && ev->source() != horoscopeView
        && strequ( (char*)ev->format(), (char*)"text/plain" ) )
    {
        ev->acceptProposedAction();
    }
    else ev->ignore();
}

void SearchWidget::dropEvent( QDropEvent* ev )
{
    ev->acceptProposedAction();
    KamalaApp->mainWindow->internalSaveWheel1(
        atoi( ev->mimeData()->text().toAscii().constData() ) );
}

void SearchWidget::resetSearchPattern() const
{
    KamalaApp->horoscopeProxyModel->setFilterWildcard( searchLineEdit->text() );
}
