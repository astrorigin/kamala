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

/** @file subwindow.cpp
 */

#include "subwindow.hpp"

#include <QCloseEvent>
// #include <QImage>
#include <QMdiArea>
#include <QMdiSubWindow>
// #include <QPainter>
#include <QResizeEvent>
#include <QString>
#include <QWidget>
// #include <KActionCollection>
#include <KDebug>
// #include <KMessageBox>
// #include <KSelectAction>

#include "../application.hpp"
#include "../mainwindow.hpp"
#include "../views/chartgraphicsview.hpp"

#include <core.h>
//#include <swephexp.h>

SubWindow::SubWindow( Chart* ch, QWidget* parent )
    : QMdiSubWindow( parent, Qt::SubWindow )
{
    setAttribute( Qt::WA_DeleteOnClose );

    chart = ch;

    setWindowTitle( QString::fromUtf8( ch->wh1->horo->name->ptr ) );

    ChartGraphicsView* view = new ChartGraphicsView( ch, this );
    setWidget( (QWidget*) view );


    if ( KamalaApp->core->prefs->openMaximized )
        showMaximized();
    else
        resize( 755, 775 );
}

void SubWindow::closeEvent( QCloseEvent* ev )
{
    KamalaApp->mainWindow->internalSubWindowCloseEvent(
        mdiArea()->subWindowList().indexOf( this ) );
    ev->accept();
}

void SubWindow::resizeEvent( QResizeEvent* ev )
{
    const QSize sz = ev->size();
    ChartGraphicsView* view = (ChartGraphicsView*) widget();

    // is this supposed to work ???
    //view->fitInView( 0, 0, 720, 720, Qt::IgnoreAspectRatio );

    // this works...
    view->resetMatrix();
    view->scale( sz.width() / 755.0, sz.height() / 775.0 );

    view->centerOn( 0, 0 );
}

void SubWindow::reload()
{
    setWindowTitle( QString::fromUtf8( chart->wh1->horo->name->ptr ) );
    ((ChartGraphicsView*)widget())->reload();
}

#if 0
void SubWindow::zoomIn() const
{
    GraphicsView *view = (GraphicsView*) widget();
    view->scale( 1.1, 1.1 );
}

void SubWindow::zoomOut() const
{
    GraphicsView *view = (GraphicsView*) widget();
    view->scale( 0.9, 0.9 );
}

void SubWindow::saveChartAsImage( const QString &path )
{ // todo: make img size changeable etc
    QImage img( 1080, 1527, QImage::Format_ARGB32_Premultiplied );
    QPainter painter( &img );
    ((GraphicsView*) widget())->scene()->render( &painter );

    if ( img.save( path ) )
    {
        kDebug() << "Image successfully saved as" << path;
        KMessageBox::information( this,
            i18nc( "@info", "Image successfully saved as <filename>%1</filename>.", path ),
            i18nc( "@title:window", "Image Saved" ) );
    }
    else
    {
        kWarning() << "Unable to save image" << path;
        KMessageBox::error( this,
            i18nc( "@info", "<warning>Unable to save image with path "
                   "<filename>%1</filename> !</warning>", path ),
            i18nc( "@title:window", "Error" ) );
    }
}

void SubWindow::stepBack()
{
    int i = mdiArea()->subWindowList().indexOf(this);
    ChartCollection *coll = ChartCollection::openedCharts();
    Chart *ch = coll->chart(i);
    Horoscope *horo = ch->radix()->info();
    Context *ctxt = ch->context();
    //Settings *sett = ch->settings();
    WheelResults res = ch->radix()->results();

    KActionCollection *actions = KActionCollection::allCollections().at(0);
    KSelectAction *stepType = (KSelectAction*) actions->action("stepTypeWheel1");

    if (stepType->currentItem() == 0)
    { // time step
        DateTime dt = horo->dateTime();
        KSelectAction *stepValue = (KSelectAction*) actions->action("timeStepValueWheel1");
        int iStepValue = stepValue->currentText().toInt();
        KSelectAction *stepUnit = (KSelectAction*) actions->action("timeStepUnitWheel1");
        int iStepUnit = stepUnit->currentItem();
        switch (iStepUnit)
        {
            case 0: dt.addSeconds(- iStepValue); break;
            case 1: dt.addMinutes(- iStepValue); break;
            case 2: dt.addHours(- iStepValue); break;
            case 3: dt.addDays(- iStepValue); break;
            case 4: dt.addMonths(- iStepValue); break;
            case 5: dt.addYears(- iStepValue); break;
            default:
                kWarning() << "Invalid step unit";
        }
        Q_ASSERT(dt.isValid());
        horo->setDateTime(dt);
    }
    else if (stepType->currentItem() == 1)
    { // space step
        KSelectAction *stepAxis = (KSelectAction*) actions->action("spaceStepAxisWheel1");
        if (stepAxis->currentItem() == 0)
        { // north/south axis
            GeoLat coord = horo->latitude();
            if (!GeoLat_Check(coord - 1))
            { // invalid latitude
                KMessageBox::error(this,
                    i18nc("@info", "<warning>Minimal latitude reached !</warning>"),
                    i18nc("@title:window", "Error"));
                return;
            }
            horo->setLatitude(coord - 1);
        }
        else
        { // east/west axis
            GeoLon coord = horo->longitude();
            if (!GeoLon_Check(coord - 1))
            { // invalid longitude
                KMessageBox::error(this,
                    i18nc("@info", "<warning>Minimal longitude reached !</warning>"),
                    i18nc("@title:window", "Error"));
                return;
            }
            horo->setLongitude(coord - 1);
        }
    }
    else if (stepType->currentItem() == 2)
    { // solar return step
        if (ctxt->centering() > 1)
        { // todo: heliocentric and barycentric
            return;
        }
        int sunIdx = (PlanetCollection::dbCollection()->planet("Sun"))->idx();
        Q_ASSERT(res.planets().contains(sunIdx)); // todo: get pos if not found
        double sunPt = res.planets().value(sunIdx).longitude;
        double jdStart = horo->dateTime().julianDay()
            - (1.0/86400); // correction to avoid finding same pos
        int flag = ctxt->swissephFlags();
        double jdRet, posRet[6];
        char err[100];
        int i = swh_next_aspect(SE_SUN, 0, sunPt, jdStart, 0, 1, 0, flag, &jdRet, posRet, err);
        if (i != 0)
        {
            kWarning() << err;
            return;
        }
        DateTime tmp = horo->dateTime();
        tmp.fromJulianDay(jdRet);
        horo->setDateTime(tmp);
    }
    else if (stepType->currentItem() == 3)
    { // moon return step
        if (ctxt->centering() > 1)
        { // todo: heliocentric and barycentric
            return;
        }
        int moonIdx = (PlanetCollection::dbCollection()->planet("Moon"))->idx();
        Q_ASSERT(res.planets().contains(moonIdx)); // todo: get pos if not found
        double moonPt = res.planets().value(moonIdx).longitude;
        double jdStart = horo->dateTime().julianDay()
            - (1.0/86400); // correction to avoid finding same pos
        int flag = ctxt->swissephFlags();
        double jdRet, posRet[6];
        char err[100];
        int i = swh_next_aspect(SE_MOON, 0, moonPt, jdStart, 0, 1, 0, flag, &jdRet, posRet, err);
        if (i != 0)
        {
            kWarning() << err;
            return;
        }
        DateTime tmp = horo->dateTime();
        tmp.fromJulianDay(jdRet);
        horo->setDateTime(tmp);
    }

    coll->horoscopeChanged((HoroscopeCollection*) 0, horo, Horoscope::InvalidProperty);
}

void SubWindow::stepForward()
{
    int i = mdiArea()->subWindowList().indexOf(this);
    ChartCollection *coll = ChartCollection::openedCharts();
    Chart *ch = coll->chart(i);
    Horoscope *horo = ch->radix()->info();
    Context *ctxt = ch->context();
    //Settings *sett = ch->settings();
    WheelResults res = ch->radix()->results();

    KActionCollection *actions = KActionCollection::allCollections().at(0);
    KSelectAction *stepType = (KSelectAction*) actions->action("stepTypeWheel1");

    if (stepType->currentItem() == 0)
    { // time step
        DateTime dt = horo->dateTime();
        KSelectAction *stepValue = (KSelectAction*) actions->action("timeStepValueWheel1");
        int iStepValue = stepValue->currentText().toInt();
        KSelectAction *stepUnit = (KSelectAction*) actions->action("timeStepUnitWheel1");
        int iStepUnit = stepUnit->currentItem();
        switch (iStepUnit)
        {
            case 0: dt.addSeconds(iStepValue); break;
            case 1: dt.addMinutes(iStepValue); break;
            case 2: dt.addHours(iStepValue); break;
            case 3: dt.addDays(iStepValue); break;
            case 4: dt.addMonths(iStepValue); break;
            case 5: dt.addYears(- iStepValue); break;
            default:
                kWarning() << "Invalid step unit";
        }
        Q_ASSERT(dt.isValid());
        horo->setDateTime(dt);
    }
    else if (stepType->currentItem() == 1)
    { // space step
        KSelectAction *stepAxis = (KSelectAction*) actions->action("spaceStepAxisWheel1");
        if (stepAxis->currentItem() == 0)
        { // north/south axis
            GeoLat coord = horo->latitude();
            if (!GeoLat_Check(coord + 1))
            { // invalid latitude
                KMessageBox::error(this,
                    i18nc("@info", "<warning>Maximal latitude reached !</warning>"),
                    i18nc("@title:window", "Error"));
                return;
            }
            horo->setLatitude(coord + 1);
        }
        else
        { // east/west axis
            GeoLon coord = horo->longitude();
            if (!GeoLon_Check(coord + 1))
            { // invalid longitude
                KMessageBox::error(this,
                    i18nc("@info", "<warning>Maximal longitude reached !</warning>"),
                    i18nc("@title:window", "Error"));
                return;
            }
            horo->setLongitude(coord + 1);
        }
    }
    else if (stepType->currentItem() == 2)
    { // solar return step
        if (ctxt->centering() > 1)
        { // todo: heliocentric and barycentric
            return;
        }
        int sunIdx = (PlanetCollection::dbCollection()->planet("Sun"))->idx();
        Q_ASSERT(res.planets().contains(sunIdx)); // todo: get pos if not found
        double sunPt = res.planets().value(sunIdx).longitude;
        double jdStart = horo->dateTime().julianDay()
            + (1.0/86400); // correction to avoid finding same pos
        int flag = ctxt->swissephFlags();
        double jdRet, posRet[6];
        char err[100];
        int i = swh_next_aspect(SE_SUN, 0, sunPt, jdStart, 0, 0, 0, flag, &jdRet, posRet, err);
        if (i != 0)
        {
            kWarning() << err;
            return;
        }
        DateTime tmp = horo->dateTime();
        tmp.fromJulianDay(jdRet);
        horo->setDateTime(tmp);
    }
    else if (stepType->currentItem() == 3)
    { // moon return step
        if (ctxt->centering() > 1)
        { // todo: heliocentric and barycentric
            return;
        }
        int moonIdx = (PlanetCollection::dbCollection()->planet("Moon"))->idx();
        Q_ASSERT(res.planets().contains(moonIdx)); // todo: get pos if not found
        double moonPt = res.planets().value(moonIdx).longitude;
        double jdStart = horo->dateTime().julianDay()
            + (1.0/86400); // correction to avoid finding same pos
        int flag = ctxt->swissephFlags();
        double jdRet, posRet[6];
        char err[100];
        int i = swh_next_aspect(SE_MOON, 0, moonPt, jdStart, 0, 0, 0, flag, &jdRet, posRet, err);
        if (i != 0)
        {
            kWarning() << err;
            return;
        }
        DateTime tmp = horo->dateTime();
        tmp.fromJulianDay(jdRet);
        horo->setDateTime(tmp);
    }

    coll->horoscopeChanged((HoroscopeCollection*) 0, horo, Horoscope::InvalidProperty);
}

#endif
