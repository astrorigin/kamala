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

/** @file aspectgraphicsitem.hpp
 */

#ifndef KAMALA_ASPECTGRAPHICSITEM_HPP
#define KAMALA_ASPECTGRAPHICSITEM_HPP

class QGraphicsItem;
#include <QGraphicsLineItem>
#include "../kamala_export.hpp"

#include <core.h>

/** @class AspectGraphicsItem
 *  @brief Graphics line item for aspects
 */
class KAMALA_EXPORT AspectGraphicsItem
    : public QGraphicsLineItem
{
  public:

    /** @brief Constructor
     *  @param data Aspect data
     *  @param parent Parent item
     */
    explicit AspectGraphicsItem( const AspectData& data, QGraphicsItem* parent );

};

#endif // KAMALA_ASPECTGRAPHICSITEM_HPP
