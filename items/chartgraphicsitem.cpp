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

/** @file chartgraphicsitem.cpp
 */

#include "chartgraphicsitem.hpp"

#include <QAction>
#include <QBrush>
#include <QChar>
#include <QColor>
#include <QCursor>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsTextItem>
#include <QLineF>
#include <QMap>
#include <QPair>
#include <QPen>
#include <QPointF>
#include <QTransform>
#include <QVector>

#include <KActionCollection>
#include <KActionMenu>
#include <KDebug>
#include <KLocalizedString>
#include <KMenu>
#include <KSelectAction>

#include "../application.hpp"
#include "../mainwindow.hpp"
#include "../translation.hpp"
#include "aspectgraphicsitem.hpp"
#include "bunch.hpp"
#include "cuspgraphicsitem.hpp"
#include "planetgraphicsitem.hpp"
#include "svgcollection.hpp"
#include "zodiacframegraphicsitem.hpp"
#include "zodiacgraphicsitem.hpp"

extern "C" {
#include <swephexp.h>
}
#include <math.h>
#include <core.h>

#ifdef M_PI
#   define PI      M_PI
#else
#   define PI      3.14159265358979323846
#endif

/* Frequently used pens
 */
static QPen drawPen;
static QPen darkPen;
static QPen middlePen;
static QPen lightPen;

ChartGraphicsItem::ChartGraphicsItem( Chart* ch, QGraphicsItem* parent )
    : QGraphicsRectItem( 0, 0, 720, 720, parent ),
    chart( ch )
{
    setBrush( QBrush( QColor( KamalaApp->core->prefs->bgcolor ) ) );
    setPen( QPen( QColor( Qt::transparent ) ) );
    draw();
}

void ChartGraphicsItem::preparePens()
{
    if ( strequ( KamalaApp->core->prefs->bgcolor, (char*)"#000000" ) )
    { // black bg color
        drawPen = QPen( QColor( Qt::white ) );
        darkPen = QPen( QColor( Qt::lightGray ) );
        middlePen = QPen( QColor( Qt::gray ) );
        lightPen = QPen( QColor( Qt::darkGray ) );
    }
    else
    { // white bg color
        drawPen = QPen( QColor( Qt::black ) );
        darkPen = QPen( QColor( Qt::darkGray ) );
        middlePen = QPen( QColor( Qt::gray ) );
        lightPen = QPen( QColor( Qt::lightGray ) );
    }
    drawPen.setCapStyle( Qt::FlatCap );
    darkPen.setCapStyle( Qt::FlatCap );
    middlePen.setCapStyle( Qt::FlatCap );
    lightPen.setCapStyle( Qt::FlatCap );
}

void ChartGraphicsItem::draw()
{
    if ( chart->type == RadixChartType )
        return draw1();
    else
        return draw2();
}

void ChartGraphicsItem::draw1()
{
    // reset our items lists
    planetItems1.clear();
    planetItems2.clear();
    aspectItems.clear();

    // prepare some vars
    SvgCollection* svgColl = SvgCollection::theme(
        KamalaApp->core->prefs->theme->ptr );

    const bool bgIsBlack = ( strequ( KamalaApp->core->prefs->bgcolor, (char*)"#000000" ) );
    const Wheel* wh = chart->wh1;

    const double vernalAng = swe_degnorm( wh->cusps[1] - 180 );// ascendant on left side
    int i;
    char buf[12];
    BTree* planetsData = chart->wh1->planets;
    Vector* aspectsData = chart->wh1->aspects;

    // loading zodiac frame svg
    ZodiacFrameGraphicsItem* zodFrame;
    if ( bgIsBlack )
    { // black bg color
        zodFrame = new ZodiacFrameGraphicsItem( "",
            svgColl->renderer( chart->ctxt->sidMode != 256 ?
                "zodiac_black_subdiv.svg" : "zodiac_black.svg" ),
            this );
    }
    else
    { // white bg
        zodFrame = new ZodiacFrameGraphicsItem( "",
            svgColl->renderer( chart->ctxt->sidMode != 256 ?
                "zodiac_white_subdiv.svg" : "zodiac_white.svg" ),
            this );
    }
    zodFrame->setTransform( QTransform() // rotation
        .translate( 360, 360 )
        .rotate( vernalAng )
        .translate( -360, -360 ) );

    for ( i = 0; i < 12; ++i )
    { // zodiac signs
        QPointF p;
        if ( chart->ctxt->sidMode != 256 ) // sidmode
            p = toPoint( ( vernalAng - 15 ) - ( i * 30 ), 345, -12.8, -12.8 );
        else
            p = toPoint( ( vernalAng - 15 ) - ( i * 30 ), 330, -25.6, -25.6 );
        ZodiacGraphicsItem* zodItem;
        sprintf( buf, "sign_%.2d.svg", i + 1 );
        zodItem = new ZodiacGraphicsItem(
            translationZodiacSign( i ), svgColl->renderer( buf ), this );
        if ( chart->ctxt->sidMode != 256 )
            zodItem->scale( 0.4, 0.4 );
        else
            zodItem->scale( 0.8, 0.8 );
        zodItem->setPos( p );
    }

    if ( chart->ctxt->sidMode != 256 )
    {
        for ( i = 0; i < 27; ++i )
        { // nakshatras
            QPointF p = toPoint( ( ( vernalAng - ( 40 / 6.0 ) ) - ( i * ( 40 / 3.0 ) ) ), 315, -12.8, -12.8 );
            ZodiacGraphicsItem* nakItem;
            sprintf( buf, "nak_%.2d.svg", i + 1 );
            nakItem = new ZodiacGraphicsItem(
                translationNakshatra( i ), svgColl->renderer( buf ), this );
            nakItem->scale( 0.4, 0.4 );
            nakItem->setPos( p );
            // nakshatra limits
            QGraphicsLineItem* l = new QGraphicsLineItem( this );
            l->setZValue( 1 );
            l->setPen( middlePen );
            QPointF p1 = toPoint( ( vernalAng - ( i * ( 40 / 3.0 ) ) ), 330 );
            QPointF p2 = toPoint( ( vernalAng - ( i * ( 40 / 3.0 ) ) ), 300 );
            l->setLine( QLineF( p1, p2 ) );
        }
    } /* sidmode */

    for ( i = 0; i < 360; ++i )
    { // zodiac degrees
        QGraphicsLineItem* l = new QGraphicsLineItem( this );
        l->setZValue( 1 );
        QPointF p1 = toPoint( vernalAng - i, 299 );
        QPointF p2;
        if ( i % 30 == 0 )
        {
            p2 = toPoint( vernalAng - i, 290 );
            l->setPen( drawPen );
        }
        else if ( i % 10 == 0 )
        {
            p2 = toPoint( vernalAng - i, 292 );
            l->setPen( darkPen );
        }
        else if ( i % 5 == 0 )
        {
            p2 = toPoint( vernalAng - i, 294 );
            l->setPen( middlePen );
        }
        else
        {
            p2 = toPoint( vernalAng - i, 296 );
            l->setPen( lightPen );
        }
        l->setLine( QLineF( p1, p2 ) );
    }

    for ( i = 0; i < 12; ++i )
    { // houses
        CuspGraphicsItem* l = new CuspGraphicsItem( i, wh->cusps[i + 1], this );
        QPointF p1 = toPoint( vernalAng - wh->cusps[i + 1], 225 );
        QPointF p2 = toPoint( vernalAng - wh->cusps[i + 1], 299 );
        l->setLine( QLineF( p1, p2 ) );
        if ( i % 3 == 0 )
            l->setPen( middlePen );
        else
            l->setPen( lightPen );
    }

    // planets
    Vector* vec = NULL;
    posdata_vectorize( planetsData, &vec );
    QList<double> inputPos;
    int cnt = vec->len;
    for ( i = 0; i < cnt; ++i )
        inputPos << ((PosData**)vec->ptr)[i]->res[0];
    BunchBunch bunch( inputPos, 10 );
    QList<double> outputPos = bunch.offer();

    for ( i = 0; i < cnt; ++i )
    { // planet markers
        PosData* pdata = ((PosData**)vec->ptr)[i];
        assert( pdata );
        QGraphicsLineItem* l1 = new QGraphicsLineItem( this );
        QGraphicsLineItem* l2 = new QGraphicsLineItem( this );
        l1->setZValue( 1 );
        l2->setZValue( 1 );
        QPointF p1 = toPoint( vernalAng - pdata->res[0], 225 );
        QPointF p2 = toPoint( vernalAng - pdata->res[0], 230 );
        QPointF p3 = toPoint( vernalAng - outputPos.at( i ), 240 );
        l1->setLine( QLineF( p1, p2 ) );
        l2->setLine( QLineF( p2, p3 ) );
        l1->setPen( drawPen );
        l2->setPen( drawPen );
        // planet glyph
        PlanetGraphicsItem* item = new PlanetGraphicsItem( *pdata, 0, 1, this );
        planetItems1.insert( pdata->planet->_idx, item ); // add to list
        QPointF p4 = toPoint( vernalAng - outputPos.at( i ), 260, -25.6, -25.6 );
        item->scale( 0.8, 0.8 );
        item->setPos( p4 );
    }
    vector_delete( &vec );

    // aspects
    vector_sort( aspectsData,
        (int(*)(const void*, const void*))&aspectdata_zValuesort );

    cnt = aspectsData->len;
    for ( i = 0; i < cnt; ++i )
    {
        AspectData* data = ((AspectData**)aspectsData->ptr)[i];

        PosData* pl1Data = (PosData*)btree_value( planetsData, data->planet1->_idx );
        PosData* pl2Data = (PosData*)btree_value( planetsData, data->planet2->_idx );
        Aspect* asp = data->aspect;

        QPointF pt1 = toPoint( vernalAng - pl1Data->res[0], 225 );
        QPointF pt2 = toPoint( vernalAng - pl2Data->res[0], 225 );
        AspectGraphicsItem* item = new AspectGraphicsItem( *data, this );

        // add aspect to our aspect list
        aspectItems.insert( QPair<int, int>(data->planet1->_idx, data->planet2->_idx), item );

        item->setLine( QLineF( pt1, pt2 ) );

        QPen pen = QPen( QColor( asp->color ) );
        pen.setCapStyle( Qt::FlatCap );

        if ( data->factor > 0.1 )
        {
            QVector<qreal> dash;
            if ( data->factor <= 0.2 )
                dash << 8 << 2;
            else if ( data->factor <= 0.3 )
                dash << 6 << 2;
            else if ( data->factor <= 0.4 )
                dash << 5 << 2;
            else if ( data->factor <= 0.5 )
                dash << 4 << 2;
            else if ( data->factor <= 0.6 )
                dash << 3 << 2;
            else if ( data->factor <= 0.7 )
                dash << 3 << 3;
            else if ( data->factor <= 0.8 )
                dash << 2 << 3;
            else if ( data->factor <= 0.9 )
                dash << 2 << 4;
            else if ( data->factor <= 1 )
                dash << 1 << 4;
            else
                kWarning() << "Invalid factor" << data->factor;

            pen.setDashPattern( dash );
        }
        item->setPen( pen );
    }
#if 0
    /* *** Texts *** */

    Horoscope *horo = m_chart->radix()->info();
    Context *ctxt = m_chart->ctxt();
    //Settings *sett = m_chart->settings();

    QColor dftClr = Preferences::self()->bgColor() == Preferences::WhiteBgColor ?
        QColor(Qt::black) : QColor(Qt::white);

    QStringList buff; // buffer for text

    // left column
    buff << i18nc("@info/plain Chart title", "<b>%1</b>", horo->name());
    QStringList tmpdt = horo->dateTime().toString().split(QChar(' '));
    buff << translatedDayOfWeek(horo->dateTime().dayOfWeek())
        + ", " + tmpdt[0];
    buff << tmpdt[1];
    buff << i18nc("@info/plain Location, Country", "%1, %2",
            horo->location(),
            horo->country());

    int x[3];
    GeoCoord_AsInt(horo->latitude(), x); // latitude
    QString latitudeStr = i18nc("@info/plain Latitude format {deg}:{N|S}:{min}:{sec}",
        "%1:%2:%3:%4",
        x[0],
        horo->latitude() >= 0 ?
            i18nc("@info/plain North", "N")
            : i18nc("@info/plain South", "S"),
       x[1], x[2]);
    if (latitudeStr.endsWith(QString(":0"))) // tmp hack to remove trailing zero
        latitudeStr.remove(latitudeStr.count() - 2, 2);

    GeoCoord_AsInt(horo->longitude(), x); // longitude
    QString longitudeStr = i18nc("@info/plain Longitude format {deg}:{E|W}:{min}:{sec}",
        "%1:%2:%3:%4",
        x[0],
        horo->longitude() >= 0 ?
            i18nc("@info/plain East", "E")
            : i18nc("@info/plain West", "W"),
        x[1], x[2]);
    if (longitudeStr.endsWith(QString(":0"))) // tmp hack to remove trailing zero
        longitudeStr.remove(longitudeStr.count() - 2, 2);

    buff << i18nc("@info/plain Latitude Longitude", "%1 %2",
            latitudeStr, longitudeStr);

    // show altitude only in topocentric mode
    if (ctxt->centering() == Context::TopoCentric)
        buff << i18nc("@info/plain {altitude} meters", "%1 m.", horo->altitude());

    QGraphicsTextItem *txt = new QGraphicsTextItem(this);
    txt->setHtml(buff.join("<br/>"));
    txt->setDefaultTextColor(dftClr);
    txt->setTextInteractionFlags(Qt::TextSelectableByMouse);
    txt->setPos(5, 5);

    // right column (context)
    buff.clear();

    buff << CHARTTYPE_RADIX_STR; // chart type

    buff << SIDEREAL_MODES_STRLIST.at(Context::siderealMode2idx(
        Context::i2SiderealMode(ctxt->siderealMode()))); // todo: make it better

    buff << CENTERING_MODES_STRLIST.at(ctxt->centering());

    buff << HOUSE_SYSTEMS_STRLIST.at( // todo: make it easier
        Context::houseSystem2idx(Context::i2HouseSystem(ctxt->houseSystem())));

    buff.first().prepend("<div align=\"right\">");
    buff.last().append("</div>");

    txt = new QGraphicsTextItem(this);
    txt->setTextWidth(150); // dummy width so that alignment is set
    txt->setHtml(buff.join("<br/>"));
    txt->setDefaultTextColor(dftClr);
    txt->setTextInteractionFlags(Qt::TextSelectableByMouse);
    txt->setPos(715 - txt->boundingRect().width(), 5);

    // objects column info
    PlanetDataItem *plDataItem = new PlanetDataItem(plData, hRes, this);
    plDataItem->setPos(725, 5);

    // aspects info
    AspectDataItem *aspDataItem = new AspectDataItem(aspRes, this);
    aspDataItem->setPos(0, 720);
#endif
}


void ChartGraphicsItem::draw2()
{
#if 0
    // reset our lists
    m_planetItems.clear();
    m_planetItems2.clear();
    m_aspectItems.clear();

    // prepare some vars
    SvgCollection *svgColl = SvgCollection::style(Preferences::self()->theme());
    PlanetCollection *plColl = PlanetCollection::dbCollection();
    AspectCollection *aspColl = AspectCollection::dbCollection();

    HouseDataList hRes1 = m_chart->radix()->results().houses();
    PlanetDataList plRes1 = m_chart->radix()->results().planets();

    HouseDataList hRes2 = m_chart->secondWheel()->results().houses();
    PlanetDataList plRes2 = m_chart->secondWheel()->results().planets();

    AspectDataList aspRes = m_chart->interAspects();

    // ascendant on left side
    double vernalAng = swe_degnorm(hRes1.value(45).longitude - 180);
    int i;

    // prepare pens
    QPen drawPen;
    QPen darkPen;
    QPen middlePen;
    QPen lightPen;
    if (Preferences::self()->bgColor() == Preferences::WhiteBgColor)
    {
        drawPen = QPen(QColor(Qt::black));
        darkPen = QPen(QColor(Qt::darkGray));
        middlePen = QPen(QColor(Qt::gray));
        lightPen = QPen(QColor(Qt::lightGray));
    }
    else // black bg
    {
        drawPen = QPen(QColor(Qt::white));
        darkPen = QPen(QColor(Qt::lightGray));
        middlePen = QPen(QColor(Qt::gray));
        lightPen = QPen(QColor(Qt::darkGray));
    }
    drawPen.setCapStyle(Qt::FlatCap);
    darkPen.setCapStyle(Qt::FlatCap);
    middlePen.setCapStyle(Qt::FlatCap);
    lightPen.setCapStyle(Qt::FlatCap);

    QPen interAspPen = QPen(lightPen);
    interAspPen.setDashPattern(QVector<qreal>() << 2 << 2);
    interAspPen.setCapStyle(Qt::FlatCap);

    // loading zodiac frame svg
    ZodiacFrameGraphicsItem *zodFrame;
    if (Preferences::self()->bgColor() == Preferences::WhiteBgColor)
    {
        zodFrame = new ZodiacFrameGraphicsItem("",
            svgColl->renderer("zodiac2_white.svg"), this);
    }
    else // black bg
    {
        zodFrame = new ZodiacFrameGraphicsItem("",
            svgColl->renderer("zodiac2_black.svg"), this);
    }
    zodFrame->setTransform( // rotation
        QTransform().translate(360, 360).rotate(vernalAng).translate(-360, -360));

    for (i = 0; i < 12; ++i)
    {   // zodiac signs
        QPointF p = toPoint((vernalAng - 15) - (i * 30), 330, -25.6, -25.6);
        ZodiacGraphicsItem *zodItem;
        QString ico = QString("sign_%1.svg").arg(i + 1, 2, 10, QChar('0'));
        zodItem = new ZodiacGraphicsItem(translatedZodiacSign(i), svgColl->renderer(ico), this);
        zodItem->scale(0.8, 0.8);
        zodItem->setPos(p);
    }

    for (i = 0; i < 360; ++i)
    {   // zodiac degrees
        QGraphicsLineItem *l = new QGraphicsLineItem(this);
        l->setZValue(1); // this seems necessary as not all lines appear
        QPointF p1 = toPoint(vernalAng - i, 299);
        QPointF p2;
        if (i % 30 == 0)
        {
            p2 = toPoint(vernalAng - i, 290);
            l->setPen(drawPen);
        }
        else if (i % 10 == 0)
        {
            p2 = toPoint(vernalAng - i, 292);
            l->setPen(darkPen);
        }
        else if (i % 5 == 0)
        {
            p2 = toPoint(vernalAng - i, 294);
            l->setPen(middlePen);
        }
        else
        {
            p2 = toPoint(vernalAng - i, 296);
            l->setPen(lightPen);
        }
        l->setLine(QLineF(p1, p2));
    }

    for (i = 0; i < 12; ++i)
    {   // houses
        CuspGraphicsItem *l = new CuspGraphicsItem(i, hRes1.value(45 + i), this);
        QPointF p1 = toPoint(vernalAng - hRes1.value(45 + i).longitude, 225);
        QPointF p2 = toPoint(vernalAng - hRes1.value(45 + i).longitude, 299);
        l->setLine(QLineF(p1, p2));
        l->setZValue(1); // seems necessary
        if (i % 3 == 0)
        {
            l->setPen(middlePen);
        }
        else
        {
            l->setPen(lightPen);
        }
    }

    // planets 1
    QList<PlanetData> plData1 = plRes1.sortedList();
    QList<double> inputPos;
    int cnt = plData1.count();
    for (i = 0; i < cnt; ++i)
        inputPos << plData1.at(i).longitude;
    BunchBunch bunch(inputPos, 10);
    QList<double> outputPos = bunch.offer();

    for (i = 0; i < cnt; ++i)
    {   // planet markers
        PlanetData data = plData1.at(i);
        QGraphicsLineItem *l1 = new QGraphicsLineItem(this);
        QGraphicsLineItem *l2 = new QGraphicsLineItem(this);
        QGraphicsLineItem *l3 = new QGraphicsLineItem(this);
        l1->setZValue(1); // seem necessary
        l2->setZValue(1);
        l3->setZValue(1);
        QPointF p1 = toPoint(vernalAng - data.longitude, 225);
        QPointF p2 = toPoint(vernalAng - data.longitude, 230);
        QPointF p3 = toPoint(vernalAng - outputPos.at(i), 240);
        QPointF p4 = toPoint(vernalAng - data.longitude, 175);
        l1->setLine(QLineF(p1, p2));
        l2->setLine(QLineF(p2, p3));
        l3->setLine(QLineF(p1, p4));
        l1->setPen(drawPen);
        l2->setPen(drawPen);
        l3->setPen(interAspPen);
        // planet glyph
        Planet *pl = plColl->planet(data.plIdx);
        PlanetItem *item = new PlanetItem(pl, data, 0, 2, this);
        m_planetItems.insert(pl->idx(), item); // add to list
        QPointF p5 = toPoint(vernalAng - outputPos.at(i), 260, -25.6, -25.6);
        item->scale(0.8, 0.8);
        item->setPos(p5);
    }

    // planets 2
    QList<PlanetData> plData2 = plRes2.sortedList();
    inputPos.clear();
    cnt = plData2.count();
    for (i = 0; i < cnt; ++i)
        inputPos << plData2.at(i).longitude;
    BunchBunch bunch2(inputPos, 10);
    outputPos = bunch2.offer();

    for (i = 0; i < cnt; ++i)
    {   // planet markers
        PlanetData data = plData2.at(i);
        QGraphicsLineItem *l1 = new QGraphicsLineItem(this);
        QGraphicsLineItem *l2 = new QGraphicsLineItem(this);
        l1->setZValue(1); // seem necessary
        l2->setZValue(1);
        QPointF p1 = toPoint(vernalAng - data.longitude, 175);
        QPointF p2 = toPoint(vernalAng - data.longitude, 178);
        QPointF p3 = toPoint(vernalAng - outputPos.at(i), 181);

        l1->setLine(QLineF(p1, p2));
        l2->setLine(QLineF(p2, p3));
        l1->setPen(drawPen);
        l2->setPen(drawPen);
        // planet glyph
        Planet *pl = plColl->planet(data.plIdx);
        PlanetItem *item = new PlanetItem(pl, data, 1, 2, this);
        m_planetItems2.insert(pl->idx(), item); // add to list
        QPointF p4 = toPoint(vernalAng - outputPos.at(i), 200, -19.2, -19.2);
        item->scale(0.6, 0.6);
        item->setPos(p4);
    }

    // aspects
    aspRes.sort();
    cnt = aspRes.count();
    for (i = 0; i < cnt; ++i)
    {
        AspectData data = aspRes.at(i);
        PlanetData pl1Data = plRes1.value(data.pl1Idx);
        PlanetData pl2Data = plRes2.value(data.pl2Idx);
        Aspect *asp = aspColl->aspect(data.aspIdx);

        QPointF pt1 = toPoint(vernalAng - pl1Data.longitude, 175);
        QPointF pt2 = toPoint(vernalAng - pl2Data.longitude, 175);
        AspectItem *item = new AspectItem(asp, data, this);

        // add aspect to our aspect list
        m_aspectItems.insert(QPair<int, int>(data.pl1Idx, data.pl2Idx), item);

        item->setLine(QLineF(pt1, pt2));

        QPen pen = QPen(QColor(asp->color()));
        pen.setCapStyle(Qt::FlatCap);
        if (data.factor > 0.1)
        {
            QVector<qreal> dash;
            if (data.factor <= 0.2)
                dash << 8 << 2;
            else if (data.factor <= 0.3)
                dash << 6 << 2;
            else if (data.factor <= 0.4)
                dash << 5 << 2;
            else if (data.factor <= 0.5)
                dash << 4 << 2;
            else if (data.factor <= 0.6)
                dash << 3 << 2;
            else if (data.factor <= 0.7)
                dash << 3 << 3;
            else if (data.factor <= 0.8)
                dash << 2 << 3;
            else if (data.factor <= 0.9)
                dash << 2 << 4;
            else if (data.factor <= 1)
                dash << 1 << 4;
            else
                kWarning() << "Invalid factor" << data.factor;

            pen.setDashPattern(dash);
        }
        item->setPen(pen);
    }

    /* *** Texts *** */

    Horoscope *horo = m_chart->radix()->info();
    Horoscope *horo2 = m_chart->secondWheel()->info();

    Context *ctxt = m_chart->ctxt();
    //Settings *sett = m_chart->settings();

    QColor dftClr = Preferences::self()->bgColor() == Preferences::WhiteBgColor ?
        QColor(Qt::black) : QColor(Qt::white);

    QStringList buff; // buffer for text

    // left column
    buff << i18nc("@info/plain Chart title", "<b>%1</b>", horo->name());
    QStringList tmpdt = horo->dateTime().toString().split(QChar(' '));
    buff << translatedDayOfWeek(horo->dateTime().dayOfWeek())
        + ", " + tmpdt[0];
    buff << tmpdt[1];
    buff << i18nc("@info/plain Location, Country", "%1, %2",
            horo->location(),
            horo->country());

    int x[3];
    GeoCoord_AsInt(horo->latitude(), x); // latitude
    QString latitudeStr = i18nc("@info/plain Latitude format {deg}:{N|S}:{min}:{sec}",
        "%1:%2:%3:%4",
        x[0],
        horo->latitude() >= 0 ?
            i18nc("@info/plain North", "N")
            : i18nc("@info/plain South", "S"),
       x[1], x[2]);
    if (latitudeStr.endsWith(QString(":0"))) // tmp hack to remove trailing zero
        latitudeStr.remove(latitudeStr.count() - 2, 2);

    GeoCoord_AsInt(horo->longitude(), x); // longitude
    QString longitudeStr = i18nc("@info/plain Longitude format {deg}:{E|W}:{min}:{sec}",
        "%1:%2:%3:%4",
        x[0],
        horo->longitude() >= 0 ?
            i18nc("@info/plain East", "E")
            : i18nc("@info/plain West", "W"),
        x[1], x[2]);
    if (longitudeStr.endsWith(QString(":0"))) // tmp hack to remove trailing zero
        longitudeStr.remove(longitudeStr.count() - 2, 2);

    buff << i18nc("@info/plain Latitude Longitude", "%1 %2",
            latitudeStr, longitudeStr);

    // show altitude only in topocentric mode
    if (ctxt->centering() == Context::TopoCentric)
        buff << i18nc("@info/plain {altitude} meters", "%1 m.", horo->altitude());

    QGraphicsTextItem *txt = new QGraphicsTextItem(this);
    txt->setHtml(buff.join("<br/>"));
    txt->setDefaultTextColor(dftClr);
    txt->setTextInteractionFlags(Qt::TextSelectableByMouse);
    txt->setPos(5, 5);


    // second wheel
    buff.clear();

    buff << i18nc("@info/plain Chart title", "<b>%1</b>", horo2->name());
    tmpdt = horo2->dateTime().toString().split(QChar(' '));
    buff << translatedDayOfWeek(horo2->dateTime().dayOfWeek())
        + ", " + tmpdt[0];
    buff << tmpdt[1];
    buff << i18nc("@info/plain Location, Country", "%1, %2",
            horo2->location(),
            horo2->country());

    GeoCoord_AsInt(horo2->latitude(), x); // latitude
    latitudeStr = i18nc("@info/plain Latitude format {deg}:{N|S}:{min}:{sec}",
        "%1:%2:%3:%4",
        x[0],
        horo2->latitude() >= 0 ?
            i18nc("@info/plain North", "N")
            : i18nc("@info/plain South", "S"),
       x[1], x[2]);
    if (latitudeStr.endsWith(QString(":0"))) // tmp hack to remove trailing zero
        latitudeStr.remove(latitudeStr.count() - 2, 2);

    GeoCoord_AsInt(horo2->longitude(), x); // longitude
    longitudeStr = i18nc("@info/plain Longitude format {deg}:{E|W}:{min}:{sec}",
        "%1:%2:%3:%4",
        x[0],
        horo2->longitude() >= 0 ?
            i18nc("@info/plain East", "E")
            : i18nc("@info/plain West", "W"),
        x[1], x[2]);
    if (longitudeStr.endsWith(QString(":0"))) // tmp hack to remove trailing zero
        longitudeStr.remove(longitudeStr.count() - 2, 2);

    buff << i18nc("@info/plain Latitude Longitude", "%1 %2",
            latitudeStr, longitudeStr);

    // show altitude only in topocentric mode
    if (ctxt->centering() == Context::TopoCentric)
        buff << i18nc("@info/plain {altitude} meters", "%1 m.", horo2->altitude());

    txt = new QGraphicsTextItem(this);
    txt->setHtml(buff.join("<br/>"));
    txt->setDefaultTextColor(dftClr);
    txt->setTextInteractionFlags(Qt::TextSelectableByMouse);
    txt->setPos(5, 620);


    // right column (context)
    buff.clear();

    buff << CHARTTYPE_COMPARED_STR; // chart type

    buff << SIDEREAL_MODES_STRLIST.at(Context::siderealMode2idx(
        Context::i2SiderealMode(ctxt->siderealMode()))); // todo: make it better

    buff << CENTERING_MODES_STRLIST.at(ctxt->centering());

    buff << HOUSE_SYSTEMS_STRLIST.at( // todo: make it easier
        Context::houseSystem2idx(Context::i2HouseSystem(ctxt->houseSystem())));

    buff.first().prepend("<div align=\"right\">");
    buff.last().append("</div>");

    txt = new QGraphicsTextItem(this);
    txt->setTextWidth(150); // dummy width so that alignment is set
    txt->setHtml(buff.join("<br/>"));
    txt->setDefaultTextColor(dftClr);
    txt->setTextInteractionFlags(Qt::TextSelectableByMouse);
    txt->setPos(715 - txt->boundingRect().width(), 5);

    // objects 1 column info
    PlanetDataItem *plDataItem1 = new PlanetDataItem(plData1, hRes1, this);
    plDataItem1->setPos(725, 5);

    // objects 2 column info
    PlanetDataItem *plDataItem2 = new PlanetDataItem(plData2, hRes2, this);
    plDataItem2->setPos(725, 765);

    // aspects info
    AspectDataItem *aspDataItem = new AspectDataItem(aspRes, this);
    aspDataItem->setPos(0, 720);
#endif
}


QPointF ChartGraphicsItem::toPoint(double ang, double hyp, double modx, double mody)
{
    double x = ( cos( ( PI / 180 ) * ang ) * hyp ) + modx;
    double y = ( sin( ( PI / 180 ) * ang ) * hyp ) + mody;
    return QPointF( x + 360, y + 360 );
}

void ChartGraphicsItem::contextMenuEvent( QGraphicsSceneContextMenuEvent* ev )
{
#if 0
    Q_UNUSED( ev );

    KActionCollection* coll = MainWindow::self()->actionCollection();
    KActionMenu *menu = new KActionMenu( "Settings", (QObject*) 0 );

    KSelectAction* settings1Action = (KSelectAction*) coll->action( "settingsWheel1" );
    menu->addAction( settings1Action );

    KSelectAction* contextAction = (KSelectAction*) coll->action( "chartContext" );
    menu->addAction( contextAction );

    menu->menu()->exec( QCursor::pos() );

    delete menu;
#endif
}
