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

/** @file orbwidget.hpp
 */

#ifndef KAMALA_ORBWIDGET_HPP
#define KAMALA_ORBWIDGET_HPP

class QString;
#include <QWidget>
class KDoubleNumInput;
#include "../kamala_export.hpp"

#include <core.h>

/** @class OrbWidget
 *  @brief Widget for orbs
 */
class KAMALA_EXPORT OrbWidget
    : public QWidget
{
    Q_OBJECT

  public:

    /** @brief Constructor
     *  @param label Widget label
     *  @param orb Initial orb value
     *  @param parent Parent widget
     */
    explicit OrbWidget( const QString& label, const Orb& orb, QWidget* parent );

    /** @brief Get widget current orb value
     *  @param ret Returned orb value
     */
    Orb* orb( Orb* ret ) const;

  public Q_SLOTS:

    /** @brief Reset widget orb to initial value
     */
    void reset();

    /** @brief Set widget orb value
     *  @param orb Orb value
     */
    void setOrb( const Orb& orb );

  private:

    /** @brief Initial value
     */
    Orb     _orb;

    /** @brief Applying part
     */
    KDoubleNumInput*    orbAppInput;

    /** @brief Separating part
     */
    KDoubleNumInput*    orbSepInput;

    /** @brief Stable part
     */
    KDoubleNumInput*    orbStaInput;

};

#endif // KAMALA_ORBWIDGET_HPP
