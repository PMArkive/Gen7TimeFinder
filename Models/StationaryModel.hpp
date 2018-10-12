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

#ifndef STATIONARYMODEL_HPP
#define STATIONARYMODEL_HPP

#include <QDateTime>
#include <cstdint>

typedef uint32_t u32;
typedef uint16_t u16;

class StationaryModel
{

private:
    QDateTime target;
    u32 seed, pid, ec, frame;
    u16 psv, tsv;
    int hiddenPower, ability, nature, gender;
    int ivs[6];
    bool shiny;
    bool synch;

public:
    StationaryModel() {}
    StationaryModel(u32 seed, u16 tid, u16 sid);
    QString getDateTime() const;
    void setTarget(const QDateTime &value);
    u32 getSeed() const;
    u32 getPID() const;
    void setPID(const u32 &value);
    u32 getEC() const;
    void setEC(const u32 &value);
    u32 getFrame() const;
    void setFrame(const u32 &value);
    u16 getPSV() const;
    int getHiddenPower() const;
    void calcHiddenPower();
    int getAbility() const;
    void setAbility(const int &value);
    int getNature() const;
    void setNature(const int &value);
    QString getGenderString() const;
    int getGender() const;
    void setGender(const int &value);
    int getIV(int i) const;
    void setIV(const int &i, const int &value);
    bool getShiny() const;
    void setShiny(bool value);
    bool getSynch() const;
    void setSynch(bool value);
};

#endif // STATIONARYMODEL_HPP
