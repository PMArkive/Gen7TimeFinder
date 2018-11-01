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

#ifndef PROFILE_HPP
#define PROFILE_HPP

#include <QString>
#include <Core/Game.hpp>
#include <cstdint>

using u32 = uint32_t;
using u16 = uint16_t;

class Profile
{

private:
    QString name;
    u32 offset, tick;
    u16 tid, sid;
    Game version;
    bool shinyCharm;

public:
    Profile();
    Profile(const QString &name, u32 offset, u32 tick, u16 tid, u16 sid, Game version, bool shinyCharm);
    QString getName() const;
    u32 getOffset() const;
    u32 getTick() const;
    u16 getTID() const;
    u16 getSID() const;
    Game getVersion() const;
    QString getVersionString() const;
    bool getShinyCharm() const;

};

#endif // PROFILE_HPP
