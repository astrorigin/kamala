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

/** @file translation.hpp
 *  @brief i18n utilities
 */

#ifndef KAMALA_TRANSLATION_HPP
#define KAMALA_TRANSLATION_HPP

#include <QString>
#include <QStringList>
#include <KLocalizedString>
#include "kamala_export.hpp"

#include <core.h>

/* Zodiac signs */
const QString TR_ARIES          = i18nc( "Zodiac sign", "Aries" );
const QString TR_TAURUS         = i18nc( "Zodiac sign", "Taurus" );
const QString TR_GEMINI         = i18nc( "Zodiac sign", "Gemini" );
const QString TR_CANCER         = i18nc( "Zodiac sign", "Cancer" );
const QString TR_LEO            = i18nc( "Zodiac sign", "Leo" );
const QString TR_VIRGO          = i18nc( "Zodiac sign", "Virgo" );
const QString TR_LIBRA          = i18nc( "Zodiac sign", "Libra" );
const QString TR_SCORPIO        = i18nc( "Zodiac sign", "Scorpio" );
const QString TR_SAGITTARIUS    = i18nc( "Zodiac sign", "Sagittarius" );
const QString TR_CAPRICORN      = i18nc( "Zodiac sign", "Capricorn" );
const QString TR_AQUARIUS       = i18nc( "Zodiac sign", "Aquarius" );
const QString TR_PISCES         = i18nc( "Zodiac sign", "Pisces" );

/* Zodiac signs, 3 letters abbreviation */
const QString TR_ARI_3L         = i18nc( "3-letters Zodiac sign", "Ari" );
const QString TR_TAU_3L         = i18nc( "3-letters Zodiac sign", "Tau" );
const QString TR_GEM_3L         = i18nc( "3-letters Zodiac sign", "Gem" );
const QString TR_CAN_3L         = i18nc( "3-letters Zodiac sign", "Can" );
const QString TR_LEO_3L         = i18nc( "3-letters Zodiac sign", "Leo" );
const QString TR_VIR_3L         = i18nc( "3-letters Zodiac sign", "Vir" );
const QString TR_LIB_3L         = i18nc( "3-letters Zodiac sign", "Lib" );
const QString TR_SCO_3L         = i18nc( "3-letters Zodiac sign", "Sco" );
const QString TR_SAG_3L         = i18nc( "3-letters Zodiac sign", "Sag" );
const QString TR_CAP_3L         = i18nc( "3-letters Zodiac sign", "Cap" );
const QString TR_AQU_3L         = i18nc( "3-letters Zodiac sign", "Aqu" );
const QString TR_PIS_3L         = i18nc( "3-letters Zodiac sign", "Pis" );

/* Nakshatras */
const QString TR_ASWINI         = i18nc( "Nakshatra", "Aswini" );
const QString TR_BHARANI        = i18nc( "Nakshatra", "Bharani" );
const QString TR_KRITTIKA       = i18nc( "Nakshatra", "Krittika" );
const QString TR_ROHINI         = i18nc( "Nakshatra", "Rohini" );
const QString TR_MRIGASIRA      = i18nc( "Nakshatra", "Mrigasira" );
const QString TR_ARIDRA         = i18nc( "Nakshatra", "Aridra" );
const QString TR_PUNARVASU      = i18nc( "Nakshatra", "Punarvasu" );
const QString TR_PUSHYAMI       = i18nc( "Nakshatra", "Pushyami" );
const QString TR_ASLESHA        = i18nc( "Nakshatra", "Aslesha" );
const QString TR_MAKHA          = i18nc( "Nakshatra", "Makha" );
const QString TR_PURVAPHALGUNI  = i18nc( "Nakshatra", "Purvaphalguni" );
const QString TR_UTTARAPHALGUNI = i18nc( "Nakshatra", "Uttaraphalguni" );
const QString TR_HASTA          = i18nc( "Nakshatra", "Hasta" );
const QString TR_CHITTA         = i18nc( "Nakshatra", "Chitta" );
const QString TR_SWATI          = i18nc( "Nakshatra", "Swati" );
const QString TR_VISAKHA        = i18nc( "Nakshatra", "Vishaka" );
const QString TR_ANURADHA       = i18nc( "Nakshatra", "Anuradha" );
const QString TR_JYESTHA        = i18nc( "Nakshatra", "Jyestha" );
const QString TR_MOOLA          = i18nc( "Nakshatra", "Moola" );
const QString TR_PURVASHADHA    = i18nc( "Nakshatra", "Purvashadha" );
const QString TR_UTTARASHADHA   = i18nc( "Nakshatra", "Uttarashadha" );
const QString TR_SRAVANA        = i18nc( "Nakshatra", "Sravana" );
const QString TR_DHANISTHA      = i18nc( "Nakshatra", "Dhanistha" );
const QString TR_SATABHISHA     = i18nc( "Nakshatra", "Satabisha" );
const QString TR_PURVABHADRA    = i18nc( "Nakshatra", "Purvabhadra" );
const QString TR_UTTARABHADRA   = i18nc( "Nakshatra", "Uttarabhadra" );
const QString TR_REVATI         = i18nc( "Nakshatra", "Revati" );

/* Angles */
const QString TR_ASC            = i18n( "Ascendant" );
const QString TR_DSC            = i18n( "Descendant" );
const QString TR_MC             = i18n( "Medium Coeli" );
const QString TR_IC             = i18n( "Imum Coeli" );

/* Planets */
const QString TR_SUN            = i18nc( "Planet name", "Sun" );
const QString TR_MOON           = i18nc( "Planet name", "Moon" );
const QString TR_MERCURY        = i18nc( "Planet name", "Mercury" );
const QString TR_VENUS          = i18nc( "Planet name", "Venus" );
const QString TR_MARS           = i18nc( "Planet name", "Mars" );
const QString TR_JUPITER        = i18nc( "Planet name", "Jupiter" );
const QString TR_SATURN         = i18nc( "Planet name", "Saturn" );
const QString TR_URANUS         = i18nc( "Planet name", "Uranus" );
const QString TR_NEPTUNE        = i18nc( "Planet name", "Neptune" );
const QString TR_PLUTO          = i18nc( "Planet name", "Pluto" );
const QString TR_EARTH          = i18nc( "Planet name", "Earth" );
const QString TR_CHIRON         = i18nc( "Planet name", "Chiron" );
const QString TR_PHOLUS         = i18nc( "Planet name", "Pholus" );
const QString TR_CERES          = i18nc( "Planet name", "Ceres" );
const QString TR_PALLAS         = i18nc( "Planet name", "Pallas" );
const QString TR_JUNO           = i18nc( "Planet name", "Juno" );
const QString TR_VESTA          = i18nc( "Planet name", "Vesta" );
const QString TR_RAHU_MEAN      = i18nc( "Planet name", "Rahu (m)" );
const QString TR_RAHU_TRUE      = i18nc( "Planet name", "Rahu (t)" );
const QString TR_KETU_MEAN      = i18nc( "Planet name", "Ketu (m)" );
const QString TR_KETU_TRUE      = i18nc( "Planet name", "Ketu (t)" );
const QString TR_LILITH_MEAN    = i18nc( "Planet name", "Lilith (m)" );
const QString TR_LILITH_TRUE    = i18nc( "Planet name", "Lilith (t)" );
const QString TR_PRIAPUS_MEAN   = i18nc( "Planet name", "Priapus (m)" );
const QString TR_PRIAPUS_TRUE   = i18nc( "Planet name", "Priapus (t)" );
const QString TR_CUPIDO         = i18nc( "Planet name", "Cupido" );
const QString TR_HADES          = i18nc( "Planet name", "Hades" );
const QString TR_ZEUS           = i18nc( "Planet name", "Zeus" );
const QString TR_KRONOS         = i18nc( "Planet name", "Kronos" );
const QString TR_APOLLON        = i18nc( "Planet name", "Apolon" );
const QString TR_ADMETOS        = i18nc( "Planet name", "Admetos" );
const QString TR_VULKANUS       = i18nc( "Planet name", "Vulkanus" );
const QString TR_POSEIDON       = i18nc( "Planet name", "Poseidon" );

/* Cusps, long version */
const QString TR_CUSP_01        = i18nc( "House cusp", "Cusp I" );
const QString TR_CUSP_02        = i18nc( "House cusp", "Cusp II" );
const QString TR_CUSP_03        = i18nc( "House cusp", "Cusp III" );
const QString TR_CUSP_04        = i18nc( "House cusp", "Cusp IV" );
const QString TR_CUSP_05        = i18nc( "House cusp", "Cusp V" );
const QString TR_CUSP_06        = i18nc( "House cusp", "Cusp VI" );
const QString TR_CUSP_07        = i18nc( "House cusp", "Cusp VII" );
const QString TR_CUSP_08        = i18nc( "House cusp", "Cusp IIX" );
const QString TR_CUSP_09        = i18nc( "House cusp", "Cusp IX" );
const QString TR_CUSP_10        = i18nc( "House cusp", "Cusp X" );
const QString TR_CUSP_11        = i18nc( "House cusp", "Cusp XI" );
const QString TR_CUSP_12        = i18nc( "House cusp", "Cusp XII" );

/* Cusps, short version in roman numbers */
const QString TR_CUSP_01_S      = i18nc( "House cusp (short)", "I" );
const QString TR_CUSP_02_S      = i18nc( "House cusp (short)", "II" );
const QString TR_CUSP_03_S      = i18nc( "House cusp (short)", "III" );
const QString TR_CUSP_04_S      = i18nc( "House cusp (short)", "IV" );
const QString TR_CUSP_05_S      = i18nc( "House cusp (short)", "V" );
const QString TR_CUSP_06_S      = i18nc( "House cusp (short)", "VI" );
const QString TR_CUSP_07_S      = i18nc( "House cusp (short)", "VII" );
const QString TR_CUSP_08_S      = i18nc( "House cusp (short)", "IIX" );
const QString TR_CUSP_09_S      = i18nc( "House cusp (short)", "IX" );
const QString TR_CUSP_10_S      = i18nc( "House cusp (short)", "X" );
const QString TR_CUSP_11_S      = i18nc( "House cusp (short)", "XI" );
const QString TR_CUSP_12_S      = i18nc( "House cusp (short)", "XII" );

/* Aspects */
const QString TR_CONJUNCTION    = i18nc( "Aspect", "Conjunction" );
const QString TR_OPPOSITION     = i18nc( "Aspect", "Opposition" );
const QString TR_TRINE          = i18nc( "Aspect", "Trine" );
const QString TR_SQUARE         = i18nc( "Aspect", "Square" );
const QString TR_SEXTILE        = i18nc( "Aspect", "Sextile" );
const QString TR_QUINCUNX       = i18nc( "Aspect", "Quincunx" );
const QString TR_SESQUISQUARE   = i18nc( "Aspect", "SesquiSquare" );
const QString TR_SEMISQUARE     = i18nc( "Aspect", "SemiSquare" );
const QString TR_SEMISEXTILE    = i18nc( "Aspect", "SemiSextile" );
const QString TR_SQUISQUARE     = i18nc( "Aspect", "SquiSquare" );
const QString TR_SQUISEXTILE    = i18nc( "Aspect", "SquiSextile" );
const QString TR_QUINTILE       = i18nc( "Aspect", "Quintile" );
const QString TR_BIQUINTILE     = i18nc( "Aspect", "BiQuintile" );
const QString TR_SEMIQUINTILE   = i18nc( "Aspect", "SemiQuintile" );
const QString TR_NOVILE         = i18nc( "Aspect", "Novile" );
const QString TR_BINOVILE       = i18nc( "Aspect", "BiNovile" );
const QString TR_QUADRINOVILE   = i18nc( "Aspect", "QuadriNovile" );
const QString TR_SEMINOVILE     = i18nc( "Aspect", "SemiNovile" );
const QString TR_SEPTILE        = i18nc( "Aspect", "Septile" );
const QString TR_BISEPTILE      = i18nc( "Aspect", "BiSeptile" );
const QString TR_TRISEPTILE     = i18nc( "Aspect", "TriSeptile" );
const QString TR_UNDECILE       = i18nc( "Aspect", "Undecile" );
const QString TR_BIUNDECILE     = i18nc( "Aspect", "BiUndecile" );
const QString TR_TRIUNDECILE    = i18nc( "Aspect", "TriUndecile" );
const QString TR_QUADUNDECILE   = i18nc( "Aspect", "QuadUndecile" );
const QString TR_QUINUNDECILE   = i18nc( "Aspect", "QuinUndecile" );

/* Days of week */
const QString TR_MONDAY         = i18nc( "Day of week", "Mon" );
const QString TR_TUESDAY        = i18nc( "Day of week", "Tue" );
const QString TR_WEDNESDAY      = i18nc( "Day of week", "Wed" );
const QString TR_THURSDAY       = i18nc( "Day of week", "Thu" );
const QString TR_FRIDAY         = i18nc( "Day of week", "Fri" );
const QString TR_SATURDAY       = i18nc( "Day of week", "Sat" );
const QString TR_SUNDAY         = i18nc( "Day of week", "Sun" );



/** @brief String list of calendars for a combo box
 */
const QStringList Calendars_StringList = QStringList()
                                << i18nc( "@item Calendar type", "Julian" )
                                << i18nc( "@item Calendar type", "Gregorian" );

/** @brief String list of daylights savings time for a combo box
 */
const QStringList DST_StringList = QStringList()
                            << i18nc( "@item Daylights Savings Time", "?" )
                            << i18nc( "@item Daylights Savings Time", "No DST" )
                            << i18nc( "@item Daylights Savings Time", "Is DST" );

/** @brief String list of SVG themes
 *  Each name matches a subdirectory containing the svg files.
 *  (Is not translated but placed here with all words.)
 *  Used in preferences dialog.
 */
const QStringList Themes_StringList = QStringList() << "default";

/** @brief String list of background colors
 *  Used in preferences dialog.
 */
const QStringList BackgroundColors_StringList = QStringList()
            << i18nc( "@item:inlistbox Background color", "White" )
            << i18nc( "@item:inlistbox Background color", "Black" );

/** @brief Loads the vocabulary
 *  Done on startup.
 */
KAMALA_EXPORT void loadTranslation();

/** @brief Free memory occupied by vocabulary
 */
KAMALA_EXPORT void deleteTranslation();

/** @brief Translate given word
 *  @param term Term to translate
 */
KAMALA_EXPORT QString translation( const char* term );

/** @brief Translate given zodiac sign
 *  @param i Integer [0:11]
 */
KAMALA_EXPORT QString translationZodiacSign( int i );

/** @brief Translate zodiac sign, three letters version
 *  @param i Integer [0:11]
 */
KAMALA_EXPORT QString translationZodiacSign3L( int i );

/** @brief Translate nakshatra
 *  @param i Integer [0;26]
 */
KAMALA_EXPORT QString translationNakshatra( int i );

/** @brief Translate house cusp
 *  @param i Integer [0:11]
 */
KAMALA_EXPORT QString translationCusp( int i );

/** @brief Translate house cusp name, short version
 *  @param i Integer [0:11]
 */
KAMALA_EXPORT QString translationCuspShort( int i );

/** @brief Translate day of week
 *  @param i Day of week [0:6]
 */
KAMALA_EXPORT QString translationDayOfWeek( int i );

/** @brief Get string for planet longitude (from position data)
 *  A conveniance function for LongitudeToString().
 *  @see LongitudeToString()
 *  @param d Planet positions
 *  @param withSeconds Display seconds
 */
KAMALA_EXPORT QString PosData_LongitudeToString( const PosData& d, bool withSeconds=false );

/** @brief Get string for planet longitude
 *  @param longitude Planet longitude [0:360[
 *  @param speed Planet speed
 *  @param withSeconds Display seconds
 */
KAMALA_EXPORT QString LongitudeToString( double longitude, double speed, bool withSeconds=false );

/** @brief Get string for a geographic latitude
 *  @param lat Latitude
 */
KAMALA_EXPORT QString GeoLatToString( double lat );

/** @brief Get string for a geographic longitude
 *  @param lon Longitude
 */
KAMALA_EXPORT QString GeoLonToString( double lon );

/** @brief Get string for a geographic altitude
 */
KAMALA_EXPORT QString GeoAltToString( uint alt );

#endif // KAMALA_TRANSLATION_HPP
