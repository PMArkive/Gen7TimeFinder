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

#include "IDModel.hpp"

IDModel::IDModel(u32 seed, u32 frame, u32 rand)
{
    this->seed = seed;
    this->frame = frame;
    tid = rand & 0xffff;
    sid = rand >> 16;
    tsv = (tid ^ sid) >> 4;
    displayTID = rand % 1000000;
}

QString IDModel::getDateTime()
{
    return target.toString(Qt::DefaultLocaleShortDate);
}

u32 IDModel::getSeed() const
{
    return seed;
}

u32 IDModel::getFrame() const
{
    return frame;
}

u16 IDModel::getTID() const
{
    return tid;
}

u16 IDModel::getSID() const
{
    return sid;
}

u16 IDModel::getTSV() const
{
    return tsv;
}

u32 IDModel::getDisplayTID() const
{
    return displayTID;
}

void IDModel::setTarget(const QDateTime &value)
{
    target = value;
}
