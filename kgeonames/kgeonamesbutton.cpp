/*
    Kamala Astrology Software

    Copyright 2009 Stanislas Marquis <stnsls@gmail.com>

    Kamala is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of
    the License, or (at your option) any later version.

    Kamala is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Kamala.  If not, see <http://www.gnu.org/licenses/>.
*/

/** @file kgeonamesbutton.cpp
 */

#include "kgeonamesbutton.hpp"

#include <QWidget>
#include <QToolButton>

#include <KIcon>
#include <KLocalizedString>

KGeoNamesButton::KGeoNamesButton( QWidget* parent )
    : QToolButton( parent )
{
    setIcon( KIcon( "geonames" ) );
    setToolTip( i18nc( "GeoNames button tool tip", "Query GeoNames.org" ) );
}
