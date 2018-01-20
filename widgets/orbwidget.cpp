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

/** @file orbwidget.cpp
 */

#include "orbwidget.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <QWidget>

#include <KDoubleNumInput>
#include <KLocalizedString>

#include <core.h>

OrbWidget::OrbWidget( const QString& label, const Orb& orb, QWidget* parent )
    : QWidget( parent )
{
    orb_copy( &_orb, &orb );

    QHBoxLayout* lyt = new QHBoxLayout( this );
    setLayout( lyt );

    QLabel* lbl = new QLabel( label, this );
    lyt->addWidget( lbl );

    orbAppInput = new KDoubleNumInput( 0, 30, 0, this );
    orbAppInput->setSuffix( i18nc( "Degree symbol", "°" ) );
//#warning FIXME doesnt accept Qt::AlignLeft|Qt::AlignVCenter
    orbAppInput->setLabel( i18nc( "Applying aspect", "App." ), Qt::AlignLeft );//|Qt::AlignVCenter);
    lyt->addWidget( orbAppInput );

    orbSepInput = new KDoubleNumInput( 0, 30, 0, this );
    orbSepInput->setSuffix( i18nc( "Degree symbol", "°" ) );
//#warning FIXME doesnt accept Qt::AlignLeft|Qt::AlignVCenter
    orbSepInput->setLabel( i18nc( "Separating aspect", "Sep." ), Qt::AlignLeft );//|Qt::AlignVCenter);
    lyt->addWidget( orbSepInput );

    orbStaInput = new KDoubleNumInput( 0, 30, 0, this );
    orbStaInput->setSuffix( i18nc( "Degree symbol", "°" ) );
//#warning FIXME doesnt accept Qt::AlignLeft|Qt::AlignVCenter
    orbStaInput->setLabel( i18nc( "Stable aspect", "Sta." ), Qt::AlignLeft );//|Qt::AlignVCenter);
    lyt->addWidget( orbStaInput );
}

void OrbWidget::reset()
{
    orbAppInput->setValue( _orb.applying );
    orbSepInput->setValue( _orb.separating );
    orbStaInput->setValue( _orb.stable );
}

Orb* OrbWidget::orb( Orb* ret ) const
{
    ret->applying = orbAppInput->value();
    ret->separating = orbSepInput->value();
    ret->stable = orbStaInput->value();
    return ret;
}

void OrbWidget::setOrb( const Orb& orb )
{
    orbAppInput->setValue( orb.applying );
    orbSepInput->setValue( orb.separating );
    orbStaInput->setValue( orb.stable );
}
