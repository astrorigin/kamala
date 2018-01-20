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

create table Aspects
(
    _idx        integer primary key,
    name        varchar unique,
    family      integer default 4 check ( family between 0 and 4 ),
    comments    varchar default '',
    isAbs       integer default 1 check ( isAbs in (0, 1) ),
    signStrict  integer default 0 check ( signStrict between 0 and 7 ),
    angle       numeric check ( angle >= 0 and angle < 360 ),
    dftUse      integer default 0 check ( dftUse in (0, 1) ),
    dftAppOrb   numeric default 0.5 check ( dftAppOrb >= 0 ),
    dftSepOrb   numeric default 0.5 check ( dftSepOrb >= 0 ),
    dftStaOrb   numeric default 0.5 check ( dftStaOrb >= 0 ),
    color       varchar default '#000000',
    glyph       varchar default 'glyph.svg',
    zValue      integer default 1 check ( zValue > 0 ),
    unique ( isAbs, signStrict, angle )
);/***/

create table Planets
(
    _idx        integer primary key,
    num         integer unique,
    name        varchar unique,
    family      integer default 6 check ( family between 0 and 7 ),
    comments    varchar default '',
    dftUse      integer default 0 check ( dftUse in (0, 1) ),
    dftAspect   integer default 0 check ( dftAspect in (0, 1) ),
    dftAppOrbMod numeric default 0,
    dftSepOrbMod numeric default 0,
    dftStaOrbMod numeric default 0,
    color       varchar default '',
    glyph       varchar default 'glyph.svg',
    zValue      integer default 1 check ( zValue > 0 )
);/***/

create table AspectFilters
(
    _idx        integer primary key,
    name        varchar unique,
    comments    varchar default ''
);/***/

create table _aspectFilters
(
    _idx        integer,
    aspIdx      integer,
    aspUse      integer check ( aspUse in (0, 1) ),
    primary key ( _idx, aspIdx )
);/***/

create trigger AspectFilterInsertTrigger
after insert on AspectFilters for each row
begin
    insert into _aspectFilters ( _idx, aspIdx, aspUse )
        select new._idx, _idx, dftUse from Aspects;
end;/***/

create trigger AspectFilterDeleteTrigger
before delete on AspectFilters for each row
begin
    /*select raise (rollback, 'Error: delete on AspectFilters violates foreign key constraint.')
        where (select aspanFiltIdx from Settings where aspanFiltIdx = old._idx) is not null;
    select raise (rollback, 'Error: delete on AspectFilters violates foreign key constraint.')
        where (select aspanFiltIdx from MidPointFilters where aspanFiltIdx = old._idx) is not null;*/
    delete from _aspectFilters where _idx = old._idx;
end;/***/

create table PlanetFilters
(
    _idx        integer primary key,
    name        varchar unique,
    comments    varchar default ''
);/***/

create table _planetFilters
(
    _idx        integer,
    plIdx       integer,
    plUse       integer check ( plUse in (0, 1) ),
    primary key ( _idx, plIdx )
);/***/

create trigger PlanetFilterInsertTrigger
after insert on PlanetFilters for each row
begin
    insert into _planetFilters ( _idx, plIdx, plUse )
        select new._idx, _idx, dftUse from Planets;
end;/***/

create trigger PlanetFilterDeleteTrigger
before delete on PlanetFilters for each row
begin
    /*select raise (rollback, 'Error: delete on PlanetFilters violates foreign key constraint.')
        where (select planFiltIdx from Settings where planFiltIdx = old._idx) is not null;
    select raise (rollback, 'Error: delete on PlanetFilters violates foreign key constraint.')
        where (select planFiltIdx from MidPointFilters where planFiltIdx = old._idx) is not null;*/
    delete from _planetFilters where _idx = old._idx;
end;/***/

create table OrbFilters
(
    _idx        integer primary key,
    name        varchar unique,
    comments    varchar default ''
);/***/

create table _orbFilters
(
    _idx        integer,
    aspIdx      integer,
    appOrb      numeric check ( appOrb >= 0 ),
    sepOrb      numeric check ( sepOrb >= 0 ),
    staOrb      numeric check ( staOrb >= 0 ),
    primary key ( _idx, aspIdx )
);/***/

create trigger OrbFilterInsertTrigger
after insert on OrbFilters for each row
begin
    insert into _orbFilters ( _idx, aspIdx, appOrb, sepOrb, staOrb )
        select new._idx, _idx, dftAppOrb, dftSepOrb, dftStaOrb from Aspects;
end;/***/

create trigger OrbFilterDeleteTrigger
before delete on OrbFilters for each row
begin
    /*select raise (rollback, 'Error: delete on OrbFilters violates foreign key constraint.')
        where (select planFiltIdx from Settings where planFiltIdx = old._idx) is not null;
    select raise (rollback, 'Error: delete on OrbFilters violates foreign key constraint.')
        where (select planFiltIdx from MidPointFilters where planFiltIdx = old._idx) is not null;*/
    delete from _orbFilters where _idx = old._idx;
end;/***/

create table AspectRestrs
(
    _idx        integer primary key,
    name        varchar unique,
    comments    varchar default ''
);/***/

create table _aspectRestrs
(
    _idx        integer,
    plIdx       integer,
    aspUse      integer check ( aspUse in (0, 1) ),
    primary key ( _idx, plIdx )
);/***/

create trigger AspectRestrInsertTrigger
after insert on AspectRestrs for each row
begin
    insert into _aspectRestrs ( _idx, plIdx, aspUse )
        select new._idx, _idx, dftAspect from Planets;
end;/***/

create trigger AspectRestrDeleteTrigger
before delete on AspectRestrs for each row
begin
    /*select raise (rollback, 'Error: delete on AspectRestrs violates foreign key constraint.')
        where (select aspanFiltIdx from Settings where aspanFiltIdx = old._idx) is not null;
    select raise (rollback, 'Error: delete on AspectRestrs violates foreign key constraint.')
        where (select aspanFiltIdx from MidPointRestrs where aspanFiltIdx = old._idx) is not null;*/
    delete from _aspectRestrs where _idx = old._idx;
end;/***/

create table OrbRestrs
(
    _idx        integer primary key,
    name        varchar unique,
    comments    varchar default ''
);/***/

create table _orbRestrs
(
    _idx        integer,
    plIdx       integer,
    appOrbMod   numeric,
    sepOrbMod   numeric,
    staOrbMod   numeric,
    primary key ( _idx, plIdx )
);/***/

create trigger OrbRestrInsertTrigger
after insert on OrbRestrs for each row
begin
    insert into _orbRestrs ( _idx, plIdx, appOrbMod, sepOrbMod, staOrbMod )
        select new._idx, _idx, dftAppOrbMod, dftSepOrbMod, dftStaOrbMod from Planets;
end;/***/

create trigger OrbRestrDeleteTrigger
before delete on OrbRestrs for each row
begin
    /*select raise (rollback, 'Error: delete on OrbRestrs violates foreign key constraint.')
        where (select planFiltIdx from Settings where planFiltIdx = old._idx) is not null;
    select raise (rollback, 'Error: delete on OrbRestrs violates foreign key constraint.')
        where (select planFiltIdx from MidPointRestrs where planFiltIdx = old._idx) is not null;*/
    delete from _orbRestrs where _idx = old._idx;
end;/***/

create table Profiles
(
    _idx        integer primary key,
    name        varchar unique,
    comments    varchar default '',
    calcMidp    integer default 0 check ( calcMidp in (0, 1) ),
    drawMidp    integer default 0 check ( drawMidp in (0, 1) ),
    plFiltIdx   integer,
    aspFiltIdx  integer,
    orbFiltIdx  integer,
    aspRestrIdx integer,
    orbRestrIdx integer
);/***/

create table Contexts
(
    _idx        integer primary key,
    name        varchar unique,
    comments    varchar default '',
    xCentric    integer default 0,
    hSys        varchar default 'P',
    sidMode     integer default 256,
    sidT0       numeric default 0,
    sidAyanT0   numeric default 0,
    truePos     integer default 0 check ( truePos in (0, 1) )
);/***/

create table Preferences
(
    ephePath    varchar default '',
    contextIdx  integer,
    profileIdx  integer,
    location    varchar default '-?-',
    country     varchar default '-?-',
    latitude    numeric default 0 check ( latitude between -90 and 90 ),
    longitude   numeric default 0 check ( longitude between -180 and 180 ),
    altitude    integer default 0 check ( altitude >= 0 ),
    timezone    varchar default ':UTC',
    bgcolor     varchar default '#000000',
    theme       varchar default 'default',
    openMax     integer default 0 check ( openMax in (0, 1) )
);/***/

create table Horoscopes
(
    _idx        integer primary key,
    name        varchar unique,
    comments    varchar default '',
    datetime    varchar,
    timezone    varchar default ':UTC',
    isdst       integer default -1 check ( isdst in (-1, 0, 1) ),
    utcoffset   integer default 0,
    location    varchar,
    country     varchar,
    latitude    numeric default 0 check ( latitude between -90 and 90 ),
    longitude   numeric default 0 check ( longitude between -180 and 180 ),
    altitude    integer default 0 check ( altitude >= 0 )
);/***/
