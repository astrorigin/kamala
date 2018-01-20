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

#include "wheel.h"

void wheel_new( const ZodiaCore* z, Wheel** w )
{
    assert( *w == NULL );
    Trace( printf( "-- New wheel\n" ); )
    *w = Malloc( sizeof( Wheel ) );

    (*w)->type = RadixWheelType;
    Debug( (*w)->horo = NULL; )
    horoscope_new( z, &(*w)->horo );

    (*w)->ctxt = z->prefs->context;
    (*w)->prfl = z->prefs->profile;
    (*w)->planets = NULL;

    (*w)->aspects = NULL;
    vector_new( &(*w)->aspects, 0 );
}

void wheel_delete( Wheel** w )
{
    assert( *w );

    horoscope_delete( &(*w)->horo );

    if ( (*w)->planets )
    {
        btree_traverse( (*w)->planets, (void(*)(void*))&posdata_delete );
        btree_delete( &(*w)->planets );
    }

    if ( (*w)->aspects->len )
        vector_traverse( (*w)->aspects, (void(*)(void*))&aspectdata_delete );
    vector_delete( &(*w)->aspects );

    Trace( printf( "-- Delete wheel\n" ); )
    Free( *w, sizeof( Wheel ) );
    *w = NULL;
}

void wheel_clear( Wheel* w )
{
    if ( w->planets )
    {
        btree_traverse( w->planets, (void(*)(void*))&posdata_delete );
        btree_delete( &w->planets );
    }

    if ( w->aspects->len )
        vector_traverse( w->aspects, (void(*)(void*))&aspectdata_delete );
    w->aspects->len = 0;
    vector_resize( w->aspects );
}

void wheel_calc( ZodiaCore* z, Wheel* w )
{
    assert( w->horo && w->ctxt && w->prfl );

    wheel_clear( w );
    wheel_set_swe( w );
    wheel_calc_houses( z, w );
    wheel_calc_planets( z, w );
    wheel_calc_aspects( z, w );
}

void wheel_set_swe( const Wheel* w )
{
    const Context* c = w->ctxt;
    const Horoscope* h = w->horo;

    if ( c->sidMode != NoSiderealMode )
        swe_set_sid_mode( c->sidMode, c->sidT0, c->sidAyanT0 );

    if ( c->xCentric == TopoCentric )
        swe_set_topo( h->longitude, h->latitude, h->altitude );
}

void wheel_calc_houses( ZodiaCore* z, Wheel* w )
{
    int i = swe_houses_ex( w->horo->datetime->jd, context_swe_flags( w->ctxt ),
        w->horo->latitude, w->horo->longitude, w->ctxt->hSys, w->cusps, w->ascmc );
#ifndef NDEBUG
    if ( i != 0 )
    {
        printf( "Houses calc error %d\n", i );
    }
#endif /* !NDEBUG */

    const BTree* plColl = z->planetCollection;
    const PlanetFilter* plFilt = w->prfl->planetFilter;
    const int max = w->ctxt->hSys != 'G' ? 57 : 93;

    PosData* data;
    int x = 1;

    for ( i = w->ctxt->hSys != 'G' ? 45 : 57; i < max; ++i )
    {
        if ( planetfilter_value( plFilt, i ) == False )
        {
            ++x;
            continue;
        }
        data = NULL;
        posdata_new( &data );
        data->planet = btree_value( plColl, i );
        data->res[0] = w->cusps[x];
        btree_insert( &w->planets, i, (void*) data, NULL );
        btree_reroot( w->planets );
        ++x;
    }
    /* inserting ascmc & co */
    x = 0;
    for ( i = 93; i < 101; ++i )
    {
        if ( planetfilter_value( plFilt, i ) == False )
        {
            ++x;
            continue;
        }
        data = NULL;
        posdata_new( &data );
        data->planet = btree_value( plColl, i );
        data->res[0] = w->ascmc[x];
        btree_insert( &w->planets, i, (void*) data, NULL );
        btree_reroot( w->planets );
        ++x;
    }
    /* inserting additional Dsc & Ic */
    if ( planetfilter_value( plFilt, 101 ) != False )
    {
        data = NULL;
        posdata_new( &data );
        data->planet = btree_value( plColl, i );
        data->res[0] = swe_degnorm( w->ascmc[0] - 180 );
        btree_insert( &w->planets, 101, (void*) data, NULL );
        btree_reroot( w->planets );
    }
    if ( planetfilter_value( plFilt, 102 ) != False )
    {
        data = NULL;
        posdata_new( &data );
        data->planet = btree_value( plColl, i );
        data->res[0] = swe_degnorm( w->ascmc[1] - 180 );
        btree_insert( &w->planets, 102, (void*) data, NULL );
        btree_reroot( w->planets );
    }
}

void wheel_calc_planets( ZodiaCore* z, Wheel* w )
{
    const PlanetFilter* plFilt = w->prfl->planetFilter;

    const double jd = w->horo->datetime->jd;
    const int flag = context_swe_flags( w->ctxt );

    int i;

    Planet* pl1;
    PosData* data;
    BTree* it = btree_least( z->planetCollection );

    for ( ; it; it = btree_next( it ) )
    {
        pl1 = (Planet*) it->val;

        if ( planetfilter_value( plFilt, pl1->_idx ) == False
            || pl1->family == CuspsFamily
            || pl1->family == GauquelinFamily )
        {
            continue;
        }

        data = NULL;
        posdata_new( &data );
        data->planet = pl1;
        i = planet_calc( pl1, jd, flag, data->res );

        if ( i >= 0 )
        {
            btree_insert( &w->planets, pl1->_idx, (void*) data, NULL );
            btree_reroot( w->planets );
        }
        else posdata_delete( &data );
    }
}

void wheel_calc_aspects( ZodiaCore* z, Wheel* w )
{
    const AspectFilter* aspFilt = w->prfl->aspectFilter;
    const AspectRestr* aspRestr = w->prfl->aspectRestr;
    const OrbFilter* orbFilt = w->prfl->orbFilter;
    const OrbRestr* orbRestr = w->prfl->orbRestr;

    const BTree* plEnd = btree_most( w->planets );
    const BTree* aspStart = btree_least( z->aspectCollection );

    Planet* pl1, *pl2;
    Aspect* asp;
    BTree* iterPl1, *iterPl2;
    BTree* iterAsp;
    PosData* plData1, *plData2;
    Orb orb1;
    OrbModifier* mod1, *mod2, mod3;

    double dif, factor;
    int i, appl;
    AspectData* aspData;

    for ( iterPl1 = btree_least( w->planets ); iterPl1 != plEnd; iterPl1 = btree_next( iterPl1 ) )
    {
        pl1 = ((PosData*) iterPl1->val)->planet;

        if ( aspectrestr_value( aspRestr, pl1->_idx ) == False )
            continue;

        plData1 = (PosData*) iterPl1->val;
        mod1 = (OrbModifier*) orbrestr_value( orbRestr, pl1->_idx );

        for ( iterPl2 = btree_next( iterPl1 ); iterPl2; iterPl2 = btree_next( iterPl2 ) )
        {
            pl2 = ((PosData*) iterPl2->val)->planet;

            if ( aspectrestr_value( aspRestr, pl2->_idx ) == False ){
                continue;}

            plData2 = (PosData*) iterPl2->val;
            mod2 = (OrbModifier*) orbrestr_value( orbRestr, pl2->_idx );

            for ( iterAsp = (BTree*) aspStart; iterAsp; iterAsp = btree_next( iterAsp ) )
            {
                asp = (Aspect*) iterAsp->val;

                if ( aspectfilter_value( aspFilt, asp->_idx ) == False )
                    continue;

                if ( asp->signStrict > 0 )
                {
                    if ( abs( rasi_dif2( long2rasi( plData1->res[0] ),
                        long2rasi( plData2->res[0] ) ) ) != asp->signStrict - 1 )
                    {
                        continue;
                    }
                }

                orb_copy( &orb1, (Orb*) orbfilter_value( orbFilt, asp->_idx ) );
                orbmodifier_copy( &mod3, mod1 );
                orbmodifier_average( &mod3, mod2 );
                orb_modify( &orb1, &mod3 );

                if ( asp->isAbs )
                {
                    i = match_aspect4( plData1->res[0], plData1->res[3],
                        plData2->res[0], plData2->res[3],
                        asp->angle,
                        orb1.applying, orb1.separating, orb1.stable,
                        &dif, &appl, &factor );
                }
                else
                {
                    i = match_aspect3( plData1->res[0], plData1->res[3],
                        plData2->res[0], plData2->res[3],
                        asp->angle,
                        orb1.applying, orb1.separating, orb1.stable,
                        &dif, &appl, &factor );
                }

                if ( i == 0 )
                {
                    aspData = NULL;
                    aspectdata_new( &aspData );

                    aspData->planet1 = pl1;
                    aspData->planet2 = pl2;
                    aspData->aspect = asp;
                    aspData->delta = dif;
                    aspData->applying = appl;
                    aspData->factor = factor;

                    vector_append( w->aspects, aspData );
                }
            }
        }
    }
}
