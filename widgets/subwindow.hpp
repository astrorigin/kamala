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

/** @file subwindow.hpp
 */

#ifndef KAMALA_SUBWINDOW_HPP
#define KAMALA_SUBWINDOW_HPP

class QCloseEvent;
#include <QMdiSubWindow>
class QResizeEvent;
class QString;
class QWidget;
#include "../kamala_export.hpp"

#include <core.h>

/** @class SubWindow
 *  @brief Window containing the chart wheel
 *  Holds methods for graphical operations on the chart wheel.
 */
class KAMALA_EXPORT SubWindow
    : public QMdiSubWindow
{
    Q_OBJECT

  public:

    /** @brief Pointer to chart
     */
    Chart*      chart;

    /** @brief Constructor
     *  @param ch Chart we are working on
     *  @param parent Parent widget
     */
    explicit SubWindow( Chart* ch, QWidget* parent );

    /** @brief Close event handler
     *  This activates the chart removal.
     *  @see MainWindow::internalSubWindowCloseEvent
     */
    void closeEvent( QCloseEvent* );

    /** @brief Resize event handler
     */
    void resizeEvent( QResizeEvent* );

    /** @brief Redraw chart
     */
    void reload();

#if 0
    /** @brief Zoom in 10%
    */
    void zoomIn() const;

    /** @brief Zoom out 10%
    */
    void zoomOut() const;

    /** @brief Create an image
    ** @param path Image file path
    */
    void saveChartAsImage( const QString &path );


    void stepBack();

    void stepForward();
#endif

};

#endif // KAMALA_SUBWINDOW_HPP
