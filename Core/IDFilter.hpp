/*
 * This file is part of Gen7TimeFinder
 * Copyright (C) 2018 by Admiral_Fish
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef IDFILTER_HPP
#define IDFILTER_HPP

#include <QVector>
#include <QPair>
#include <Models/IDModel.hpp>

enum FilterType
{
    TID = 0,
    SID = 1,
    TIDSID = 2,
    G7TID = 3
};

class IDFilter
{

private:
    QVector<u32> tidFilter;
    QVector<u32> sidFilter;
    QVector<u32> tsvFilter;
    FilterType filterType;
    bool checkID;
    bool checkTSV;

public:
    IDFilter() {}
    IDFilter(QString idList, QString tsvList, int filterType);
    bool compare(IDModel frame);

};

#endif // IDFILTER_HPP
