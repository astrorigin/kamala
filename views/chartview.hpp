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

/** @file chartview.hpp
 */

#ifndef KAMALA_CHARTVIEW_HPP
#define KAMALA_CHARTVIEW_HPP

class QContextMenuEvent;
class QItemSelection;
class QMouseEvent;
#include <QPixmap>
#include <QPoint>
#include <QTableView>
class QWidget;
class KActionMenu;
#include "../kamala_export.hpp"

#include <core.h>

class ChartModel;

/** @class ChartView
 *  @brief View of currently opened charts
 */
class KAMALA_EXPORT ChartView
    : public QTableView
{
    Q_OBJECT

  public:

    /** @brief Pointer to local context menu
     */
    KActionMenu*    contextMenu;

    /** @brief Constructor
     */
    explicit ChartView( const ChartModel*, QWidget* parent );

    /** @brief Currently selected chart, if any
     */
    Chart* selectedChart() const;

    /** @brief Context menu event handler
     */
    void contextMenuEvent( QContextMenuEvent* );

    /** @brief Selection change handler
     *  Activate the corresponding subwindow.
     */
    void selectionChanged( const QItemSelection&, const QItemSelection& );

    /** @brief Mouse press event handler
     *  Prepare drag operation
     */
    void mousePressEvent( QMouseEvent* );

    /** @brief Mouse move event handler
     *  Initiate drag operation if appropriate.
     */
    void mouseMoveEvent( QMouseEvent* );

  public Q_SLOTS:

    /** @brief Mouse double click handler
     *  Edit first wheel data.
     */
    void viewDoubleClicked( const QModelIndex& );

  private:

    /** @brief This point records the last mouse press position
     */
    QPoint      _dragStartPos;

    /** @brief This records the index of the last chart mouse pressed on (or -1)
     */
    int         _dragIndex;

    /** @brief Pixmap for cursor (drag operation)
     */
    const QPixmap       _dragPix;

};

#endif // KAMALA_CHARTVIEW_HPP
