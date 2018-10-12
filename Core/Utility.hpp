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
#include <Models/Profile.hpp>

typedef uint64_t u64;
typedef uint32_t u32;

namespace Utility
{
    u32 changeEndian(u32 num);
    u64 getCitraTime(QDateTime dateTime, u64 offset);
    u64 getNormalTime(u64 time, u64 offset);
    u32 calcInitialSeed(u32 *values);
    QString getNature(int nature);
    QString getHiddenPower(int hiddenPower);
    QVector<Profile> loadProfileList();
    void saveProfile(Profile profile);
    void deleteProfile(Profile profile);
    void updateProfile(Profile original, Profile edit);
    QStringList getNatures();
    QStringList getHiddenPowers();
    QStringList getGenderRatios();

}

#endif // UTILITY_HPP
