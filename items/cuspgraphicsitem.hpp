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

/** @file cuspgraphicsitem.hpp
 */

#ifndef KAMALA_CUSPGRAPHICSITEM_HPP
#define KAMALA_CUSPGRAPHICSITEM_HPP

class QGraphicsItem;
#include <QGraphicsLineItem>
#include "../kamala_export.hpp"

#include <core.h>

/** @class CuspGraphicsItem
 *  @brief Graphics line item for houses cusps
 */
class KAMALA_EXPORT CuspGraphicsItem
    : public QGraphicsLineItem
{
  public:

    /** @brief Constructor
     *  @param cusp Number [0;11]
     *  @param longitude House position
     *  @param parent Parent item
     */
    explicit CuspGraphicsItem( int cusp, double longitude, QGraphicsItem* parent );

};

#endif // KAMALA_CUSPGRAPHICSITEM_HPP
