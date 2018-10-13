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

#include "Profile.hpp"

Profile::Profile()
{
    name = "None";
    offset = 17017;
    tick = 0x383e329;
    tid = 12345;
    sid = 54321;
    version = Game::UltraSun;
    shinyCharm = false;
}

Profile::Profile(QString name, u32 offset, u32 tick, u16 tid, u16 sid, Game version, bool shinyCharm)
{
    this->name = std::move(name);
    this->offset = offset;
    this->tick = tick;
    this->tid = tid;
    this->sid = sid;
    this->version = version;
    this->shinyCharm = shinyCharm;
}

QString Profile::getName() const
{
    return name;
}

u32 Profile::getOffset() const
{
    return offset;
}

u32 Profile::getTick() const
{
    return tick;
}

u16 Profile::getTID() const
{
    return tid;
}

u16 Profile::getSID() const
{
    return sid;
}

Game Profile::getVersion() const
{
    return version;
}

QString Profile::getVersionString() const
{
    switch (version)
    {
        case Game::Sun:
            return "Sun";
        case Game::Moon:
            return "Moon";
        case Game::UltraSun:
            return "Ultra Sun";
        case Game::UltraMoon:
            return "Ultra Moon";
    }
}

bool Profile::getShinyCharm() const
{
    return shinyCharm;
}
