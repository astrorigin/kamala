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

/** @file chartgraphicsview.hpp
 */

#ifndef KAMALA_CHARTGRAPHICSVIEW_HPP
#define KAMALA_CHARTGRAPHICSVIEW_HPP

#include <QGraphicsView>
class QWidget;
#include "../kamala_export.hpp"

#include <core.h>

/** @class ChartGraphicsView
 *  @brief Graphics view of a chart scene
 */
class KAMALA_EXPORT ChartGraphicsView
    : public QGraphicsView
{
    Q_OBJECT

  public:

    /** @brief Pointer to chart
     */
    Chart*      chart;

    /** @brief Constructor
     *  This creates the underlying scene.
     *  @param ch Chart we are working on
     *  @param parent Parent widget
     */
    explicit ChartGraphicsView( Chart* ch, QWidget* parent );

  public Q_SLOTS:

    /** @brief Reload the scene
     */
    void reload();
};

#endif // KAMALA_CHARTGRAPHICSVIEW_HPP
