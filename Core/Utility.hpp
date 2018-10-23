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

#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <QCryptographicHash>
#include <QDateTime>
#include <QString>
#include <QDomDocument>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <cstdint>
#include <Results/Profile.hpp>

using u64 = uint64_t;
using u32 = uint32_t;

namespace Utility
{
    u32 changeEndian(u32 num);
    u64 getCitraTime(const QDateTime &dateTime, u64 offset);
    u64 getNormalTime(u64 time, u64 offset);
    u32 calcInitialSeed(u32 tick, u64 epoch);
    QString getNature(int nature);
    QString getHiddenPower(int hiddenPower);
    QVector<Profile> loadProfileList();
    void saveProfile(const Profile &profile);
    void deleteProfile(const Profile &profile);
    void updateProfile(const Profile &original, const Profile &edit);
    QStringList getNatures();
    QStringList getHiddenPowers();
    QStringList getGenderRatios();

}

#endif // UTILITY_HPP
