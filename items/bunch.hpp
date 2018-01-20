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

/** @file bunch.hpp
 *  @brief Classes to arrange the planets positions
 */

#ifndef KAMALA_BUNCH_HPP
#define KAMALA_BUNCH_HPP

#include <QList>
#include <QPair>
#include "../kamala_export.hpp"

/** @class Bunch
 *  @brief A group of planets
 */
class KAMALA_EXPORT Bunch
    : public QList<double>
{
  public:

    explicit Bunch( double width, double pos );

    void addFlower( double pos );

    void calcCenter();

    bool acceptFlower( double pos ) const;

    bool acceptBunch( Bunch* other ) const;

    void addBunch( const Bunch& other );

    double orb() const;

    static bool mySort( double x, double y );

    QList<QPair<double, double> > arrange();

    double      width;

    double      center;

};

/** @class BunchBunch
 *  @brief Many groups of planets
 */
class KAMALA_EXPORT BunchBunch
    : public QList<Bunch*>
{
  public:

    explicit BunchBunch( const QList<double>& input, double width );

    virtual ~BunchBunch();

    void addFlower( double pos );

    void newBunch( double pos );

    void arrange();

    QList<double> offer();

    bool subArrange();

    QList<double>       input;

    double      width;

};

#endif // KAMALA_BUNCH_HPP
