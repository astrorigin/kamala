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

#ifndef ZODIACORE_ORB_H
#define ZODIACORE_ORB_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _orb_t Orb;

typedef struct _orb_t OrbModifier;

struct _orb_t
{
    double  applying;
    double  separating;
    double  stable;
};

#define orb_new( x )            _orb_t_new( (struct _orb_t**) x )

#define orbmodifier_new( x )    _orb_t_new( (struct _orb_t**) x )

#define orb_delete( x )         _orb_t_delete( (struct _orb_t**) x )

#define orbmodifier_delete( x ) _orb_t_delete( (struct _orb_t**) x )

#define orb_copy( x, y )            (*x) = (*y)

#define orbmodifier_copy( x, y )    (*x) = (*y)

#define orb_average( x, y )         _orb_t_average( (struct _orb_t*) x, (struct _orb_t*) y )

#define orbmodifier_average( x, y ) _orb_t_average( (struct _orb_t*) x, (struct _orb_t*) y )

void _orb_t_new( struct _orb_t** );

void _orb_t_delete( struct _orb_t** );

Orb* orb_modify( Orb*, const OrbModifier* );

struct _orb_t* _orb_t_average( struct _orb_t*, const struct _orb_t* );


#ifdef __cplusplus
}
#endif

#endif /* !ZODIACORE_ORB_H */
