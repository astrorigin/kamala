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

/** @file kgeonamesquery.hpp
 */

#ifndef KGEONAMESQUERY_HPP
#define KGEONAMESQUERY_HPP

#include <QObject>
class QString;
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QThread>

#include "kgeoname.hpp"
#include "kgeonames_export.hpp"

/** @class KGeoNamesQuery
 *  @brief Query GeoNames.org database
 */
class GEONAMES_EXPORT KGeoNamesQuery
    : public QNetworkAccessManager
{
    Q_OBJECT

  public:

    /** @brief The network reply
     */
    QNetworkReply*      networkReply;

    /** @brief The results list
     */
    QList<KGeoName>     resultsList;

    /** @brief Constructor
     *  @param name The name searched
     *  @param parent Parent object
     */
    explicit KGeoNamesQuery( const QString& name, QObject* parent=0 );

    /** @brief Destructor
     */
    virtual ~KGeoNamesQuery();

  Q_SIGNALS:

    /** @brief Signal normal end of query
     */
    void success();

    /** @brief Signal xml error
     *  @param msg Error message
     */
    void xmlError( const QString& msg );

    /** @brief Signal network error
     *  @param code Network error code
     */
    void networkError( QNetworkReply::NetworkError code );

  private Q_SLOTS:

    /** @brief Query error handler
     */
    void queryError( QNetworkReply::NetworkError code ) const;

    /** @brief Query finished handler
     */
    void queryFinished();

};

/** @class KGeoNamesAsyncQuery
 *  @brief Query GeoNames.org asynchronously
 */
class GEONAMES_EXPORT KGeoNamesAsyncQuery
    : public QThread
{
    Q_OBJECT

  public:

    /** @brief Constructor
     *  @param name The name searched
     *  @param parent Parent object
     */
    explicit KGeoNamesAsyncQuery( const QString& name, QObject* parent=0 );

    /** @brief Destructor
     */
    virtual ~KGeoNamesAsyncQuery();

    /** @brief Pointer to the results
     *  Is null if there is no successful query done.
     */
    QList<KGeoName>* resultsList() const;

  private:

    /** @brief The query object used internaly
     */
    KGeoNamesQuery*     query;

    /** @brief The name searched
     */
    QString     name;

    /** @brief The search process
     */
    void run();

};

#endif // KGEONAMESQUERY_HPP
