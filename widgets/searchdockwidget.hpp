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

/** @file searchdockwidget.hpp
 */

#ifndef KAMALA_SEARCHDOCKWIDGET_HPP
#define KAMALA_SEARCHDOCKWIDGET_HPP

#include <QDockWidget>
class QWidget;
#include "../kamala_export.hpp"

class SearchWidget;

/** @class SearchDockWidget
 *  @brief Dock widget for searching the horoscope database
 */
class KAMALA_EXPORT SearchDockWidget
    : public QDockWidget
{
    Q_OBJECT

  public:

    /** @brief Pointer to internal widget
     */
    SearchWidget*       widget;

    /** @brief Constructor
     *  @param parent Parent widget
     */
    explicit SearchDockWidget( QWidget* parent );

};

#endif // KAMALA_SEARCHDOCKWIDGET_HPP
