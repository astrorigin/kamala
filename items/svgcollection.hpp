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

/** @file svgcollection.hpp
 */

#ifndef KAMALA_SVGCOLLECTION_HPP
#define KAMALA_SVGCOLLECTION_HPP

#include <QByteArray>
#include <QMap>
class QSvgRenderer;
#include "../kamala_export.hpp"

/** @class SvgCollection
 *  @brief This class manages the SVG files
 */
class KAMALA_EXPORT SvgCollection
    : public QMap<QByteArray, QSvgRenderer*>
{
  public:

    /** @brief Get a SVG collection
     *  @param style SVG theme and directory name ("default", ...)
     */
    static SvgCollection* theme( const char* style );

    /** @brief Get a Svg renderer of given file name
     *  @param file File name relative to the collection directory
     *  @param clr Change object color (only when loaded the first time)
     */
    QSvgRenderer* renderer( const char* file, const char* clr="" );

    /** @brief Destructor
     */
    virtual ~SvgCollection();

  private:

    /** @brief Constructor
     *  @param style Theme name
     */
    explicit SvgCollection( const char* style );

    /** @brief The theme in use
     */
    const QByteArray        style;

};

#endif // KAMALA_SVGCOLLECTION_HPP
