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

/** @file application.cpp
 */

#include "application.hpp"

#include <QString>

#include <KApplication>
#include <KDebug>
#include <KStandardDirs>

#include "items/chartgraphicsitem.hpp"
#include "mainwindow.hpp"
#include "models/chartmodel.hpp"
#include "models/horoscopemodel.hpp"
#include "models/horoscopeproxymodel.hpp"
#include "translation.hpp"

#include <core.h>

KamalaApplication::KamalaApplication()
    : KApplication(),
    core( NULL )
{
    // check for existence of our local data dir, usually in ~/.kde/share/apps/
    QString homeDir = KStandardDirs::locateLocal( "data", "kamala/", true );

    // check for existence of our shared dir
    QString shareDir = KStandardDirs::installPath( "data" ) + "kamala/";
    if ( !KStandardDirs::exists( shareDir ) )
        kFatal() << "Fatal: Unable to find shared directory, check your installation";

    // check for existence of atlas database
    QString atlasDb = KStandardDirs::locate( "data", "kamala/atlas.db" );
    if ( atlasDb.isEmpty() )
        atlasDb = "0"; // disable the atlas

    // check for sql files
    QString sqliteCreates = KStandardDirs::locate( "data", "kamala/sqlite_creates.sql" );
    QString sqliteInserts = KStandardDirs::locate( "data", "kamala/sqlite_inserts.sql" );
    if ( sqliteCreates.isEmpty() || sqliteInserts.isEmpty() )
        kFatal() << "Fatal: Unable to find SQL files, check your installation";

    // set env vars for core
    setenv( "ZODIACORE_HOME_DIR", homeDir.toUtf8().constData(), 1 );
    setenv( "ZODIACORE_SHARE_DIR", shareDir.toUtf8().constData(), 1 );
    setenv( "ZODIACORE_ATLAS_DB", atlasDb.toUtf8().constData(), 1 );
    setenv( "ZODIACORE_DB_CREATES", sqliteCreates.toUtf8().constData(), 1 );
    setenv( "ZODIACORE_DB_INSERTS", sqliteInserts.toUtf8().constData(), 1 );

    // init core
    zodiacore_new( &core );

    // create models
    horoscopeModel = new HoroscopeModel( core, this );
    horoscopeProxyModel = new HoroscopeProxyModel( horoscopeModel, this );
    chartModel = new ChartModel( core, this );

    // other preparations
    loadTranslation(); // load vocabulary
    ChartGraphicsItem::preparePens(); // load pens

    // init gui
    mainWindow = new MainWindow;
    mainWindow->initialize();
    mainWindow->show();
}

KamalaApplication::~KamalaApplication()
{
    // free core
    zodiacore_delete( &core, True );
    // delete vocabulary
    deleteTranslation();
}

QStringList KamalaApplication::contextsStringList() const
{
    QStringList sl;
    BTree* it = btree_least( core->contextCollection );
    for ( ; it; it = btree_next( it ) )
        sl << QString::fromUtf8( ((Context*)it->val)->name->ptr );
    sl.sort();
    return sl;
}

QStringList KamalaApplication::profilesStringList() const
{
    QStringList sl;
    BTree* it = btree_least( core->profileCollection );
    for ( ; it; it = btree_next( it ) )
        sl << QString::fromUtf8( ((Profile*)it->val)->name->ptr );
    sl.sort();
    return sl;
}
