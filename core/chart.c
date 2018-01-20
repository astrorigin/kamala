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

#include "chart.h"

#include "prefs.h"

void chart_init( ZodiaCore* z )
{
    assert( z->chartCollection == NULL );
    vector_new( &z->chartCollection, 0 );
}

void chart_fini( ZodiaCore* z )
{
    assert( z->chartCollection );

    if ( z->chartCollection->len )
        vector_traverse( z->chartCollection, (void(*)(void*))&chart_delete );

    vector_delete( &z->chartCollection );
}

uint chart_register( ZodiaCore* z, Chart* c )
{
    assert( c );

    vector_append( z->chartCollection, c );
    return z->chartCollection->len - 1;
}

void chart_unregister( ZodiaCore* z, uint idx )
{
    assert( idx < z->chartCollection->len );
    vector_remove( z->chartCollection, idx );
}

void chart_new( ZodiaCore* z, Chart** c )
{
    assert( *c == NULL );
    Trace( printf( "-- New chart\n" ); )
    *c = Malloc( sizeof( Chart ) );

    (*c)->type = RadixChartType;
    (*c)->ctxt = z->prefs->context;
    Debug( (*c)->wh1 = )
    (*c)->wh2 = NULL;
    wheel_new( z, &(*c)->wh1 );

    (*c)->interAspects = NULL;
    vector_new( &(*c)->interAspects, 0 );
}

void chart_delete( Chart** c )
{
    assert( *c );

    wheel_delete( &(*c)->wh1 );

    if ( (*c)->wh2 )
        wheel_delete( &(*c)->wh2 );

    if ( (*c)->interAspects->len )
        vector_traverse( (*c)->interAspects, (void(*)(void*))&aspectdata_delete );
    vector_delete( &(*c)->interAspects );

    Trace( printf( "-- Delete chart\n" ); )
    Free( *c, sizeof( Chart ) );
    *c = NULL;
}

void chart_now( const ZodiaCore* z, Chart* c )
{
    assert( c );

    if ( !c->wh1->ctxt )
        c->wh1->ctxt = c->ctxt;

    if ( !c->wh1->prfl )
        c->wh1->prfl = z->prefs->profile;

    horoscope_now( z, c->wh1->horo );
}

void chart_clear( Chart* c )
{
    if ( c->interAspects->len )
        vector_traverse( c->interAspects, (void(*)(void*))&aspectdata_delete );
    c->interAspects->len = 0;
    vector_resize( c->interAspects );
}

void chart_calc( ZodiaCore* z, Chart* c )
{
    if ( c->type == RadixChartType )
    {
        wheel_calc( z, c->wh1 );
    }
    else if ( c->type == ComparedChartType )
    {
        assert( c->wh2 );
        wheel_calc( z, c->wh1 );
        wheel_calc( z, c->wh2 );
        chart_clear( c );
        chart_calc_interaspects( z, c );
    }
}

void chart_calc_interaspects( ZodiaCore* z, Chart* c )
{
    assert( c && c->wh1 && c->wh2 );

    chart_clear( c );

    const BTree* plData1 = btree_least( c->wh1->planets );
    const BTree* plData2 = btree_least( c->wh2->planets );
    assert( plData1 && plData2 );

    const BTree* aspects = btree_least( z->aspectCollection );

    const AspectFilter* aspFilt1 = c->wh1->prfl->aspectFilter;
    const AspectFilter* aspFilt2 = c->wh2->prfl->aspectFilter;

    const AspectRestr* aspRestr1 = c->wh1->prfl->aspectRestr;
    const AspectRestr* aspRestr2 = c->wh2->prfl->aspectRestr;

    const OrbFilter* orbFilt1 = c->wh1->prfl->orbFilter;
    const OrbFilter* orbFilt2 = c->wh2->prfl->orbFilter;

    const OrbRestr* orbRestr1 = c->wh1->prfl->orbRestr;
    const OrbRestr* orbRestr2 = c->wh2->prfl->orbRestr;

    BTree* itPlData1 = (BTree*) plData1;
    BTree* itPlData2 = (BTree*) plData2;
    BTree* itAspects = (BTree*) aspects;

    PosData* posData1, *posData2;
    Planet* pl1, *pl2;
    Aspect* asp;
    Orb orb1, *orb2;
    OrbModifier* mod1, *mod2;
    OrbModifier mod3;
    AspectData* aspData;

    double dif, factor;
    int i, appl;

    for ( ; itPlData1; itPlData1 = btree_next( itPlData1 ) )
    {
        posData1 = (PosData*) itPlData1->val;
        pl1 = posData1->planet;
        mod1 = (OrbModifier*) orbrestr_value( orbRestr1, pl1->_idx );

        for ( ; itPlData2; itPlData2 = btree_next( itPlData2 ) )
        {
            posData2 = (PosData*) itPlData2->val;
            pl2 = posData2->planet;
            mod2 = (OrbModifier*) orbrestr_value( orbRestr2, pl2->_idx );

            for ( ; itAspects; itAspects = btree_next( itAspects ) )
            {
                asp = (Aspect*) itAspects->val;

                if (    aspectfilter_value( aspFilt1, asp->_idx ) == False
                    ||  aspectfilter_value( aspFilt2, asp->_idx ) == False
                    ||  aspectrestr_value( aspRestr1, pl1->_idx ) == False
                    ||  aspectrestr_value( aspRestr1, pl2->_idx ) == False
                    ||  aspectrestr_value( aspRestr2, pl1->_idx ) == False
                    ||  aspectrestr_value( aspRestr2, pl2->_idx ) == False )
                {
                    continue;
                }

                orb_copy( &orb1, (Orb*) orbfilter_value( orbFilt1, asp->_idx ) );
                orb2 = (Orb*) orbfilter_value( orbFilt2, asp->_idx );
                orb_average( &orb1, orb2 );
                orbmodifier_copy( &mod3, mod1 );
                orbmodifier_average( &mod3, mod2 );
                orb_modify( &orb1, &mod3 );

                if ( !asp->isAbs )
                {
                    i = match_aspect3( posData1->res[0], posData1->res[3],
                        posData2->res[0], posData2->res[3],
                        asp->angle,
                        orb1.applying, orb1.separating, orb1.stable,
                        &dif, &appl, &factor );
                }
                else
                {
                    i = match_aspect4( posData1->res[0], posData1->res[3],
                        posData2->res[0], posData2->res[3],
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

                    vector_append( c->interAspects, (void*) aspData );
                }
            }
            itAspects = (BTree*) aspects;
        }
        itPlData2 = (BTree*) plData2;
    }
}
