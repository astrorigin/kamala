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

/** @file searchwidget.hpp
 */

#ifndef KAMALA_SEARCHWIDGET_HPP
#define KAMALA_SEARCHWIDGET_HPP

class QDragEnterEvent;
class QDropEvent;
class QToolBar;
#include <QWidget>
class KLineEdit;
#include "../kamala_export.hpp"

class HoroscopeView;

/** @brief Dynamic filtering only under this value (horoscopes in database)
 *  Filtering more horoscopes requires user to press return in search line edit.
 */
const int MaxDynamicHoroscopeFilter = 10000;

/** @class SearchWidget
 *  @brief Widget for searching the horoscope database
 */
class KAMALA_EXPORT SearchWidget
    : public QWidget
{
    Q_OBJECT

  public:

    /** @brief Pointer to the search line edit
     *  Contains a string pattern to filter the horoscope view.
     */
    KLineEdit*          searchLineEdit;

    /** @brief Pointer to the tool bar
     */
    QToolBar*           toolBar;

    /** @brief Pointer to the horoscope database view
     */
    HoroscopeView*      horoscopeView;

    /** @brief Constructor
     */
    explicit SearchWidget( QWidget* parent );

    /** @brief Drag enter event handler
     */
    void dragEnterEvent( QDragEnterEvent* );

    /** @brief Drop event handler
     *  @see MainWindow::internalSaveWheel1
     */
    void dropEvent( QDropEvent* );

  public Q_SLOTS:

    /** @brief Reset search pattern of proxy model with the current search text
     */
    void resetSearchPattern() const;
};

#endif // KAMALA_SEARCHWIDGET_HPP
