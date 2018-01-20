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

/** @file chartdockwidget.hpp
 */

#ifndef KAMALA_CHARTDOCKWIDGET_HPP
#define KAMALA_CHARTDOCKWIDGET_HPP

#include <QDockWidget>
class QWidget;
#include "../kamala_export.hpp"

class ChartWidget;

/** @class ChartDockWidget
 *  @brief Opened charts dock widget
 */
class KAMALA_EXPORT ChartDockWidget
    : public QDockWidget
{
    Q_OBJECT

  public:

    /** @brief Pointer to internal widget
     */
    ChartWidget*        widget;

    /** @brief Constructor
     *  @param parent Parent widget
     */
    explicit ChartDockWidget( QWidget* parent );

  public Q_SLOTS:

    /** @brief Set currently focused chart
     *  Signal emited by a subwindow activation.
     *  @param iWin Index of activated subwindow
     */
    void setCurrentIndex( int iWin ) const;

};

#endif // KAMALA_CHARTDOCKWIDGET_HPP
