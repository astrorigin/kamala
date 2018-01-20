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

#include "orb.h"

void _orb_t_new( struct _orb_t** orb )
{
    assert( *orb == NULL );
    Trace( printf( "-- New struct orb\n" ); )
    *orb = Malloc( sizeof( struct _orb_t ) );

    (*orb)->applying = (*orb)->separating = (*orb)->stable = 0;
}

void _orb_t_delete( struct _orb_t** orb )
{
    assert( *orb );
    Trace( printf( "-- Delete struct orb\n" ); )
    Free( *orb, sizeof( struct _orb_t ) );
    *orb = NULL;
}

Orb* orb_modify( Orb* orb, const OrbModifier* mod )
{
    orb->applying += ( orb->applying / 100 ) * mod->applying;
    orb->separating += ( orb->separating / 100 ) * mod->separating;
    orb->stable += ( orb->stable / 100 ) * mod->stable;
    return orb;
}

struct _orb_t* _orb_t_average( struct _orb_t* orb, const struct _orb_t* other )
{
    orb->applying = ( orb->applying + other->applying ) / 2;
    orb->separating = ( orb->separating + other->separating ) / 2;
    orb->stable = ( orb->stable + other->stable ) / 2;
    return orb;
}
