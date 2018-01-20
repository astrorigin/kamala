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

/** @file mainwindow.hpp
 */

#ifndef KAMALA_MAINWINDOW_HPP
#define KAMALA_MAINWINDOW_HPP

class QMdiSubWindow;
class QWidget;
#include <KXmlGuiWindow>
#include "kamala_export.hpp"

#include <core.h>

#include "application.hpp"

class CentralWidget;
class ChartDockWidget;
class SearchDockWidget;

/** @class MainWindow
 *  @brief The Kamala main window
 *  Holds all application action slots. And more :P
 */
class KAMALA_EXPORT MainWindow
    : public KXmlGuiWindow
{
    friend class KamalaApplication;

    Q_OBJECT

  public:

    /** @brief Pointer to central widget
     */
    CentralWidget*      central;

    /** @brief Pointer to horoscope database search dock widget
     */
    SearchDockWidget*   searchDock;

    /** @brief Pointer to currently opened charts dock widget
     */
    ChartDockWidget*    chartDock;

    /** @brief Get number of currently opened charts
     */
    uint numCharts() const;

    /** @brief Get current chart, if any
     *  @return Pointer to current chart, or null
     */
    Chart* currentChart() const;

  public Q_SLOTS:

    /** @brief Enable/disable actions according to the current program state
     */
    void resetActions() const;

    /* "Graphical" actions, available to user interface through menus, etc.
     * These are prefixed with `action'.
     */

    /** @brief Create a new chart window
     *  Create and display a chart with current/local data.
     *  This should always succeed.
     */
    void actionNewChart();

    /** @brief Close the current chart window
     *  Close the current chart, if there is any.
     */
    void actionCloseChart() const;

    /** @brief Close all chart subwindows
     */
    void actionCloseAllCharts() const;

    /** @brief Open a new chart with currently selected horoscope
     */
    void actionOpenChart();

    /** @brief Remove selected horoscope data
     */
    void actionDeleteChart();

    /** @brief Edit current chart data
     */
    void actionEditWheel1();

    /** @brief Save current chart data
     */
    void actionSaveWheel1();

    /** @brief Launch preferences dialog
     */
    void actionPreferences();

    /* "Invisible" actions, used internally. Prefixed with `internal'.
     */

    /** @brief Open a new chart window with given horoscope as radix wheel
     *  @param horoIdx Horoscope idx
     */
    void internalOpenChart( const idx_t horoIdx );

    /** @brief Remove given horoscope from database
     *  @param horoIdx Horoscope idx
     */
    void internalDeleteHoroscope( const idx_t horoIdx );

    /** @brief Reload all charts with given horoscope
     *  @param horoIdx Horoscope idx
     */
    void internalReloadChart( const idx_t horoIdx );

    /** @brief Save data of given chart
     *  @param index Chart index, or -1 for current chart
     */
    void internalSaveWheel1( int index );

    /** @brief Subwindow activation event handler
     *  Catches subWindowActivated signal of central widget.
     */
    void internalSubWindowActivated( QMdiSubWindow* );

    /** @brief Subwindow close event handler
     *  Remove given chart off other places as well, since the subwindow is
     *  destroying itself right afterwards.
     *  @param iWin Subwindow index
     */
    void internalSubWindowCloseEvent( int iWin );

  private:

    /** @brief Constructor
     *  This only creates actions and then returns.
     *  We need the main window created and attached to KamalaApp->mainWindow,
     *  and the actions collection initialized, before the rest of the widgets
     *  can be made.
     *  @see initialize()
     *  @param parent Parent widget
     */
    explicit MainWindow( QWidget* parent=0 );

    /** @brief Initialize widgets and the rest
     *  @see Constructor
     */
    void initialize();

    /** @brief Initialize the set of actions
     */
    void createActions();

};

#endif // KAMALA_MAINWINDOW_HPP
