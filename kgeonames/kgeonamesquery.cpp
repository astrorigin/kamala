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

/** @file kgeonamesquery.cpp
*/

#include "kgeonamesquery.hpp"

#include <QObject>
#include <QString>
#include <QList>
#include <QListIterator>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QXmlStreamReader>
#include <QThread>

#include <KDebug>

#include "kgeoname.hpp"

KGeoNamesQuery::KGeoNamesQuery( const QString& name, QObject* parent )
    : QNetworkAccessManager( parent )
{
    //kDebug() << "Querying GeoNames.org for" << name;

    QNetworkRequest req;
    req.setUrl( QString(
        "http://ws.geonames.org/search?q=%1&featureClass=P&style=FULL" )
        .arg( name ) );

    networkReply = this->get( req );

    connect( networkReply, SIGNAL( error( QNetworkReply::NetworkError ) ),
        this, SLOT( queryError( QNetworkReply::NetworkError ) ) );
    connect( networkReply, SIGNAL( error( QNetworkReply::NetworkError ) ),
        this, SIGNAL( networkError( QNetworkReply::NetworkError ) ) );
    connect( networkReply, SIGNAL( finished() ), this, SLOT( queryFinished() ) );
}

KGeoNamesQuery::~KGeoNamesQuery()
{
    delete networkReply;
}

void KGeoNamesQuery::queryError( QNetworkReply::NetworkError code ) const
{
    kWarning() << "Network error:" << code;
}

void KGeoNamesQuery::queryFinished()
{
    QByteArray data = networkReply->readAll();
    //kDebug() << "GeoNames query finished:" << data;

    QXmlStreamReader xml( data );
    int tokenType;
    while ( !xml.atEnd() )
    {
        tokenType = xml.readNext();
        if ( tokenType != QXmlStreamReader::StartElement || xml.name() != "geoname" )
            continue;

        KGeoName res;

        while ( tokenType != QXmlStreamReader::StartElement || xml.name() != "name" )
            tokenType = xml.readNext();
        res.name = xml.readElementText();

        while ( tokenType != QXmlStreamReader::StartElement || xml.name() != "lat" )
            tokenType = xml.readNext();
        res.latitude = xml.readElementText().toDouble();

        while ( tokenType != QXmlStreamReader::StartElement || xml.name() != "lng" )
            tokenType = xml.readNext();
        res.longitude = xml.readElementText().toDouble();

        while ( tokenType != QXmlStreamReader::StartElement || xml.name() != "countryName" )
            tokenType = xml.readNext();
        res.country = xml.readElementText();

        while ( tokenType != QXmlStreamReader::StartElement || xml.name() != "timezone" )
            tokenType = xml.readNext();
        res.timezone = xml.readElementText();

        /* todo... Querying for elevation uses another network query to geonames.org.
         * As there is a limitation to the number of requests one IP can send
         * in one day, it is maybe not really worth it.
         */
        res.elevation = 0;

        resultsList << res;
    }

    if ( xml.hasError() )
    {
        kWarning() << xml.errorString() << xml.lineNumber() << xml.columnNumber();
        emit xmlError( xml.errorString() );
    }
    else emit success();
}

KGeoNamesAsyncQuery::KGeoNamesAsyncQuery( const QString& nam, QObject* parent )
    : QThread( parent ),
    query( 0 ),
    name( nam ) {}

KGeoNamesAsyncQuery::~KGeoNamesAsyncQuery()
{
    if ( query ) delete query;
}

QList<KGeoName>* KGeoNamesAsyncQuery::resultsList() const
{
    if ( query )
        return &query->resultsList;
    else
        return 0;
}

void KGeoNamesAsyncQuery::run()
{
    query = new KGeoNamesQuery( name );

    connect( query, SIGNAL( networkError( QNetworkReply::NetworkError ) ),
        this, SLOT( terminate() ) );
    connect( query, SIGNAL( xmlError( const QString& ) ),
        this, SLOT( terminate() ) );
    connect( query, SIGNAL( success() ), this, SLOT( quit() ) );

    exec();
}
