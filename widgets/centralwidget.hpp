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

/** @file centralwidget.hpp
 */

#ifndef KAMALA_CENTRALWIDGET_HPP
#define KAMALA_CENTRALWIDGET_HPP

class QDragEnterEvent;
class QDropEvent;
#include <QMdiArea>
class QString;
class QWidget;
#include "../kamala_export.hpp"

#include <core.h>

/** @class CentralWidget
 *  @brief Kamala central widget, containing charts subwindows
 */
class KAMALA_EXPORT CentralWidget
    : public QMdiArea
{
    Q_OBJECT

  public:

    /** @brief Constructor
     */
    explicit CentralWidget( QWidget* parent );

    /** @brief Drag enter event handler
     */
    void dragEnterEvent( QDragEnterEvent* );

    /** @brief Drop event handler
     *  @see MainWindow::internalOpenChart
     */
    void dropEvent( QDropEvent* );

  public Q_SLOTS:

    /** @brief Activate a chart subwindow
     *  Triggered from chart view (dock widget), etc.
     *  @param iWin Subwindow index
     */
    void setActiveSubWindow( int iWin );

    /** @brief Create a new subwindow with the given chart
     *  @param ch Newly created chart
     */
    void addSubWindow( Chart* ch );

    /** @brief Close a subwindow
     *  @param iWin Subwindow index, or -1 for current subwindow
     */
    void closeSubWindow( int iWin ) const;

    /** @brief Close all subwindows
     */
    void closeAllSubWindows() const;
#if 0
    void stepBack();

    void stepForward();

    void zoomIn() const;

    void zoomOut() const;

    void saveChartAsImage( const QString &path ) const;



    void slotChartChanged( ChartCollection *coll, Chart *ch );
#endif

};

#endif // KAMALA_CENTRALWIDGET_HPP
