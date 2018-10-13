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

#ifndef IDRESULT_HPP
#define IDRESULT_HPP

#include <QDateTime>
#include <QString>
#include <cstdint>

using u32 = uint32_t;
using u16 = uint16_t;

class IDResult
{

private:
    QDateTime target;
    u32 seed{}, frame{};
    u16 tid{};
    u16 sid{};
    u16 tsv{};
    u32 displayTID{};

public:
    IDResult(u32 seed, u32 frame, u32 rand);
    IDResult() = default;
    QString getDateTime() const;
    u32 getSeed() const;
    u32 getFrame() const;
    u16 getTID() const;
    u16 getSID() const;
    u16 getTSV() const;
    u32 getDisplayTID() const;
    void setTarget(const QDateTime &value);

};

#endif // IDRESULT_HPP
