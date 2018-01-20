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

/** @file bunch.cpp
 */

#include "bunch.hpp"

#include <QList>
#include <QListIterator>
#include <QPair>
#include <KDebug>

#include <core.h>

extern "C" {
#include <swephexp.h>
}

#include <math.h>

Bunch::Bunch( double wdth, double pos )
    : width( wdth ),
    center( pos )
{
    append( pos );
}

void Bunch::addFlower( double pos )
{
    append( pos );
    calcCenter();
}

void Bunch::calcCenter()
{
    int tmp = 0, i, j;
    double dist, p1, p2, maxp1, maxp2;
    const int cnt = count();

    for ( i = 0; i < cnt - 1; ++i )
    {
        p1 = at( i );
        for ( j = i + 1; j < cnt; ++j )
        {
            p2 = at( j );
            dist = fabs( swe_difdeg2n( p1, p2 ) );
            if ( dist >= tmp )
            {
                maxp1 = p1;
                maxp2 = p2;
                tmp = dist;
            }
        }
    }
    center = swe_deg_midp( maxp1, maxp2 );
}

bool Bunch::acceptFlower( double pos ) const
{
    int i, applic;
    double diffret, factor;

    i = match_aspect( pos, 0, center, 0, 0, orb(),
        &diffret, &applic, &factor );

    if ( !i )
        return true;
    return false;
}

bool Bunch::acceptBunch( Bunch* other ) const
{
    int i, applic;
    double diffret, factor;

    i = match_aspect( center, 0, other->center, 0, 0, orb() + other->orb(),
        &diffret, &applic, &factor);

    if ( !i )
        return true;
    return false;
}

double Bunch::orb() const
{
    return ( width * count() ) / 2;
}

void Bunch::addBunch( const Bunch& other )
{
    append( other );
    calcCenter();
}

static double s_bunchCenter; // unthreadsafe solution.

QList<QPair<double, double> > Bunch::arrange()
{
    s_bunchCenter = center;
    qSort( begin(), end(), mySort );

    QList<QPair<double, double> > ret;
    double dist = orb() - ( width / 2 );
    const int cnt = count();

    for ( int i = 0; i < cnt; ++i )
    {
        ret.append( QPair<double, double>( at( i ), swe_degnorm( center - dist ) ) );
        dist -= width;
    }
    return ret;
}

bool Bunch::mySort( double x, double y )
{
    return swe_difdeg2n( x, s_bunchCenter ) < swe_difdeg2n( y, s_bunchCenter );
#if 0
    const double t1 = swe_difdeg2n( x, s_bunchCenter );
    const double t2 = swe_difdeg2n( y, s_bunchCenter );
    if ( t1 >= t2 )
        return false;
    return true;
#endif
}

BunchBunch::BunchBunch( const QList<double>& inpt, double wdth )
    : input( inpt )
{
    if ( input.count() > 36 )
      // usual width break
        wdth = 360.0 / input.count();

    width = wdth;
    QListIterator<double> iter( input );
    while ( iter.hasNext() )
    {
        addFlower( iter.next() );
    }
    arrange();
}

BunchBunch::~BunchBunch()
{
    QListIterator<Bunch*> iter( *this );
    while ( iter.hasNext() )
        delete iter.next();
}

void BunchBunch::addFlower( double pos )
{
    const int cnt = count();
    if ( cnt == 0 )
    {
        newBunch( pos );
    }
    else
    {
        for ( int i = 0; i < cnt; ++i )
        {
            if ( at( i )->acceptFlower( pos ) )
            {
                at( i )->addFlower( pos );
                return;
            }
        }
        newBunch( pos );
    }
}

void BunchBunch::newBunch( double pos )
{
    append( new Bunch( width, pos ) );
}

void BunchBunch::arrange()
{
    bool test = true;
    while ( test )
    {
        test = subArrange();
        if ( !test )
        {
            const int cnt = count();
            const int idx = cnt / 2;
            for ( int i = 0; i < idx; ++i )
            {
                swap( i, cnt - ( i + 1 ) );
            }
            test = subArrange();
        }
    }
}

#if 0
int BunchBunch::myReverse(double x, double y)
{
    if (x > y)
        return -1;
    else if (y > x)
        return 1;
    return 0;
}
#endif

bool BunchBunch::subArrange()
{
    QList<Bunch*> b( *this );
    const int cnt = count();
    Bunch *b1, *b2;
    for ( int i = 0; i < cnt - 1; ++i )
    {
        for ( int j = 1; j < cnt; ++j )
        {
            if ( i == j )
                continue;
            if ( b.at( i )->acceptBunch( b.at( j ) ) )
            {
                b1 = b.at( i );
                b2 = b.at( j );
                removeOne( b1 );
                removeOne( b2 );
                b1->addBunch( *b2 );
                append( b1 );
                delete b2;
                return true;
            }
        }
    }
    return false;
}

QList<double> BunchBunch::offer()
{
    int key, start, idx;
    Bunch *b;
    QList<double> ret;
    for ( int i = 0; i < input.count(); ++i )
        ret << -1;
    QListIterator<Bunch*> iter( *this );
    while ( iter.hasNext() )
    {
        b = iter.next();
        QList<QPair<double, double> > pairs = b->arrange();
        QListIterator<QPair<double, double> > iter2( pairs );
        while ( iter2.hasNext() )
        {
            QPair<double, double> pair = iter2.next();
            key = -1;
            start = -1;
            while ( key == -1 )
            {
                idx = input.indexOf( pair.first, start + 1 );
                Q_ASSERT( idx != -1 );
                if ( ret.at( idx ) == -1 )
                {
                    key = idx;
                }
                else
                {
                    start = idx;
                }
            }
            ret[key] = pair.second;
        }
    }
    return ret;
}
