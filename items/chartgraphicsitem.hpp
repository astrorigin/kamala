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

/** @file chartgraphicsitem.hpp
 */

#ifndef KAMALA_CHARTGRAPHICSITEM_HPP
#define KAMALA_CHARTGRAPHICSITEM_HPP

class QGraphicsItem;
#include <QGraphicsRectItem>
class QGraphicsSceneContextMenuEvent;
#include <QMap>
#include <QObject>
#include <QPair>
class QPointF;
#include "../kamala_export.hpp"

#include <core.h>

class AspectGraphicsItem;
class PlanetGraphicsItem;

/** @class ChartGraphicsItem
 *  @brief A square graphics item for the chart
 */
class KAMALA_EXPORT ChartGraphicsItem
    : public QGraphicsRectItem
{
  public:

    /** @brief Pointer to chart
     */
    Chart*      chart;

    /** @brief Constructor
     *  @param ch Chart we are working on
     *  @param parent Parent item
     */
    explicit ChartGraphicsItem( Chart* ch, QGraphicsItem* parent=0 );

    /** @brief Prepare pens
     *  Initialize frequently used pens according to preferences.
     */
    static void preparePens();

    /** @brief Draw the chart
     */
    void draw();

    /** @brief Context menu event handler
     */
    void contextMenuEvent( QGraphicsSceneContextMenuEvent* );

    /** @brief Map containing wheel-1 planet items
     */
    QMap<int, PlanetGraphicsItem*>      planetItems1;

    /** @brief Map containing wheel-2 planet items
     */
    QMap<int, PlanetGraphicsItem*>      planetItems2;

    /** @brief Map containing aspects items
     */
    QMap<QPair<int, int>, AspectGraphicsItem*>      aspectItems;

  private:

    /** @brief Draw a radix chart
     */
    void draw1();

    /** @brief Draw a compared chart
     */
    void draw2();

    /** @brief translate given angle/distance to our coordinates
     */
    static QPointF toPoint( double ang, double hyp, double modx=0, double mody=0 );

};

#endif // KAMALA_CHARTGRAPHICSITEM_HPP
