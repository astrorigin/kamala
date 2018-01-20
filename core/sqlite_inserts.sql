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

/* Aspects */
insert into Aspects (angle, name, family, zValue, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, color, glyph)
values (0, 'Conjunction', 0, 1, 1, 10, 10, 10, '#ffff00', 'conjunction.svg');/***/
insert into Aspects (angle, name, family, zValue, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, color, glyph)
values (180, 'Opposition', 0, 2, 1, 10, 10, 10, '#0000ff', 'opposition.svg');/***/
insert into Aspects (angle, name, family, zValue, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, color, glyph)
values (120, 'Trine', 0, 3, 1, 8, 8, 8, '#00ff00', 'trine.svg');/***/
insert into Aspects (angle, name, family, zValue, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, color, glyph)
values (90, 'Square', 0, 4, 1, 8, 8, 8, '#ff0000', 'square.svg');/***/
insert into Aspects (angle, name, family, zValue, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, color, glyph)
values (60, 'Sextile', 0, 5, 1, 4, 4, 4, '#00ffff', 'sextile.svg');/***/
insert into Aspects (angle, name, family, zValue, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, color, glyph)
values (150, 'Quincunx', 0, 6, 0, 4, 4, 4, '#ff00c0', 'quincunx.svg');/***/
insert into Aspects (angle, name, family, zValue, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, color, glyph)
values (135, 'SesquiSquare', 0, 7, 0, 2, 2, 2, '#c08000', 'sesquisquare.svg');/***/
insert into Aspects (angle, name, family, zValue, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, color, glyph)
values (45, 'SemiSquare', 0, 8, 0, 2, 2, 2, '#c08000', 'semisquare.svg');/***/
insert into Aspects (angle, name, family, zValue, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, color, glyph)
values (30, 'SemiSextile', 0, 9, 0, 2, 2, 2, '#ff00c0', 'semisextile.svg');/***/
insert into Aspects (angle, name, family, zValue, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, color, glyph)
values (22.5, 'SquiSquare', 0, 10, 0, 1, 1, 1, '#c08000', 'squisquare.svg');/***/
insert into Aspects (angle, name, family, zValue, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, color, glyph)
values (15, 'SquiSextile', 0, 11, 0, 1, 1, 1, '#c08000', 'squisextile.svg');/***/

insert into Aspects (angle, name, family, zValue, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, color, glyph)
values (72, 'Quintile', 0, 12, 0, 1, 1, 1, '#0080ff', 'quintile.svg');/***/
insert into Aspects (angle, name, family, zValue, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, color, glyph)
values (144, 'BiQuintile', 0, 13, 0, 1, 1, 1, '#0080ff', 'biquintile.svg');/***/
insert into Aspects (angle, name, family, zValue, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, color, glyph)
values (36, 'SemiQuintile', 0, 14, 0, 1, 1, 1, '#0080ff', 'semiquintile.svg');/***/

insert into Aspects (angle, name, family, zValue, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, color, glyph)
values (40, 'Novile', 1, 15, 0, 0.5, 0.5, 0.5, '#ff8000', 'novile.svg');/***/
insert into Aspects (angle, name, family, zValue, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, color, glyph)
values (80, 'BiNovile', 1, 16, 0, 0.5, 0.5, 0.5, '#ff8000', 'binovile.svg');/***/
insert into Aspects (angle, name, family, zValue, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, color, glyph)
values (160, 'QuadriNovile', 1, 17, 0, 0.5, 0.5, 0.5, '#ff8000', 'quatronovile.svg');/***/
insert into Aspects (angle, name, family, zValue, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, color, glyph)
values (20, 'SemiNovile', 1, 18, 0, 0.5, 0.5, 0.5, '#ff8000', 'seminovile.svg');/***/

insert into Aspects (angle, name, family, zValue, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, color, glyph)
values ((360./7), 'Septile', 1, 19, 0, 0.5, 0.5, 0.5, '#808080', 'septile.svg');/***/
insert into Aspects (angle, name, family, zValue, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, color, glyph)
values ((360./7)*2, 'BiSeptile', 1, 20, 0, 0.5, 0.5, 0.5, '#808080', 'biseptile.svg');/***/
insert into Aspects (angle, name, family, zValue, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, color, glyph)
values ((360./7)*3, 'TriSeptile', 1, 21, 0, 0.5, 0.5, 0.5, '#808080', 'triseptile.svg');/***/

insert into Aspects (angle, name, family, zValue, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, color, glyph)
values ((360./11), 'Undecile', 1, 22, 0, 0.5, 0.5, 0.5, '#008080', 'undecile.svg');/***/
insert into Aspects (angle, name, family, zValue, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, color, glyph)
values ((360./11)*2, 'BiUndecile', 1, 23, 0, 0.5, 0.5, 0.5, '#008080', 'biundecile.svg');/***/
insert into Aspects (angle, name, family, zValue, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, color, glyph)
values ((360./11)*3, 'TriUndecile', 1, 24, 0, 0.5, 0.5, 0.5, '#008080', 'triundecile.svg');/***/
insert into Aspects (angle, name, family, zValue, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, color, glyph)
values ((360./11)*4, 'QuadUndecile', 1, 25, 0, 0.5, 0.5, 0.5, '#008080', 'quadundecile.svg');/***/
insert into Aspects (angle, name, family, zValue, dftUse, dftAppOrb, dftSepOrb, dftStaOrb, color, glyph)
values ((360./11)*5, 'QuinUndecile', 1, 26, 0, 0.5, 0.5, 0.5, '#008080', 'quinundecile.svg');/***/

/* Planets */
-- ***** Real Bodies
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (0, 'Sun', 0, 1, 1, 1, 'sun.svg');/***/ -- Sun
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (1, 'Moon', 0, 2, 1, 1, 'moon.svg');/***/ -- Moon
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (2, 'Mercury', 0, 3, 1, 1, 'mercury.svg');/***/ -- Mercury
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (3, 'Venus', 0, 4, 1, 1, 'venus.svg');/***/ -- Venus
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (4, 'Mars', 0, 5, 1, 1, 'mars.svg');/***/ -- Mars
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (5, 'Jupiter', 0, 6, 1, 1, 'jupiter.svg');/***/ -- Jupiter
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (6, 'Saturn', 0, 7, 1, 1, 'saturn.svg');/***/ -- Saturn
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (7, 'Uranus', 0, 8, 1, 1, 'uranus.svg');/***/ -- Uranus
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (8, 'Neptune', 0, 9, 1, 1, 'neptune.svg');/***/ -- Neptune
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (9, 'Pluto', 0, 10, 1, 1, 'pluto.svg');/***/ -- Pluto
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (14, 'Earth', 0, 11, 0, 0, 'earth.svg');/***/ -- Earth
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (15, 'Chiron', 0, 12, 0, 0, 'chiron.svg');/***/ -- Chiron
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (16, 'Pholus', 0, 13, 0, 0, 'pholus.svg');/***/ -- Pholus
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (17, 'Ceres', 0, 14, 0, 0, 'ceres.svg');/***/ -- Ceres
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (18, 'Pallas', 0, 15, 0, 0, 'pallas.svg');/***/ -- Pallas
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (19, 'Juno', 0, 16, 0, 0, 'juno.svg');/***/ -- Juno
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (20, 'Vesta', 0, 17, 0, 0, 'vesta.svg');/***/ -- Vesta

-- ***** Lunar nodes, Lilith/Priapus
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (10, 'Rahu (m)', 0, 18, 0, 0, 'rahu.svg');/***/ -- North lunar node (mean)
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (11, 'Rahu (t)', 0, 19, 0, 0, 'rahu.svg');/***/ -- North lunar node (true)
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-2, 'Ketu (m)', 0, 20, 0, 0, 'ketu.svg');/***/ -- South lunar node (mean)
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-3, 'Ketu (t)', 0, 21, 0, 0, 'ketu.svg');/***/ -- South lunar node (true)
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (12, 'Lilith (m)', 0, 22, 0, 0, 'lilith.svg');/***/ -- Mean Lunar Apogee
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (13, 'Lilith (t)', 0, 23, 0, 0, 'lilith.svg');/***/ -- Osculating Lunar Apogee
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-4, 'Priapus (m)', 0, 24, 0, 0, 'priapus.svg');/***/ -- Priapus (mean)
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-5, 'Priapus (t)', 0, 25, 0, 0, 'priapus.svg');/***/ -- Priapus (true)

-- ***** Hamburg/Uranian "planets"
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (40, 'Cupido', 1, 26, 0, 0, 'cupido.svg');/***/ -- Cupido
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (41, 'Hades', 1, 27, 0, 0, 'hades.svg');/***/ -- Hades
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (42, 'Zeus', 1, 28, 0, 0, 'zeus.svg');/***/ -- Zeus
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (43, 'Kronos', 1, 29, 0, 0, 'kronos.svg');/***/ -- Kronos
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (44, 'Apollon', 1, 30, 0, 0, 'apollon.svg');/***/ -- Apollon
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (45, 'Admetos', 1, 31, 0, 0, 'admetos.svg');/***/ -- Admetos
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (46, 'Vulkanus', 1, 32, 0, 0, 'vulkanus.svg');/***/ -- Vulkanus
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (47, 'Poseidon', 1, 33, 0, 0, 'poseidon.svg');/***/ -- Poseidon

-- ***** Other fictitious bodies
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (48, 'Isis', 2, 34, 0, 0, 'isis.svg');/***/ -- Isis
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (49, 'Nibiru', 2, 35, 0, 0, 'nibiru.svg');/***/ -- Nibiru
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (50, 'Harrington', 2, 36, 0, 0, 'harrington.svg');/***/ -- Harrington
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (51, 'Neptune (Leverrier)', 2, 37, 0, 0, 'neptune_leverrier.svg');/***/ -- Neptune Leverrier
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (52, 'Neptune (Adams)', 2, 38, 0, 0, 'neptune_adams.svg');/***/ -- Neptune Adams
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (53, 'Pluto (Lowell)', 2, 39, 0, 0, 'pluto_lowell.svg');/***/ -- Pluto Lowell
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (54, 'Pluto (Pickering)', 2, 40, 0, 0, 'pluto_pickering.svg');/***/ -- Pluto Pickering
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (55, 'Vulcan', 2, 41, 0, 0, 'vulcan.svg');/***/ -- Vulcan
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (56, 'White Moon', 2, 42, 0, 0, 'white_moon.svg');/***/ -- White Moon
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (57, 'Proserpina', 2, 43, 0, 0, 'proserpina.svg');/***/ -- Proserpina
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (58, 'Waldemath', 2, 44, 0, 0, 'waldemath.svg');/***/ -- Waldemath

-- ***** Houses cusps ( -100 <= num <= -199 ) related to swe_houses()
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-100, 'Cusp 01', 3, 50, 0, 1, 'cusp_01.svg');/***/ -- House cusp I (Asc)
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-101, 'Cusp 02', 3, 51, 0, 1, 'cusp_02.svg');/***/ -- House cusp II
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-102, 'Cusp 03', 3, 52, 0, 1, 'cusp_03.svg');/***/ -- House cusp III
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-103, 'Cusp 04', 3, 53, 0, 1, 'cusp_04.svg');/***/ -- House cusp IV (FC)
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-104, 'Cusp 05', 3, 54, 0, 1, 'cusp_05.svg');/***/ -- House cusp V
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-105, 'Cusp 06', 3, 55, 0, 1, 'cusp_06.svg');/***/ -- House cusp VI
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-106, 'Cusp 07', 3, 56, 0, 1, 'cusp_07.svg');/***/ -- House cusp VII (Des)
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-107, 'Cusp 08', 3, 57, 0, 1, 'cusp_08.svg');/***/ -- House cusp VIII
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-108, 'Cusp 09', 3, 58, 0, 1, 'cusp_09.svg');/***/ -- House cusp IX
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-109, 'Cusp 10', 3, 59, 0, 1, 'cusp_10.svg');/***/ -- House cusp X (MC)
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-110, 'Cusp 11', 3, 60, 0, 1, 'cusp_11.svg');/***/ -- House cusp XI
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-111, 'Cusp 12', 3, 61, 0, 1, 'cusp_12.svg');/***/ -- House cusp XII
/* Gauquelin sectors */
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-112, 'Sector 01', 4, 62, 0, 1, 'gauquelin_01.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-113, 'Sector 02', 4, 63, 0, 1, 'gauquelin_02.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-114, 'Sector 03', 4, 64, 0, 1, 'gauquelin_03.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-115, 'Sector 04', 4, 65, 0, 1, 'gauquelin_04.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-116, 'Sector 05', 4, 66, 0, 1, 'gauquelin_05.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-117, 'Sector 06', 4, 67, 0, 1, 'gauquelin_06.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-118, 'Sector 07', 4, 68, 0, 1, 'gauquelin_07.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-119, 'Sector 08', 4, 69, 0, 1, 'gauquelin_08.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-120, 'Sector 09', 4, 70, 0, 1, 'gauquelin_09.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-121, 'Sector 10', 4, 71, 0, 1, 'gauquelin_10.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-122, 'Sector 11', 4, 72, 0, 1, 'gauquelin_11.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-123, 'Sector 12', 4, 73, 0, 1, 'gauquelin_12.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-124, 'Sector 13', 4, 74, 0, 1, 'gauquelin_13.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-125, 'Sector 14', 4, 75, 0, 1, 'gauquelin_14.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-126, 'Sector 15', 4, 76, 0, 1, 'gauquelin_15.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-127, 'Sector 16', 4, 77, 0, 1, 'gauquelin_16.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-128, 'Sector 17', 4, 78, 0, 1, 'gauquelin_17.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-129, 'Sector 18', 4, 79, 0, 1, 'gauquelin_18.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-130, 'Sector 19', 4, 80, 0, 1, 'gauquelin_19.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-131, 'Sector 20', 4, 81, 0, 1, 'gauquelin_20.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-132, 'Sector 21', 4, 82, 0, 1, 'gauquelin_21.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-133, 'Sector 22', 4, 83, 0, 1, 'gauquelin_22.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-134, 'Sector 23', 4, 84, 0, 1, 'gauquelin_23.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-135, 'Sector 24', 4, 85, 0, 1, 'gauquelin_24.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-136, 'Sector 25', 4, 86, 0, 1, 'gauquelin_25.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-137, 'Sector 26', 4, 87, 0, 1, 'gauquelin_26.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-138, 'Sector 27', 4, 88, 0, 1, 'gauquelin_27.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-139, 'Sector 28', 4, 89, 0, 1, 'gauquelin_28.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-140, 'Sector 29', 4, 90, 0, 1, 'gauquelin_29.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-141, 'Sector 30', 4, 91, 0, 1, 'gauquelin_30.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-142, 'Sector 31', 4, 92, 0, 1, 'gauquelin_31.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-143, 'Sector 32', 4, 93, 0, 1, 'gauquelin_32.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-144, 'Sector 33', 4, 94, 0, 1, 'gauquelin_33.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-145, 'Sector 34', 4, 95, 0, 1, 'gauquelin_34.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-146, 'Sector 35', 4, 96, 0, 1, 'gauquelin_35.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-147, 'Sector 36', 4, 97, 0, 1, 'gauquelin_36.svg');/***/

/* Asc, Mc, etc */
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-148, 'Asc', 3, 100, 1, 1, 'asc.svg');/***/ -- Asc
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-149, 'Mc', 3, 101, 1, 1, 'mc.svg');/***/ -- Mc
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-150, 'Armc', 3, 104, 0, 1, 'armc.svg');/***/ -- ARMC
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-151, 'Vertex', 3, 105, 0, 1, 'vertex.svg');/***/ -- Vertex
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-152, 'Equatorial Ascendant', 3, 106, 0, 1, 'equasc.svg');/***/ -- Equatorial ascendant
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-153, 'Co-ascendant (Koch)', 3, 107, 0, 1, 'coasc1.svg');/***/ -- Co-Ascendant (Koch)
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-154, 'Co-ascendant (Munkasey)', 3, 108, 0, 1, 'coasc2.svg');/***/ -- Co-Ascendant (Munkasey)
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-155, 'Polar Ascendant (Munkasey)', 3, 109, 0, 1, 'poasc.svg');/***/ -- Polar Ascendant (Munkasey)
-- Additional values:
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-156, 'Dsc', 3, 102, 0, 1, 'dsc.svg');/***/ -- Dsc
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-157, 'Ic', 3, 103, 0, 1, 'ic.svg');/***/ -- Ic
--

-- ***** Fixed Stars
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1000, 'Aldebaran', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1001, 'Algol', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1002, 'Antares', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1003, 'Regulus', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1004, 'Sirius', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1005, 'Spica', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1006, 'Gal. Center', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1007, 'Great Attractor', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1008, 'Virgo Cluster', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1009, 'Andromeda Galaxy', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1010, 'Praesepe Cluster', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1011, 'Deneb', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1012, 'Rigel', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1013, 'Mira', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1014, 'Ain', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Andromeda **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1015, 'Alpheratz', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1016, 'Mirach', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1017, 'Almaak', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Aquila **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1018, 'Altair', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1019, 'Alshain', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1020, 'Tarazed', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1021, 'Deneb Okab', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1022, 'Dheneb', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1023, 'Al Thalimaim', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Aquarius **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1024, 'Sadalmelek', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1025, 'Sadalsuud', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1026, 'Sadalachbia', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1027, 'Skat', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1028, 'Albali', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1029, 'Ancha', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1030, 'Situla', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1031, 'Seat', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Ara **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1032, 'Ara', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Aries **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1033, 'Hamal', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1034, 'Sheratan', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1035, 'Mesarthim', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1036, 'Botein', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Auriga **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1037, 'Capella', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1038, 'Menkalinan', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1039, 'Prijipati', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1040, 'Maaz', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1041, 'Al Anz', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1042, 'Haedi', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1043, 'Hoedus II', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1044, 'Hasseleh', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1045, 'Al Khabdhilinan', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Bootes **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1046, 'Arcturus', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1047, 'Nekkar', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1048, 'Seginus', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1049, 'Haris', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1050, 'Princeps', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1051, 'Izar', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1052, 'Mufrid', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1053, 'Asellus Primus', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1054, 'Asellus Secundus', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1055, 'Asellus Tertius', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1056, 'Alkalurops', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1057, 'Ceginus', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1058, 'Merga', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Caelum **
-- ** Camelopardalis **
-- ** Capricornus **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1059, 'Giedi Prima', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1060, 'Giedi Secunda', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1061, 'Dabih', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1062, 'Nashira', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1063, 'Deneb Algedi', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1064, 'Castra', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1065, 'Armus', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1066, 'Dorsum', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1067, 'Alshat', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1068, 'Oculus', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1069, 'Bos', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Carina **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1070, 'Canopus', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1071, 'Miaplacidus', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1072, 'Avior', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1073, 'Foramen', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1074, 'Scutulum', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Cassiopeia **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1075, 'Schedar', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1076, 'Caph', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1077, 'Tsih', 5, 1000, 0, 0, 'fixedstar.svg');/***/
--insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
--values (-1078, 'Ruchbah', 5, 1000, 0, 0, 'fixedstar.svg');/*?*/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1079, 'Segin', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1080, 'Achird', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1081, 'Marfak', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Centaurus **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1082, 'Rigel Kentaurus', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1083, 'Hadar', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1084, 'Muhlifain', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1085, 'Menkent', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1086, 'Ke Kwan', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1087, 'Proxima Cent.', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Cepheus **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1088, 'Alderamin', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1089, 'Alphirk', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1090, 'Alrai', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1091, 'Kurhah', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1092, 'Erakis', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1093, 'The Garnet Star', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1094, 'Kurdah', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1095, 'Al Kalb al Rai', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Cetus **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1096, 'Menkar', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1097, 'Diphda', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1098, 'Kaffaljidhma', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1099, 'Baten Kaitos', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1100, 'Deneb Algenubi', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1101, 'Deneb Kaitos', 5, 1000, 0, 0, 'fixedstar.svg');/***/
--insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
--values (-1102, 'Menkar', 5, 1000, 0, 0, 'fixedstar.svg');/*?*/
-- ** Chameleon **
-- ** Circinus **
-- ** Canis Major **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1103, 'Mirzam', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1104, 'Muliphein', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1105, 'Wezen', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1106, 'Adara', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1107, 'Furud', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1108, 'Aludra', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Canis Minor **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1109, 'Procyon', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1110, 'Gomeisa', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Cancer **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1112, 'Acubens', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1113, 'Al Tarf', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1114, 'Asellus Borealis', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1115, 'Tegmen', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Columba **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1116, 'Phact', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1117, 'Wazn', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1118, 'Tsze', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Coma Berenices **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1119, 'Diadem', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1120, 'Aldafirah', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1121, 'Kissin', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Corona Borealis **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1122, 'Alphecca', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1123, 'Nusakan', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1124, 'The Blaze Star', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Crater **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1125, 'Alkes', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1126, 'Alsharasif', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1127, 'Labrum', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Crux **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1128, 'Acrux', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1129, 'Mimosa', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1130, 'Gacrux', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Corvus **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1131, 'Alchiba', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1132, 'Kraz', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1133, 'Gienah', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1134, 'Algorab', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1135, 'Minkar', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Canis Venatici **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1136, 'Cor Caroli', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1137, 'Asterion', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Cygnus **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1138, 'Albireo', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1139, 'Sador', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1140, 'Gienah Cygni', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1141, 'Azelfafage', 5, 1000, 0, 0, 'fixedstar.svg');/***/
--insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
--values (-1142, 'Ruchbah', 5, 1000, 0, 0, 'fixedstar.svg');/*?*/
-- ** Delphinus **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1143, 'Sualocin', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1144, 'Rotanev', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1145, 'Deneb Dulphim', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Dorado **
-- ** Draco **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1146, 'Thuban', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1147, 'Rastaban', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1148, 'Eltanin', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1149, 'Nodus II', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1150, 'Tyl', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1151, 'Nodus I', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1152, 'Edasich', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1153, 'Giansar', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1154, 'Arrakis', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1155, 'Kuma', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1156, 'Grumium', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1157, 'Alsafi', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1158, 'Dziban', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1159, 'Alathfar', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Equuleus **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1160, 'Kitalpha', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Eridanus **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1161, 'Achernar', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1162, 'Cursa', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1163, 'Zaurak', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1164, 'Rana', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1165, 'Azha', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1166, 'Acamar', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1167, 'Zibal', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1168, 'Beid', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1169, 'Keid', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1170, 'Angetenar', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1171, 'Theemin', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1172, 'Sceptrum', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Fornax **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1173, 'Fornacis', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Gemini **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1174, 'Castor', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1175, 'Pollux', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1176, 'Alhena', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1177, 'Wasat', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1178, 'Mebsuta', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1179, 'Mekbuda', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1180, 'Propus', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1181, 'Tejat', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1182, 'Alzirr', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Grus **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1183, 'Alnair', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1184, 'Al Dhanab', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Hercules **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1185, 'Ras Algethi', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1186, 'Kornephoros', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1187, 'Sarin', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1188, 'Marsik', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1189, 'Masym', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1190, 'Kajam', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1191, 'Apex', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Horologium **
-- ** Hydra **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1192, 'Alphard', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1193, 'Cor Hydrae', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1194, 'Al Minliar al Shuja', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1195, 'Ukdah', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1196, 'Minchir', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Hydrus **
-- ** Indus **
-- ** Lacerta **
-- ** Leo **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1197, 'Denebola', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1198, 'Algieba', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1199, 'Dhur', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1200, 'Zosma', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1201, 'Ras Elased Australis', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1202, 'Adhafera', 5, 1000, 0, 0, 'fixedstar.svg');/***/
--insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
--values (-1203, 'Algieba', 5, 1000, 0, 0, 'fixedstar.svg');/*?*/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1204, 'Tse Tseng', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1205, 'Alminhar', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1206, 'Alterf', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1207, 'Ras Elased Borealis', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1208, 'Subra', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1209, 'Coxa', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1210, 'Chertan', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Lepus **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1211, 'Arneb', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1212, 'Nihal', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Libra **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1213, 'Zugen Elgenubi', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1214, 'Zuben Eshmali', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1215, 'Zuben Elakrab', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1216, 'Zuben Elakribi', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1217, 'Zuben Hakrabi', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1218, 'Brachium', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Leo Minor **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1219, 'Praecipua', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Lupus **
-- ** Lynx **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1220, 'Alsciaukat', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1221, 'Mabsuthat', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Lyra **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1222, 'Vega', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1223, 'Sheliak', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1224, 'Sulaphat', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1225, 'Aladfar', 5, 1000, 0, 0, 'fixedstar.svg');/***/
--insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
--values (-1226, 'Alathfar', 5, 1000, 0, 0, 'fixedstar.svg');/*?*/
-- ** Mensa **
-- ** Microscopium **
-- ** Monoceros **
-- ** Musca **
-- ** Norma **
-- ** Octans **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1227, 'Polaris Australis', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Ophiucus **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1228, 'Rasalhague', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1229, 'Celbalrai', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1230, 'Yed Prior', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1231, 'Yed Posterior', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1232, 'Han', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1233, 'Sabik', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1234, 'Marfik', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1235, 'Sinistra', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1236, "Barnard's star", 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Orion **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1237, 'Betelgeuse', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1238, 'Bellatrix', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1239, 'Mintaka', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1240, 'Alnilam', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1241, 'Alnitak', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1242, 'Hatsya', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1243, 'Saiph', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1244, 'Heka', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1245, 'Tabit', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1246, 'Thabit', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Pavo **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1247, 'Peacock', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Phoenix **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1248, 'Ankaa', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Pegasus **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1249, 'Markab', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1250, 'Scheat', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1251, 'Algenib', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1252, 'Enif', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1253, 'Homam', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1254, 'Matar', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1255, 'Biham', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1256, 'Sadalbari', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1257, 'Kerb', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1258, 'Salm', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Perseus **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1259, 'Mirfak', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1261, 'Atik', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1262, 'Miram', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1263, 'Misam', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1264, 'Menkib', 5, 1000, 0, 0, 'fixedstar.svg');/***/
--insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
--values (-1265, 'Atik', 5, 1000, 0, 0, 'fixedstar.svg');/*?*/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1266, 'Gorgona Secunda', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1267, 'Gorgona Tertia', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1268, 'Gorgona Quarta', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Pictor **
-- ** Piscis Austrinus **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1269, 'Fomalhaut', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Pisces **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1270, 'Alrischa', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1271, 'Fum Alsamakah', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1272, 'Al Pherg', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Puppis **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1273, 'Naos', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1274, 'Asmidiske', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Pyxis **
-- ** Reticulum **
-- ** Sculptor **
-- ** Scorpius **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1275, 'Akrab', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1276, 'Dschubba', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1277, 'Sargas', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1278, 'Shaula', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1279, 'Jabbah', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1280, 'Grafias', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1281, 'Alniyat', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1282, 'Lesath', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1283, 'Jabhat al Akrab', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Scutum **
-- ** Serpens **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1284, 'Unukalhai', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1285, 'Chow', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1286, 'Alya', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Sextans **
-- ** Sagitta **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1287, 'Sham', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Sagittarius **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1288, 'Rukbat', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1289, 'Arkab Prior', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1290, 'Arkab Posterior', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1291, 'Alnasl', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1292, 'Kaus Medis', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1293, 'Kaus Australis', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1294, 'Ascella', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1295, 'Kaus Borealis', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1296, 'Polis', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1297, 'Ain al Rami', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1298, 'Manubrium', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1299, 'Albaldah', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1300, 'Nunki', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1301, 'Terebellium', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Taurus **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1302, 'Elnath', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1303, 'Hyadum I', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1304, 'Hyadum II', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1305, 'Al Hecka', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1306, 'Alcyone', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1307, 'Caleano', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1308, 'Electra', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1309, 'Taygeta', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1310, 'Maia', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1311, 'Asterope', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1312, 'Sterope I', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1313, 'Sterope II', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1314, 'Merope', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1315, 'Atlas', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Telescopium **
-- ** Triangulum Australe **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1316, 'Atria', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Triangulum **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1317, 'Ras Mutallah', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Tucana **
-- ** Ursa Major **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1318, 'Dubhe', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1319, 'Merak', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1320, 'Phecda', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1321, 'Megrez', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1322, 'Alioth', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1323, 'Mizar', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1324, 'Alkaid', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1325, 'Al Haud', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1326, 'Talitha Borealis', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1327, 'Talitha Australis', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1328, 'Tania Borealis', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1329, 'Tania Australis', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1330, 'Alula Borealis', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1331, 'Alula Australis', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1332, 'Muscida', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1333, 'El Kophrah', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1334, 'Alcor', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1335, 'Saidak', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Ursa Minor **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1336, 'Polaris', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1337, 'Kochab', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1338, 'Pherkad', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1339, 'Yildun', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1340, 'Pherkad Minor', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Vela **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1341, 'Suhail al Muhlif', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1342, 'Markeb', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1343, 'Alsuhail', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1344, 'Suhail', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1345, 'Tseen Ke', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Virgo **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1346, 'Zavijava', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1347, 'Alaraph', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1348, 'Porrima', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1349, 'Auva', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1350, 'Vindemiatrix', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1351, 'Heze', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1352, 'Zaniah', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1353, 'Syrma', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1354, 'Khambalia', 5, 1000, 0, 0, 'fixedstar.svg');/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1355, 'Rijl al Awwa', 5, 1000, 0, 0, 'fixedstar.svg');/***/
-- ** Volans **
-- ** Vulpecula **
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-1356, 'Anser', 5, 1000, 0, 0, 'fixedstar.svg');/***/

-- ***** Asteroids (num > 10000)
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (146199, 'Eris', 6, 146199, 0, 0, 'eris.svg' );/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (17066, 'Nessus', 6, 17066, 0, 0, 'nessus.svg' );/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (60000, 'Quaoar', 6, 60000, 0, 0, 'quaoar.svg' );/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (100377, 'Sedna', 6, 100377, 0, 0, 'sedna.svg' );/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (30000, 'Varuna', 6, 30000, 0, 0, 'varuna.svg' );/***/
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (10128, 'Nemesis', 6, 10128, 0, 0, 'nemesis.svg' );/***/

-- ***** Parts ( -300 <= num )
insert into Planets (num, name, family, zValue, dftUse, dftAspect, glyph)
values (-300, 'Fortune (Rudhyar)', 7, 200, 0, 0, 'part_fortune.svg');/***/ -- Part of Fortune

insert into AspectFilters ( name, comments )
values ( '<Aspects Filter 1>', 'Example aspects filter.' );/***/

insert into PlanetFilters ( name, comments )
values ( '<Planets Filter 1>', 'Example planets filter.' );/***/

insert into OrbFilters ( name, comments )
values ( '<Orbs Filter 1>', 'Example orbs filter.' );/***/

insert into AspectRestrs ( name, comments )
values ( '<Aspects Restrs 1>', 'Example aspects restrictions.' );/***/

insert into OrbRestrs ( name, comments )
values ( '<Orbs Restrs 1>', 'Example orbs restrictions.' );/***/


insert into Profiles ( name, comments, plFiltIdx, aspFiltIdx, orbFiltIdx, aspRestrIdx, OrbRestrIdx )
values ('<Profile 1>', 'Example profile.', 1, 1, 1, 1, 1 );/***/

insert into Contexts ( name, comments )
values ( '<Context 1>', 'Example context.' );/***/

insert into Preferences ( ephePath, contextIdx, profileIdx, location, country, latitude, longitude, altitude, timezone, bgcolor, theme )
values ( '', 1, 1, 'Lausanne', 'Switzerland', 46.5, 6.6, 300, ':Europe/Zurich', '#000000', 'default' );/***/
