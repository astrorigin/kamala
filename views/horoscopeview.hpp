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

/** @file horoscopeview.hpp
 */

#ifndef KAMALA_HOROSCOPEVIEW_HPP
#define KAMALA_HOROSCOPEVIEW_HPP

class QContextMenuEvent;
class QMouseEvent;
#include <QPixmap>
#include <QPoint>
#include <QTableView>
class QWidget;
class KActionMenu;
#include "../kamala_export.hpp"

#include <core.h>

class HoroscopeProxyModel;

/** @class HoroscopeView
 *  @brief View on the horoscope database
 */
class KAMALA_EXPORT HoroscopeView
    : public QTableView
{
    Q_OBJECT

  public:

    /** @brief Pointer to the local context menu
     */
    KActionMenu*        contextMenu;

    /** @brief Constructor
     *  @param model Proxy model
     *  @param parent Parent widget
     */
    explicit HoroscopeView( HoroscopeProxyModel* model, QWidget* parent );

    /** @brief Get currently selected horoscope, if any
     */
    Horoscope* selectedHoroscope() const;

    /** @brief Context menu event handler
     */
    void contextMenuEvent( QContextMenuEvent* );

    /** @brief Selection change handler
     *  Reset actions.
     */
    void selectionChanged( const QItemSelection&, const QItemSelection& );

    /** @brief Mouse press event handler
     *  Prepare drag operation.
     */
    void mousePressEvent( QMouseEvent* );

    /** @brief Mouse move event handler
     *  Initiate drag operation if appropriate.
     */
    void mouseMoveEvent( QMouseEvent* );

  private:

    /** @brief This point records the last mouse press position
     */
    QPoint      _dragStartPos;

    /** @brief This records the last horoscope idx pressed by mouse (or -1)
     */
    int         _dragIndex;

    /** @brief Pixmap for cursor (drag operation)
     */
    const QPixmap       _dragPix;
};

#endif // KAMALA_HOROSCOPEVIEW_HPP
