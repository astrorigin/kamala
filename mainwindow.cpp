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

/** @file mainwindow.cpp
 */

#include "mainwindow.hpp"

#include <QList>
#include <QListIterator>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QPointer>
#include <QWidget>

#include <KDebug>
#include <KLocalizedString>
#include <KMessageBox>
#include <KXmlGuiWindow>

#include "application.hpp"
#include "dialogs/horoscopedialog.hpp"
#include "dialogs/preferencesdialog.hpp"
#include "items/chartgraphicsitem.hpp"
#include "models/chartmodel.hpp"
#include "models/horoscopemodel.hpp"
#include "views/horoscopeview.hpp"
#include "widgets/centralwidget.hpp"
#include "widgets/chartdockwidget.hpp"
#include "widgets/searchdockwidget.hpp"
#include "widgets/searchwidget.hpp"
#include "widgets/subwindow.hpp"

MainWindow::MainWindow( QWidget* parent )
    : KXmlGuiWindow( parent )
{
    setWindowTitle(
        i18nc( "@title:window", "<application>Kamala</application>" ) );

    createActions();
}

void MainWindow::initialize()
{
    chartDock = new ChartDockWidget( this );
    addDockWidget( Qt::LeftDockWidgetArea, chartDock );

    searchDock = new SearchDockWidget( this );
    addDockWidget( Qt::LeftDockWidgetArea, searchDock );

    central = new CentralWidget( this );
    setCentralWidget( central );

    setupGUI();

    actionNewChart(); // load current chart on startup
}

uint MainWindow::numCharts() const
{
    return KamalaApp->core->chartCollection->len;
}

Chart* MainWindow::currentChart() const
{
    if ( !KamalaApp->core->chartCollection->len )
        return NULL;
    return ((Chart**)KamalaApp->core->chartCollection->ptr)
        [ central->subWindowList().indexOf( central->currentSubWindow() ) ];
}

void MainWindow::actionNewChart()
{
    Chart* c = NULL;
    chart_new( KamalaApp->core, &c );
    chart_now( KamalaApp->core, c );
    str_set( c->wh1->horo->name, // set default wheel name
        (char*) i18nc( "@info/plain Here&now chart title", "Current" ).toUtf8().constData(), 0 );
    chart_calc( KamalaApp->core, c );

    KamalaApp->chartModel->chartAboutToBeAdded( KamalaApp->core->chartCollection->len );
    chart_register( KamalaApp->core, c );
    KamalaApp->chartModel->chartAdded();

    central->addSubWindow( c );
    resetActions();
}

void MainWindow::actionCloseChart() const
{
    central->closeSubWindow( -1 );
    resetActions();
}

void MainWindow::actionCloseAllCharts() const
{
    central->closeAllSubWindows();
    resetActions();
}

void MainWindow::actionOpenChart()
{
    const Horoscope* h = searchDock->widget->horoscopeView->selectedHoroscope();
    assert( h );
    internalOpenChart( h->_idx );
}

void MainWindow::actionDeleteChart()
{
    const Horoscope* h = searchDock->widget->horoscopeView->selectedHoroscope();
    assert( h );

    const int res = KMessageBox::warningContinueCancel( this,
        i18nc( "@info", "<warning>Are you certain you want to delete horoscope "
               "<resource>%1</resource> ?</warning>", QString::fromUtf8( h->name->ptr ) ),
        i18nc( "@title:window", "Delete Horoscope" ),
        KStandardGuiItem::cont(), KStandardGuiItem::cancel(),
        "HoroscopeDeletionWarning" );
    if ( res != KMessageBox::Continue )
        return;

    internalDeleteHoroscope( h->_idx );
}

void MainWindow::actionEditWheel1()
{
    assert( numCharts() );
    Chart* ch = currentChart();
    Wheel* wh = ch->wh1;
    Horoscope* h = wh->horo;

    QPointer<HoroscopeDialog> dlg = new HoroscopeDialog( this, h, false );
    if ( dlg->exec() == HoroscopeDialog::Accepted )
    {
        Horoscope* res = dlg->horoscope();
        if ( h != res ) // detached
            wh->horo = res;

        chart_calc( KamalaApp->core, ch );
        ((SubWindow*)central->currentSubWindow())->reload();

        resetActions();
    }
    delete dlg;
}

void MainWindow::actionSaveWheel1()
{
    assert( numCharts() );
    internalSaveWheel1( -1 );
}

void MainWindow::actionPreferences()
{
    QPointer<PreferencesDialog> dlg = new PreferencesDialog( this );
    if ( dlg->exec() == PreferencesDialog::Accepted )
    { // reloading
        ChartGraphicsItem::preparePens();
    }
    delete dlg;
}

void MainWindow::internalOpenChart( const idx_t horoIdx )
{
    // creating a new chart
    Chart* c = NULL;
    chart_new( KamalaApp->core, &c );

    // setting data
    const Horoscope* h = (Horoscope*)btree_value(
        KamalaApp->core->horoscopeCollection, horoIdx );
    assert( h );
    horoscope_copy( c->wh1->horo, h );
    chart_calc( KamalaApp->core, c );

    // adding to core collection
    KamalaApp->chartModel->chartAboutToBeAdded( KamalaApp->core->chartCollection->len );
    chart_register( KamalaApp->core, c );
    KamalaApp->chartModel->chartAdded();

    // display chart
    central->addSubWindow( c );
    resetActions();
}

void MainWindow::internalDeleteHoroscope( const idx_t horoIdx )
{
    Horoscope* h = (Horoscope*)btree_value(
        KamalaApp->core->horoscopeCollection, horoIdx );
    assert( h );

    KamalaApp->horoscopeModel->horoscopeAboutToBeRemoved(
        horoscope_index( KamalaApp->core, h ) );
    horoscope_erase( KamalaApp->core, h );
    KamalaApp->horoscopeModel->horoscopeRemoved();

    // refresh chart model
    size_t i = 0;
    const size_t cnt = KamalaApp->core->chartCollection->len;
    for ( ; i < cnt; ++i )
    {
        if ( ((Chart**)KamalaApp->core->chartCollection->ptr)[i]->wh1->horo->_idx == 0 )
            KamalaApp->chartModel->chartChanged( i );
    }

    horoscope_delete( &h );
    resetActions();
}

void MainWindow::internalReloadChart( const idx_t horoIdx )
{
    const QList<QMdiSubWindow*> lst = central->subWindowList();
    if ( !lst.count() ) return;

    SubWindow* sub;
    QListIterator<QMdiSubWindow*> iter( lst );
    while( iter.hasNext() )
    {
        sub = (SubWindow*) iter.next();
        if ( sub->chart->wh1->horo->_idx == horoIdx )
        {
            chart_calc( KamalaApp->core, sub->chart );
            sub->reload();
        }
    }
}

void MainWindow::internalSaveWheel1( int index )
{
    Chart* ch = NULL;
    Horoscope* horo = NULL;

    if ( index < 0 )
    { // save current chart
        ch = currentChart();
        assert( ch );
    }
    else
    { // save given chart
        assert( index < KamalaApp->core->chartCollection->len );
        ch = ((Chart**)KamalaApp->core->chartCollection->ptr)[ index ];
    }
    horo = ch->wh1->horo;
    assert( horo );

    // check duplicate name
    const Horoscope* tmp = horoscope_whose_name( KamalaApp->core, horo->name->ptr );
    if ( tmp && tmp->_idx != horo->_idx )
    {
        KMessageBox::error( this,
            i18nc( "@info", "<warning>Horoscope <resource>%1</resource> "
                   "already exists !</warning>", QString::fromUtf8( horo->name->ptr ) ),
            i18nc( "@title:window", "Error" ) );
        return;
    }

    // do save
    idx_t res = 0;
    if ( horo->_idx == 0 )
    { // insertion
        const size_t i = horoscope_fake_insert( KamalaApp->core, horo->name->ptr );
        KamalaApp->horoscopeModel->horoscopeAboutToBeAdded( i );
        res = horoscope_insert( KamalaApp->core, horo );
        KamalaApp->horoscopeModel->horoscopeAdded();
    }
    else
    { // update
        res = horoscope_update( KamalaApp->core, horo );
        internalReloadChart( horo->_idx );
    }
    assert( res );

    horo->changed = False;
    resetActions();

    KMessageBox::information( this,
        i18nc( "@info", "Horoscope successfully saved as "
               "<resource>%1</resource>.", QString::fromUtf8( horo->name->ptr ) ),
        i18nc( "@title:window", "Horoscope Saved" ),
        "HoroscopeSuccessfullySaved" );
}

void MainWindow::internalSubWindowActivated( QMdiSubWindow* w )
{
    resetActions();
    if ( !w )
        return;
    chartDock->setCurrentIndex( central->subWindowList().indexOf( w ) );
}

void MainWindow::internalSubWindowCloseEvent( int iWin )
{
    Chart* c = ((Chart**)KamalaApp->core->chartCollection->ptr)[iWin];
    assert( c );
    KamalaApp->chartModel->chartAboutToBeRemoved( iWin );
    chart_unregister( KamalaApp->core, iWin );
    KamalaApp->chartModel->chartRemoved();
    chart_delete( &c );

    // make sure one row of chartsview is selected (the right one pls)
    if ( KamalaApp->core->chartCollection->len )
    {
        //central->setActiveSubWindow( i );
        chartDock->setCurrentIndex( iWin - 1 );
    }

    resetActions();
}
