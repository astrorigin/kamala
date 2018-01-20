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

/** @file svgcollection.cpp
 */

#include "svgcollection.hpp"

#include <QByteArray>
#include <QDomNode>
#include <QMap>
#include <QMapIterator>
#include <QSvgRenderer>

#include <KDebug>
#include <KGameSvgDocument>
#include <KStandardDirs>

static QMap<QByteArray, SvgCollection*> s_svgCollections; // all svg collections

SvgCollection::SvgCollection( const char* styl )
    : style( styl ) {}

SvgCollection::~SvgCollection()
{
    QMapIterator<QByteArray, QSvgRenderer*> iter( *this );
    while ( iter.hasNext() )
    {
        iter.next();
        delete iter.value();
    }
}

SvgCollection* SvgCollection::theme( const char* style )
{
    SvgCollection* coll = s_svgCollections.value(
        QByteArray::fromRawData( style, qstrlen( style ) ) );

    if ( !coll )
    {
        coll = new SvgCollection( style );
        s_svgCollections.insert( QByteArray( style ), coll );
    }
    return coll;
}

QSvgRenderer* SvgCollection::renderer( const char* file, const char* clr )
{
    const QByteArray ba = QByteArray::fromRawData( file, qstrlen( file ) );

    if ( !contains( ba ) )
    { // loading svg file
        QString path = KStandardDirs::locate( "data",
            QString( "kamala/themes/%1/%2" ).arg( style.constData() ).arg( file ) );

        QSvgRenderer* render = NULL;

        if ( clr[0] != '\0' )
        { // change object color
            KGameSvgDocument doc;
            doc.load( path );
            QDomNode node = doc.elementById( "kamala" );
            if ( node.isNull() )
            { // element not found
                kWarning() << "Unable to change color for file" << file;
                render = new QSvgRenderer( path );
            }
            else
            {
                doc.setStyleProperty( "fill", clr );
                render = new QSvgRenderer( doc.toByteArray() );
            }
        }
        else
        { // no color change
            if ( path.isEmpty() )
                kWarning() << "Unable to find svg file" << file;
            render = new QSvgRenderer( path );
        }
        Q_ASSERT( render );
        insert( QByteArray( file ), render );
        return render;
    }
    return value( ba );
}
