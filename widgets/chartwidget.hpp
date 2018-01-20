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

/** @file chartwidget.hpp
 */

#ifndef KAMALA_CHARTWIDGET_HPP
#define KAMALA_CHARTWIDGET_HPP

class QDragEnterEvent;
class QDropEvent;
#include <QWidget>
#include "../kamala_export.hpp"

class ChartView;

/** @class ChartWidget
 *  @brief Widget exposing the currently opened charts, in a table view
 */
class KAMALA_EXPORT ChartWidget
    : public QWidget
{
    Q_OBJECT

  public:

    /** @brief Pointer to view of charts
     */
    ChartView*      chartView;

    /** @brief Constructor
     *  @param parent Parent widget
     */
    explicit ChartWidget( QWidget* parent );

    /** @brief Drag enter event handler
     */
    void dragEnterEvent( QDragEnterEvent* );

    /** @brief Drop event handler
     *  @see MainWindow::internalOpenChart
     */
    void dropEvent( QDropEvent* );

    /** @brief Set currently selected chart
     *  @param idx Chart index
     */
    void setCurrentIndex( int idx ) const;

};

#endif // KAMALA_CHARTWIDGET_HPP
