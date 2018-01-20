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

/** @file zodiacgraphicsitem.hpp
 */

#ifndef KAMALA_ZODIACGRAPHICSITEM_HPP
#define KAMALA_ZODIACGRAPHICSITEM_HPP

class QGraphicsItem;
#include <QGraphicsSvgItem>
class QSvgRenderer;
#include "../kamala_export.hpp"

/** @class ZodiacGraphicsItem
 *  @brief Svg graphics item with a zodiac sign
 */
class KAMALA_EXPORT ZodiacGraphicsItem
    : public QGraphicsSvgItem
{
    Q_OBJECT

  public:

    /** @brief Constructor
     *  @param name Name of zodiac sign, for tooltip etc
     *  @param renderer Svg renderer
     *  @param parent Parent item
     */
    explicit ZodiacGraphicsItem( const QString& name, QSvgRenderer* renderer,
        QGraphicsItem* parent );

};

#endif // KAMALA_ZODIACGRAPHICSITEM_HPP
