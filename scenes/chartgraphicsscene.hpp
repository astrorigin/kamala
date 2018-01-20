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

/** @file chartgraphicsscene.hpp
 */

#ifndef KAMALA_CHARTGRAPHICSSCENE_HPP
#define KAMALA_CHARTGRAPHICSSCENE_HPP

#include <QGraphicsScene>
class QObject;
#include "../kamala_export.hpp"

#include <core.h>

/** @class ChartGraphicsScene
 *  @brief Graphics scene of a chart
 */
class KAMALA_EXPORT ChartGraphicsScene
    : public QGraphicsScene
{
    Q_OBJECT

  public:

    /** @brief Pointer to chart
     */
    Chart*      chart;

    /** @brief Constructor
     *  Create and draw the scene.
     *  @param ch Chart we are working on
     */
    explicit ChartGraphicsScene( Chart* ch, QObject* parent );

  public Q_SLOTS:

    /** @brief Draw graphics
     * This clears everything and redraws the chart. The view then gets updated
     * by a `changed' signal.
     */
    void draw();

};

#endif // KAMALA_CHARTGRAPHICSSCENE_HPP
