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

#include "StationaryFilter.hpp"

StationaryFilter::StationaryFilter(const QVector<int> &minIV, const QVector<int> &maxIV, int nature, int hiddenPower, int ability, bool shiny, int gender)
{
    this->minIV = minIV;
    this->maxIV = maxIV;
    this->nature = nature;
    this->hiddenPower = hiddenPower;
    this->ability = ability;
    this->shiny = shiny;
    this->gender = gender;
}

bool StationaryFilter::compare(const StationaryResult &frame)
{
    for (int i = 0; i < 6; i++)
    {
        int iv = frame.getIV(i);
        if (iv < minIV[i] || iv > maxIV[i])
            return false;
    }

    if (nature != -1)
    {
        if (nature != frame.getNature())
            return false;
    }

    if (hiddenPower != -1)
    {
        if (hiddenPower != frame.getHiddenPower())
            return false;
    }

    if (ability != -1)
    {
        if (ability != frame.getAbility())
            return false;
    }

    if (shiny)
    {
        if (!frame.getShiny())
            return false;
    }

    if (gender != 0)
    {
        if (gender != frame.getGender() && frame.getGender() != 0)
            return false;
    }

    return true;
}
