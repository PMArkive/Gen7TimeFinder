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

#ifndef STATIONARYFILTER_HPP
#define STATIONARYFILTER_HPP

#include <QVector>
#include <Results/StationaryResult.hpp>

class StationaryFilter
{

private:
    QVector<int> minIV, maxIV;
    int nature{}, hiddenPower{}, ability{}, gender{};
    bool shiny{};

public:
    StationaryFilter() = default;
    StationaryFilter(const QVector<int> &minIV, const QVector<int> &maxIV, int nature, int hiddenPower, int ability, bool shiny, int gender);
    bool compare(const StationaryResult &frame);

};

#endif // STATIONARYFILTER_HPP
