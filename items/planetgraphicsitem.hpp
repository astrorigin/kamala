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

/** @file planetgraphicsitem.hpp
 */

#ifndef KAMALA_PLANETGRAPHICSITEM_HPP
#define KAMALA_PLANETGRAPHICSITEM_HPP

class QGraphicsItem;
class QGraphicsSceneMouseEvent;
#include <QGraphicsSvgItem>
#include "../kamala_export.hpp"

#include <core.h>

/** @class PlanetGraphicsItem
 *  @brief Graphics SVG item for a planet
 */
class KAMALA_EXPORT PlanetGraphicsItem
    : public QGraphicsSvgItem
{
    Q_OBJECT

  public:

    /** @brief Constructor
     *  @param data Planet positions
     *  @param iWheel Wheel number
     *  @param numWheels Number of wheels in chart
     *  @param parent Parent item
     */
    explicit PlanetGraphicsItem( const PosData& data, int iWheel, int numWheels,
        QGraphicsItem* parent );

    /** @brief Mouse press event handler
     */
    void mousePressEvent( QGraphicsSceneMouseEvent* );

    /** @brief Planet idx
     */
    idx_t       plIdx;

    /** @brief Wheel number
     */
    int     iWheel;

    /** @brief Number of wheels in chart
     */
    int     numWheels;

    /** @brief Highlight flag
     *  Is true if this planet item received a mouse press event and got
     *  "highlighted".
     */
    bool    highlighted;

};

#endif // KAMALA_PLANETGRAPHICSITEM_HPP
