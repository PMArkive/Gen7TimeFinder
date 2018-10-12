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

#include "StationaryModel.hpp"

StationaryModel::StationaryModel(u32 seed, u16 tid, u16 sid)
{
    this->seed = seed;
    tsv = (tid ^ sid) >> 4;
    for (int i = 0; i < 6; i++)
        ivs[i] = -1;
}

QString StationaryModel::getDateTime() const
{
    return target.toString(Qt::DefaultLocaleShortDate);
}

void StationaryModel::setTarget(const QDateTime &value)
{
    target = value;
}

u32 StationaryModel::getSeed() const
{
    return seed;
}

u32 StationaryModel::getPID() const
{
    return pid;
}

void StationaryModel::setPID(const u32 &value)
{
    pid = value;
    psv = ((pid >> 16) ^ (pid & 0xffff)) >> 4;
    shiny = psv == tsv;
}

u32 StationaryModel::getEC() const
{
    return ec;
}

void StationaryModel::setEC(const u32 &value)
{
    ec = value;
}

u32 StationaryModel::getFrame() const
{
    return frame;
}

void StationaryModel::setFrame(const u32 &value)
{
    frame = value;
}

u16 StationaryModel::getPSV() const
{
    return psv;
}

int StationaryModel::getHiddenPower() const
{
    return hiddenPower;
}

void StationaryModel::calcHiddenPower()
{
    hiddenPower = ((((ivs[0] & 1) + 2 * (ivs[1] & 1) + 4 * (ivs[2] & 1) + 8 * (ivs[5] & 1) + 16 * (ivs[3] & 1) + 32 * (ivs[4] & 1)) * 15) / 63);
}

int StationaryModel::getAbility() const
{
    return ability;
}

void StationaryModel::setAbility(const int &value)
{
    ability = value;
}

int StationaryModel::getNature() const
{
    return nature;
}

void StationaryModel::setNature(const int &value)
{
    nature = value;
}

QString StationaryModel::getGenderString() const
{
    return gender == 0 ? "-" : gender == 1 ? "♂" : "♀";
}

int StationaryModel::getGender() const
{
    return gender;
}

void StationaryModel::setGender(const int &value)
{
    gender = value;
}

int StationaryModel::getIV(int i) const
{
    return ivs[i];
}

void StationaryModel::setIV(const int &i, const int &value)
{
    ivs[i] = value;
}

bool StationaryModel::getShiny() const
{
    return shiny;
}

void StationaryModel::setShiny(bool value)
{
    shiny = value;
}

bool StationaryModel::getSynch() const
{
    return synch;
}

void StationaryModel::setSynch(bool value)
{
    synch = value;
}
