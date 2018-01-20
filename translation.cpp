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

/** @file translation.cpp
 */

#include "translation.hpp"

#include <QByteArray>
#include <QChar>
#include <QMap>
#include <QString>

#include <KDebug>
#include <KLocalizedString>

#include <core.h>

static QMap<QByteArray, QString>* s_namesMap = NULL; // vocabulary

void loadTranslation()
{
    s_namesMap = new QMap<QByteArray, QString>;

    s_namesMap->insert( "Asc",      TR_ASC );
    s_namesMap->insert( "Dsc",      TR_DSC );
    s_namesMap->insert( "Mc",       TR_MC );
    s_namesMap->insert( "Ic",       TR_IC );

    s_namesMap->insert( "Sun",      TR_SUN );
    s_namesMap->insert( "Moon",     TR_MOON );
    s_namesMap->insert( "Mercury",  TR_MERCURY );
    s_namesMap->insert( "Venus",    TR_VENUS );
    s_namesMap->insert( "Mars",     TR_MARS );
    s_namesMap->insert( "Jupiter",  TR_JUPITER );
    s_namesMap->insert( "Saturn",   TR_SATURN );
    s_namesMap->insert( "Uranus",   TR_URANUS );
    s_namesMap->insert( "Neptune",  TR_NEPTUNE );
    s_namesMap->insert( "Pluto",    TR_PLUTO );
    s_namesMap->insert( "Earth",    TR_EARTH );
    s_namesMap->insert( "Chiron",   TR_CHIRON );
    s_namesMap->insert( "Pholus",   TR_PHOLUS );
    s_namesMap->insert( "Ceres",    TR_CERES );
    s_namesMap->insert( "Pallas",   TR_PALLAS );
    s_namesMap->insert( "Juno",     TR_JUNO );
    s_namesMap->insert( "Vesta",    TR_VESTA );
    s_namesMap->insert( "Rahu (m)",     TR_RAHU_MEAN );
    s_namesMap->insert( "Rahu (t)",     TR_RAHU_TRUE );
    s_namesMap->insert( "Ketu (m)",     TR_KETU_MEAN );
    s_namesMap->insert( "Ketu (t)",     TR_KETU_TRUE );
    s_namesMap->insert( "Lilith (m)",   TR_LILITH_MEAN );
    s_namesMap->insert( "Lilith (t)",   TR_LILITH_TRUE );
    s_namesMap->insert( "Priapus (m)",  TR_PRIAPUS_MEAN );
    s_namesMap->insert( "Priapus (t)",  TR_PRIAPUS_TRUE );
    s_namesMap->insert( "Cupido",   TR_CUPIDO );
    s_namesMap->insert( "Hades",    TR_HADES );
    s_namesMap->insert( "Zeus",     TR_ZEUS );
    s_namesMap->insert( "Kronos",   TR_KRONOS );
    s_namesMap->insert( "Apollon",  TR_APOLLON );
    s_namesMap->insert( "Admetos",  TR_ADMETOS );
    s_namesMap->insert( "Vulkanus", TR_VULKANUS );
    s_namesMap->insert( "Poseidon", TR_POSEIDON );

    s_namesMap->insert( "Conjunction",  TR_CONJUNCTION );
    s_namesMap->insert( "Opposition",   TR_OPPOSITION );
    s_namesMap->insert( "Trine",        TR_TRINE );
    s_namesMap->insert( "Square",       TR_SQUARE );
    s_namesMap->insert( "Sextile",      TR_SEXTILE );
    s_namesMap->insert( "Quincunx",     TR_QUINCUNX );
    s_namesMap->insert( "SesquiSquare", TR_SESQUISQUARE );
    s_namesMap->insert( "SemiSquare",   TR_SEMISQUARE );
    s_namesMap->insert( "SemiSextile",  TR_SEMISEXTILE );
    s_namesMap->insert( "SquiSquare",   TR_SQUISQUARE );
    s_namesMap->insert( "SquiSextile",  TR_SQUISEXTILE );
    s_namesMap->insert( "Quintile",     TR_QUINTILE );
    s_namesMap->insert( "BiQuintile",   TR_BIQUINTILE );
    s_namesMap->insert( "SemiQuintile", TR_SEMIQUINTILE );
    s_namesMap->insert( "Novile",       TR_NOVILE );
    s_namesMap->insert( "BiNovile",     TR_BINOVILE );
    s_namesMap->insert( "QuadriNovile", TR_QUADRINOVILE );
    s_namesMap->insert( "SemiNovile",   TR_SEMINOVILE );
    s_namesMap->insert( "Septile",      TR_SEPTILE );
    s_namesMap->insert( "BiSeptile",    TR_BISEPTILE );
    s_namesMap->insert( "TriSeptile",   TR_TRISEPTILE );
    s_namesMap->insert( "Undecile",     TR_UNDECILE );
    s_namesMap->insert( "BiUndecile",   TR_BIUNDECILE );
    s_namesMap->insert( "TriUndecile",  TR_TRIUNDECILE );
    s_namesMap->insert( "QuadUndecile", TR_QUADUNDECILE );
    s_namesMap->insert( "QuinUndecile", TR_QUINUNDECILE );

}

void deleteTranslation()
{
    if ( s_namesMap )
        delete s_namesMap;
}

QString translation( const char* name )
{
#ifndef NDEBUG
    const QByteArray ba = QByteArray::fromRawData( name, strlen( name ) );
    if ( s_namesMap->contains( ba ) )
        return s_namesMap->value( ba );

    else
    {
        kWarning() << "Missing translation for" << name;
        return QString::fromUtf8( name );
    }
#else
    return s_namesMap->value( QByteArray::fromRawData( name, strlen( name ) ) );
#endif // !NDEBUG
}

QString translationZodiacSign( int i )
{
    switch ( i )
    {
        case 0: return TR_ARIES;
        case 1: return TR_TAURUS;
        case 2: return TR_GEMINI;
        case 3: return TR_CANCER;
        case 4: return TR_LEO;
        case 5: return TR_VIRGO;
        case 6: return TR_LIBRA;
        case 7: return TR_SCORPIO;
        case 8: return TR_SAGITTARIUS;
        case 9: return TR_CAPRICORN;
        case 10: return TR_AQUARIUS;
        case 11: return TR_PISCES;
        default:
            kWarning() << "Invalid zodiac index" << i;
            return QString();
    }
}

QString translationZodiacSign3L( int i )
{
    switch ( i )
    {
        case 0: return TR_ARI_3L;
        case 1: return TR_TAU_3L;
        case 2: return TR_GEM_3L;
        case 3: return TR_CAN_3L;
        case 4: return TR_LEO_3L;
        case 5: return TR_VIR_3L;
        case 6: return TR_LIB_3L;
        case 7: return TR_SCO_3L;
        case 8: return TR_SAG_3L;
        case 9: return TR_CAP_3L;
        case 10: return TR_AQU_3L;
        case 11: return TR_PIS_3L;
        default:
            kWarning() << "Invalid zodiac index" << i;
            return QString();
    }
}

QString translationNakshatra( int i )
{
    switch( i )
    {
        case 0: return TR_ASWINI;
        case 1: return TR_BHARANI;
        case 2: return TR_KRITTIKA;
        case 3: return TR_ROHINI;
        case 4: return TR_MRIGASIRA;
        case 5: return TR_ARIDRA;
        case 6: return TR_PUNARVASU;
        case 7: return TR_PUSHYAMI;
        case 8: return TR_ASLESHA;
        case 9: return TR_MAKHA;
        case 10: return TR_PURVAPHALGUNI;
        case 11: return TR_UTTARAPHALGUNI;
        case 12: return TR_HASTA;
        case 13: return TR_CHITTA;
        case 14: return TR_SWATI;
        case 15: return TR_VISAKHA;
        case 16: return TR_ANURADHA;
        case 17: return TR_JYESTHA;
        case 18: return TR_MOOLA;
        case 19: return TR_PURVASHADHA;
        case 20: return TR_UTTARASHADHA;
        case 21: return TR_SRAVANA;
        case 22: return TR_DHANISTHA;
        case 23: return TR_SATABHISHA;
        case 24: return TR_PURVABHADRA;
        case 25: return TR_UTTARABHADRA;
        case 26: return TR_REVATI;
        default:
            kWarning() << "Invalid nakshatra index" << i;
            return QString();
    }
}

QString translationCusp( int i )
{
    switch ( i )
    {
        case 0: return TR_CUSP_01;
        case 1: return TR_CUSP_02;
        case 2: return TR_CUSP_03;
        case 3: return TR_CUSP_04;
        case 4: return TR_CUSP_05;
        case 5: return TR_CUSP_06;
        case 6: return TR_CUSP_07;
        case 7: return TR_CUSP_08;
        case 8: return TR_CUSP_09;
        case 9: return TR_CUSP_10;
        case 10: return TR_CUSP_11;
        case 11: return TR_CUSP_12;
        default:
            kWarning() << "Invalid cusp index" << i;
            return QString();
    }
}

QString translationCuspShort( int i )
{
    switch ( i )
    {
        case 0: return TR_CUSP_01_S;
        case 1: return TR_CUSP_02_S;
        case 2: return TR_CUSP_03_S;
        case 3: return TR_CUSP_04_S;
        case 4: return TR_CUSP_05_S;
        case 5: return TR_CUSP_06_S;
        case 6: return TR_CUSP_07_S;
        case 7: return TR_CUSP_08_S;
        case 8: return TR_CUSP_09_S;
        case 9: return TR_CUSP_10_S;
        case 10: return TR_CUSP_11_S;
        case 11: return TR_CUSP_12_S;
        default:
            kWarning() << "Invalid cusp index" << i;
            return QString();
    }
}

QString translationDayOfWeek( int i )
{
    switch ( i )
    {
        case 0: return TR_MONDAY;
        case 1: return TR_TUESDAY;
        case 2: return TR_WEDNESDAY;
        case 3: return TR_THURSDAY;
        case 4: return TR_FRIDAY;
        case 5: return TR_SATURDAY;
        case 6: return TR_SUNDAY;
        default:
            kWarning() << "Invalid day of week index" << i;
            return QString();
    }
}



// frequently used strings
static const QChar s_zerochar = QChar( '0' );
static const QString s_argString = QString( "%1" );

QString PosData_LongitudeToString( const PosData& d, bool withSeconds )
{
    return LongitudeToString( d.res[0], d.res[3], withSeconds );
}

QString LongitudeToString( double longitude, double speed, bool withSeconds )
{
    int i[4];
    posdata_longitude_split( longitude, i );

    QString coords;

    if ( !withSeconds )
    {
        if ( speed >= 0 )
        { // direct
            coords = i18nc( "{degrees} {sign} {minutes}", "%1° %2 %3'",
                s_argString.arg( i[0], 2, 10, s_zerochar ),
                translationZodiacSign3L( i[1] ) ,
                s_argString.arg( i[2], 2, 10, s_zerochar )  );
        }
        else
        { // retro
            coords = i18nc( "{degrees} {sign} {minutes} {Retrograde}", "%1° %2 %3' R",
                s_argString.arg( i[0], 2, 10, s_zerochar ),
                translationZodiacSign3L( i[1] ),
                s_argString.arg( i[2], 2, 10, s_zerochar )  );
        }
    }
    else
    {
        if ( speed >= 0 )
        { // direct
            coords = i18nc( "{degrees} {sign} {minutes} {seconds}", "%1° %2 %3' %4\"",
                s_argString.arg( i[0], 2, 10, s_zerochar ),
                translationZodiacSign3L( i[1] ),
                s_argString.arg( i[2], 2, 10, s_zerochar ),
                s_argString.arg( i[3], 2, 10, s_zerochar )  );
        }
        else
        { // retro
            coords = i18nc( "{degrees} {sign} {minutes} {seconds} {Retrograde}", "%1° %2 %3' %4\" R",
                s_argString.arg( i[0], 2, 10, s_zerochar ),
                translationZodiacSign3L( i[1] ),
                s_argString.arg( i[2], 2, 10, s_zerochar ),
                s_argString.arg( i[3], 2, 10, s_zerochar )  );
        }
    }
    return coords;
}

QString GeoLatToString( double lat )
{
    GeoCoord coord;
    geocoord_from_double( &coord, lat );
    return i18nc(
        "@info/plain Latitude format {deg}:{N|S}:{min}:{sec}",
        "%1:%2:%3:%4", coord.deg,
        coord.dir ?
            i18nc( "@info/plain North", "N" )
            : i18nc( "@info/plain South", "S" ),
        coord.min, coord.sec );
}

QString GeoLonToString( double lon )
{
    GeoCoord coord;
    geocoord_from_double( &coord, lon );
    return i18nc(
        "@info/plain Longitude format {deg}:{E|W}:{min}:{sec}",
        "%1:%2:%3:%4", coord.deg,
        coord.dir ?
            i18nc( "@info/plain East", "E" )
            : i18nc( "@info/plain West", "W" ),
        coord.min, coord.sec );
}

QString GeoAltToString( uint alt )
{
    return i18nc( "@info/plain {altitude} meters", "%1 m.", alt );
}
