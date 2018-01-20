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

/** @file main.cpp
 *  @brief The main process
 */

#include <KAboutData>
#include <KCmdLineArgs>
#include <KGlobal>

#include "application.hpp"

int main( int argc, char** argv )
{
    /* KDE "About" data */
    KAboutData aboutData
    (
        "kamala",                                       // program name
        0,                                              // message catalog name
        ki18n( "<application>Kamala</application>" ),   // displayable program name
        ZODIACORE_CVERSION,                             // version
        ki18n( "Astrology software for KDE" ),          // short description
        KAboutData::License_GPL_V3,                     // license
        ki18n( "&copy; 2009 Stanislas Marquis" ),       // copyright
        ki18n(                                          // other text
            "This is free software; see the license for copying conditions. "
            "There is NO warranty; not even for MERCHANTABILITY or "
            "FITNESS FOR A PARTICULAR PURPOSE." ),
        "http://kamala.chaosorigin.com/",               // homepage
        "roundphi@gmail.com"                            // bug report email
    );

    /* Credits */
    aboutData.addAuthor(
        ki18n( "Stanislas Marquis" ),
        ki18n( "Project author" ), "<email>roundphi@gmail.com</email>", "" );

    aboutData.addCredit(
        ki18n( "Dieter Koch" ),
        ki18n( "Swisseph author" ), "", "http://www.astro.com/" );

    aboutData.addCredit(
        ki18n( "Alois Treindl" ),
        ki18n( "Swisseph author" ), "", "http://www.astro.com/" );

    aboutData.addCredit(
        ki18n( "Eugene Trounev" ),
        ki18n( "Kamala icon" ), "<email>eugene.trounev@gmail.com</email>", "" );

    aboutData.addCredit(
        ki18n( "Marc Wick & co." ),
        ki18n( "GeoNames database" ), "", "http://geonames.org/" );

    /* Start app */
    KCmdLineArgs::init( argc, argv, &aboutData );
    KamalaApplication kamalaApp;
    return kamalaApp.exec();

}
