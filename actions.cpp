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

/** @file actions.cpp
 */

#include <KAction>
#include <KActionCollection>
#include <KActionMenu>
#include <KDebug>
#include <KIcon>
#include <KLocalizedString>
#include <KSelectAction>
#include <KStandardAction>
#include <KToggleAction>

#include "application.hpp"
#include "mainwindow.hpp"
#include "views/horoscopeview.hpp"
#include "widgets/searchdockwidget.hpp"
#include "widgets/searchwidget.hpp"

void MainWindow::createActions()
{
    KActionCollection* coll = actionCollection();

    //const BTree* ctxtColl = KamalaApp->core->contextCollection;
    //const BTree* prflColl = KamalaApp->core->profileCollection;

    // Horoscope database actions

    KAction* openChart = coll->addAction( "openChart" );
    openChart->setText( i18nc( "@action", "Open" ) );
    openChart->setIcon( KIcon( "tab-new-background" ) );
    connect( openChart, SIGNAL( triggered() ), this, SLOT( actionOpenChart() ) );

    KAction* deleteChart = coll->addAction( "deleteChart" );
    deleteChart->setText( i18nc( "@action", "Delete" ) );
    deleteChart->setIcon( KIcon( "edit-delete" ) );
    connect( deleteChart, SIGNAL( triggered() ), this, SLOT( actionDeleteChart() ) );

    // Chart menu

    KAction* newChart = coll->addAction( "newChart" );
    newChart->setText( i18nc( "@action", "New" ) );
    newChart->setIcon( KIcon( "tab-new" ) );
    newChart->setShortcut( Qt::CTRL + Qt::Key_N );
    connect( newChart, SIGNAL( triggered() ), this, SLOT( actionNewChart() ) );

    KAction* closeChart = coll->addAction( "closeChart" );
    closeChart->setText( i18nc( "@action", "Close" ) );
    closeChart->setIcon( KIcon( "tab-close" ) );
    closeChart->setShortcut( Qt::CTRL + Qt::Key_W );
    connect( closeChart, SIGNAL( triggered() ), this, SLOT( actionCloseChart() ) );

    KAction* closeAll = coll->addAction( "closeAllCharts" );
    closeAll->setText( i18nc( "@action", "Close All" ) );
    closeAll->setShortcut( Qt::CTRL + Qt::SHIFT + Qt::Key_W );
    connect( closeAll, SIGNAL( triggered() ), this, SLOT( actionCloseAllCharts() ) );



    KAction* quitApp = coll->addAction( "quitApp" );
    quitApp->setText( i18nc( "@action", "Quit" ) );
    quitApp->setIcon( KIcon( "application-exit" ) );
    quitApp->setShortcut( Qt::CTRL + Qt::Key_Q );
    connect( quitApp, SIGNAL( triggered() ), this, SLOT( close() ) );

#if 0
    KAction* saveAsImage = coll->addAction( "saveAsImage" );
    saveAsImage->setText( i18nc( "@action", "Save Image..." ) );
    saveAsImage->setIcon( KIcon( "view-preview" ) );
    connect( saveAsImage, SIGNAL( triggered() ), this, SLOT( saveChartAsImage() ) );

    KSelectAction* chartContext = new KSelectAction( KIcon( "configure" ),
        i18nc( "@action Select action", "Context" ), this );
    chartContext->setItems( ctxtColl->contextNames() );
    coll->addAction( "chartContext", (KAction*) chartContext );
    connect( chartContext, SIGNAL( triggered( const QString& ) ),
        this, SLOT( chartContextTriggered( const QString& ) ) );

    KAction* zoomIn = coll->addAction( "zoomIn" );
    zoomIn->setText( i18nc( "@action", "Zoom In" ) );
    zoomIn->setIcon( KIcon( "zoom-in" ) );
    zoomIn->setShortcut( Qt::CTRL + Qt::Key_Plus );
    connect( zoomIn, SIGNAL( triggered() ), this, SLOT( zoomIn() ) );

    KAction* zoomOut = coll->addAction( "zoomOut" );
    zoomOut->setText( i18nc( "@action", "Zoom Out" ) );
    zoomOut->setIcon( KIcon( "zoom-out" ) );
    zoomOut->setShortcut( Qt::CTRL + Qt::Key_Minus );
    connect( zoomOut, SIGNAL( triggered() ), this, SLOT( zoomOut() ) );

#endif

    // Wheel 1 menu

    KAction* editWheel1 = coll->addAction( "editWheel1" );
    editWheel1->setText( i18nc( "@action Edit 1st wheel data", "Edit ( 1 )..." ) );
    editWheel1->setIcon( KIcon( "document-edit" ) );
    editWheel1->setShortcut( Qt::CTRL + Qt::Key_E );
    connect( editWheel1, SIGNAL( triggered() ), this, SLOT( actionEditWheel1() ) );

    KAction* saveWheel1 = coll->addAction( "saveWheel1" );
    saveWheel1->setText( i18nc( "@action Save 1st wheel data", "Save ( 1 )" ) );
    saveWheel1->setIcon( KIcon( "document-save" ) );
    saveWheel1->setShortcut( Qt::CTRL + Qt::Key_S );
    connect( saveWheel1, SIGNAL( triggered() ), this, SLOT( actionSaveWheel1() ) );

#if 0
    KAction* saveWheel1As = coll->addAction( "saveWheel1As" );
    saveWheel1As->setText( i18nc( "@action", "Save As..." ) );
    saveWheel1As->setIcon( KIcon( "document-save-as" ) );
    saveWheel1As->setShortcut( Qt::CTRL + Qt::SHIFT + Qt::Key_S );
    connect( saveWheel1As, SIGNAL( triggered() ), this, SLOT( saveWheel1As() ) );

    KSelectAction* settingsWheel1 = new KSelectAction( KIcon( "configure" ),
        i18nc("@action Select action", "Settings"), this );
    settingsWheel1->setItems( settColl->settingsNames() );
    coll->addAction( "settingsWheel1", (KAction*) settingsWheel1 );
    connect( settingsWheel1, SIGNAL( triggered( const QString& ) ),
        this, SLOT( settingsWheel1Triggered( const QString& ) ) );

    KAction* stepBackWheel1 = coll->addAction( "stepBackWheel1" );
    stepBackWheel1->setText( i18nc( "@action", "Step Back" ) );
    stepBackWheel1->setIcon( KIcon( "go-previous" ) );
    stepBackWheel1->setShortcut( Qt::ALT + Qt::Key_Left );
    connect( stepBackWheel1, SIGNAL( triggered() ), this, SLOT( stepBack() ) );

    KAction* stepForwardWheel1 = coll->addAction( "stepForwardWheel1" );
    stepForwardWheel1->setText( i18nc( "@action", "Step Forward" ) );
    stepForwardWheel1->setIcon( KIcon( "go-next" ) );
    stepForwardWheel1->setShortcut( Qt::ALT + Qt::Key_Right );
    connect( stepForwardWheel1, SIGNAL( triggered() ), this, SLOT( stepForward() ) );

    // step type
    KSelectAction* stepTypeWheel1 = new KSelectAction( KIcon( "configure" ),
        i18nc( "@action", "Step Type" ), this );
    stepTypeWheel1->setItems( QStringList()
        << i18nc( "@option:check", "Time Step" )
        << i18nc( "@option:check", "Space Step" ) );
    stepTypeWheel1->setCurrentItem( 0 );
    coll->addAction( "stepTypeWheel1", (KAction*) stepTypeWheel1 );

    // time step value
    KSelectAction* timeStepValueWheel1 = new KSelectAction( KIcon( "configure" ),
        i18nc( "@action", "Time Step Value" ), this );
    timeStepValueWheel1->setItems( QStringList()
        << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9" << "10"
        << "20" << "30" << "40" << "50" << "100" );
    timeStepValueWheel1->setCurrentItem( 0 );
    coll->addAction( "timeStepValueWheel1", (KAction*) timeStepValueWheel1 );

    // time step unit
    KSelectAction* timeStepUnitWheel1 = new KSelectAction( KIcon( "configure" ),
        i18nc( "@action", "Time Step Unit" ), this );
    timeStepUnitWheel1->setItems( QStringList()
        << i18nc( "@option:check Time step unit", "Second" )
        << i18nc( "@option:check Time step unit", "Minute" )
        << i18nc( "@option:check Time step unit", "Hour" )
        << i18nc( "@option:check Time step unit", "Day" )
        << i18nc( "@option:check Time step unit", "Month" )
        << i18nc( "@option:check Time step unit", "Year" ) );
    timeStepUnitWheel1->setCurrentItem( 3 );
    coll->addAction( "timeStepUnitWheel1", (KAction*) timeStepUnitWheel1 );

    // space step axis
    KSelectAction* spaceStepAxisWheel1 = new KSelectAction( KIcon( "configure" ),
        i18nc ( "@action", "Space Step Axis" ), this );
    spaceStepAxisWheel1->setItems( QStringList()
        << i18nc( "@option:check Space step axis", "North / South" )
        << i18nc( "@option:check Space step axis", "East / West" ) );
    spaceStepAxisWheel1->setCurrentItem( 1 );
    coll->addAction( "spaceStepAxisWheel1", (KAction*) spaceStepAxisWheel1 );



    * *** Wheel 2 actions ***

    KToggleAction* showWheel2 = new KToggleAction( i18nc( "@action", "Show / Hide" ), this );
    showWheel2->setShortcut( Qt::Key_C );
    coll->addAction( "showWheel2", (KAction*) showWheel2 );
    connect( showWheel2, SIGNAL( triggered() ), this, SLOT( showWheel2() ) );

    KAction* transitsNow = coll->addAction( "transitsNow" );
    transitsNow->setText( i18nc( "@action", "Transits For Now" ) );
    //transitsNow->setIcon( KIcon( "" ) );
    transitsNow->setShortcut( Qt::Key_N );
    connect( transitsNow, SIGNAL( triggered() ), this, SLOT( transitsNow() ) );

    KAction* editWheel2 = coll->addAction( "editWheel2" );
    editWheel2->setText( i18nc( "@action", "Edit..." ) );
    editWheel2->setIcon( KIcon( "document-edit" ) );
    editWheel2->setShortcut( Qt::CTRL + Qt::SHIFT + Qt::Key_E );
    connect( editWheel2, SIGNAL( triggered() ), this, SLOT( editWheel2() ) );



    * Tools actions

    KAction *executeScript = coll->addAction("executeScript");
    executeScript->setText(i18nc("@action", "Execute Script..."));
    executeScript->setIcon(KIcon("edit-bomb"));
    connect(executeScript, SIGNAL(triggered()), this, SLOT(executeScript()));
#endif
    /* Settings actions */

    KStandardAction::preferences( this, SLOT( actionPreferences() ), (QObject*) coll );
#if 0
    KAction *contextMan = coll->addAction("contextManager");
    contextMan->setText(i18nc("@action", "Configure Contexts..."));
    contextMan->setIcon(KIcon("configure"));
    connect(contextMan, SIGNAL(triggered()), this, SLOT(contextManager()));

    KAction *settingsMan = coll->addAction("settingsManager");
    settingsMan->setText(i18nc("@action", "Configure Settings..."));
    settingsMan->setIcon(KIcon("configure"));
    connect(settingsMan, SIGNAL(triggered()), this, SLOT(settingsManager()));

    KAction *planetFilterMan = coll->addAction("planetFilterManager");
    planetFilterMan->setText(i18nc("@action", "Configure Planets Filters..."));
    planetFilterMan->setIcon(KIcon("configure"));
    connect(planetFilterMan, SIGNAL(triggered()), this, SLOT(planetFilterManager()));

    KAction *aspectFilterMan = coll->addAction("aspectFilterManager");
    aspectFilterMan->setText(i18nc("@action", "Configure Aspects Filters..."));
    aspectFilterMan->setIcon(KIcon("configure"));
    connect(aspectFilterMan, SIGNAL(triggered()), this, SLOT(aspectFilterManager()));

    KAction *orbFilterMan = coll->addAction("orbFilterManager");
    orbFilterMan->setText(i18nc("@action", "Configure Orbs Filters..."));
    orbFilterMan->setIcon(KIcon("configure"));
    connect(orbFilterMan, SIGNAL(triggered()), this, SLOT(orbFilterManager()));

    KAction *aspectRestrictionMan = coll->addAction("aspectRestrictionManager");
    aspectRestrictionMan->setText(i18nc("@action", "Configure Aspects Restrictions..."));
    aspectRestrictionMan->setIcon(KIcon("configure"));
    connect(aspectRestrictionMan, SIGNAL(triggered()), this, SLOT(aspectRestrictionManager()));

    KAction *orbRestrictionMan = coll->addAction("orbRestrictionManager");
    orbRestrictionMan->setText(i18nc("@action", "Configure Orbs Restrictions..."));
    orbRestrictionMan->setIcon(KIcon("configure"));
    connect(orbRestrictionMan, SIGNAL(triggered()), this, SLOT(orbRestrictionManager()));

    KAction *aspectMan = coll->addAction("aspectManager");
    aspectMan->setText(i18nc("@action", "Configure Aspects..."));
    aspectMan->setIcon(KIcon("configure"));
    connect(aspectMan, SIGNAL(triggered()), this, SLOT(aspectManager()));

    KAction *planetMan = coll->addAction("planetManager");
    planetMan->setText(i18nc("@action", "Configure Planets..."));
    planetMan->setIcon(KIcon("configure"));
    connect(planetMan, SIGNAL(triggered()), this, SLOT(planetManager()));

    KAction *keywordMan = coll->addAction("keywordManager");
    keywordMan->setText(i18nc("@action", "Configure Keywords..."));
    keywordMan->setIcon(KIcon("configure"));
    connect(keywordMan, SIGNAL(triggered()), this, SLOT(keywordManager()));

    * Dummy actions connected to HoroscopeView slots

    // edit horoscope
    KAction *editHoroscope = coll->addAction( "editHoroscope" );
    editHoroscope->setText( i18nc( "@action", "Edit Horoscope..." ) );
    editHoroscope->setIcon( KIcon( "document-edit" ) );

    // delete horoscope
    KAction *deleteHoroscope = coll->addAction( "deleteHoroscope" );
    deleteHoroscope->setText( i18nc( "@action", "Delete Horoscope" ) );
    deleteHoroscope->setIcon( KIcon( "edit-delete" ) );
#endif
}

void MainWindow::resetActions() const
{
    KActionCollection* coll = actionCollection();

    if ( numCharts() > 0 )
    { // at least one opened chart
        const Horoscope* h = currentChart()->wh1->horo;
        assert( h );

        coll->action( "closeChart" )->setEnabled( true );
        coll->action( "closeAllCharts" )->setEnabled( true );

        coll->action( "editWheel1" )->setEnabled( true );

        if ( !h->_idx || h->changed )
        {
            coll->action( "saveWheel1" )->setEnabled( true );
        }
        else
        {
            coll->action( "saveWheel1" )->setEnabled( false );
        }

#if 0
        coll->action( "saveAsImage" )->setEnabled( true );

        coll->action( "chartContext" )->setEnabled( true );
        coll->action( "zoomIn" )->setEnabled( true );
        coll->action( "zoomOut" )->setEnabled( true );

        coll->action( "editWheel1" )->setEnabled( true );
        coll->action( "saveWheel1As" )->setEnabled( true );
        coll->action( "settingsWheel1" )->setEnabled( true );
        coll->action( "stepBackWheel1" )->setEnabled( true );
        coll->action( "stepForwardWheel1" )->setEnabled( true );

        coll->action( "showWheel2" )->setEnabled( true );
        coll->action( "transitsNow" )->setEnabled( true );

        if ( currentChart()->type() == Chart::TypeCompared )
        { // two wheels
            coll->action( "editWheel2" )->setEnabled( true );
            coll->action( "showWheel2" )->setChecked( true );
        }
        else
        { // one wheel
            coll->action( "editWheel2" )->setEnabled( false );
            coll->action( "showWheel2" )->setChecked( false );
        }
#endif
    }
    else
    { // no opened chart
        coll->action( "closeChart" )->setEnabled( false );
        coll->action( "closeAllCharts" )->setEnabled( false );

        coll->action( "editWheel1" )->setEnabled( false );
        coll->action( "saveWheel1" )->setEnabled( false );
#if 0
        coll->action( "saveAsImage" )->setEnabled( false );

        coll->action( "chartContext" )->setEnabled( false );
        coll->action( "zoomIn" )->setEnabled( false );
        coll->action( "zoomOut" )->setEnabled( false );

        coll->action( "editWheel1" )->setEnabled( false );
        coll->action( "saveWheel1As" )->setEnabled( false );
        coll->action( "settingsWheel1" )->setEnabled( false );
        coll->action( "stepBackWheel1" )->setEnabled( false );
        coll->action( "stepForwardWheel1" )->setEnabled( false );

        coll->action( "editWheel2" )->setEnabled( false );
        coll->action( "showWheel2" )->setEnabled( false );
        coll->action( "showWheel2" )->setChecked( false );
        coll->action( "transitsNow" )->setEnabled( false );
#endif
    }

    if ( searchDock->widget->horoscopeView->selectedHoroscope() )
    {
        coll->action( "openChart" )->setEnabled( true );
        coll->action( "deleteChart" )->setEnabled( true );
    }
    else
    {
        coll->action( "openChart" )->setEnabled( false );
        coll->action( "deleteChart" )->setEnabled( false );
    }
}

#if 0
void MainWindow::chartContextTriggered( const QString &selected )
{
    Chart* current = currentChart();
    Q_ASSERT( current );
    ContextCollection* ctxtColl = ContextCollection::dbCollection();

    current->setContext( ctxtColl->context( selected ) );
    current->calc();
    ChartCollection::openedCharts()->emitChartChanged( current );
}

void MainWindow::contextChanged( ContextCollection* ctxtColl, Context*, Context::Properties p )
{
    if ( p & Context::NameProperty )
    {
        KActionCollection* coll = actionCollection();
        KSelectAction* chartContext = (KSelectAction*) coll->action( "chartContext" );
        chartContext->clear();
        chartContext->setItems( ctxtColl->contextNames() );
        if ( currentChart() )
        {
            QString selected = currentChart()->context()->name();
            chartContext->setCurrentAction( selected );
        }
    }
}

void MainWindow::contextAdded( ContextCollection* ctxtColl, Context* )
{ // merge
    KActionCollection* coll = actionCollection();
    KSelectAction* chartContext = (KSelectAction*) coll->action( "chartContext" );
    chartContext->clear();
    chartContext->setItems( ctxtColl->contextNames() );
    if ( currentChart() )
    {
        QString selected = currentChart()->context()->name();
        chartContext->setCurrentAction( selected );
    }
}

void MainWindow::contextRemoved( ContextCollection* ctxtColl, Context*, int )
{ // merge ^
    KActionCollection* coll = actionCollection();
    KSelectAction* chartContext = (KSelectAction*) coll->action( "chartContext" );
    chartContext->clear();
    chartContext->setItems( ctxtColl->contextNames() );
    if ( currentChart() )
    {
        QString selected = currentChart()->context()->name();
        chartContext->setCurrentAction( selected );
    }
}

void MainWindow::settingsWheel1Triggered( const QString &selected )
{
    Chart* current = currentChart();
    Q_ASSERT( current );
    Wheel* radx = current->radix();
    SettingsCollection* settColl = SettingsCollection::dbCollection();

    radx->setSettings( settColl->settings( selected ) );
    current->calc();
    ChartCollection::openedCharts()->emitChartChanged( current );
}

void MainWindow::settingsChanged( SettingsCollection* settColl, Settings*, Settings::Properties p )
{
    if ( p & Settings::NameProperty )
    {
        KActionCollection* coll = actionCollection();
        KSelectAction* settingsWheel1 = (KSelectAction*) coll->action( "settingsWheel1" );
        settingsWheel1->clear();
        settingsWheel1->setItems( settColl->settingsNames() );
        if ( currentChart() )
        {
            QString selected = currentChart()->radix()->settings()->name();
            settingsWheel1->setCurrentAction( selected );
        }
    }
}

void MainWindow::settingsAdded( SettingsCollection* settColl, Settings* )
{ // merge
    KActionCollection* coll = actionCollection();
    KSelectAction* settingsWheel1 = (KSelectAction*) coll->action( "settingsWheel1" );
    settingsWheel1->clear();
    settingsWheel1->setItems( settColl->settingsNames() );
    if ( currentChart() )
    {
        QString selected = currentChart()->radix()->settings()->name();
        settingsWheel1->setCurrentAction( selected );
    }
}

void MainWindow::settingsRemoved( SettingsCollection* settColl, Settings*, int )
{ // merge ^
    KActionCollection* coll = actionCollection();
    KSelectAction* settingsWheel1 = (KSelectAction*) coll->action( "settingsWheel1" );
    settingsWheel1->clear();
    settingsWheel1->setItems( settColl->settingsNames() );
    if ( currentChart() )
    {
        QString selected = currentChart()->radix()->settings()->name();
        settingsWheel1->setCurrentAction( selected );
    }
}
#endif