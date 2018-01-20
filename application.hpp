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

/** @file application.hpp
 */

#ifndef KAMALA_APPLICATION_HPP
#define KAMALA_APPLICATION_HPP

#include <QStringList>
#include <KApplication>
#include "kamala_export.hpp"

#include <core.h>

class ChartModel;
class HoroscopeModel;
class HoroscopeProxyModel;
class MainWindow;

/** @def KamalaApp
 *  @brief Pointer to the current Kamala application
 */
#define KamalaApp       (KamalaApplication::self())


/** @class KamalaApplication
 *  @brief Kamala application
 */
class KAMALA_EXPORT KamalaApplication
    : public KApplication
{
    Q_OBJECT

  public:

    /** @brief Pointer to current application
     *  @see Macro KamalaApp
     */
    static const KamalaApplication* self()
        { return (const KamalaApplication*) KApplication::KApp; }

    /** @brief Pointer to ZodiaCore
     */
    ZodiaCore*      core;

    /** @brief Pointer to the horoscope database model
     */
    HoroscopeModel*     horoscopeModel;

    /** @brief Pointer to horoscope proxy model
     */
    HoroscopeProxyModel*    horoscopeProxyModel;

    /** @brief Pointer to currently opened charts model
     */
    ChartModel*     chartModel;

    /** @brief Pointer to main window
     */
    MainWindow*     mainWindow;

    /** @brief Constructor
     *  Start the application.
     */
    explicit KamalaApplication();

    /** @brief Destructor
     */
    virtual ~KamalaApplication();

    /** @brief Get string list of contexts, sorted alphabeticaly
     */
    QStringList contextsStringList() const;

    /** @brief Get string list of profiles, sorted alphabeticaly
     */
    QStringList profilesStringList() const;

};

#endif // KAMALA_APPLICATION_HPP
