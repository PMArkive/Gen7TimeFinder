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

#include "Utility.hpp"

u32 Utility::changeEndian(u32 num)
{
    return ((num >> 24) & 0xff) |
           ((num << 8) & 0xff0000) |
           ((num >> 8) & 0xff00) |
           ((num << 24) & 0xff000000);
}

u64 Utility::getCitraTime(const QDateTime &dateTime, u64 offset)
{
    return static_cast<u64>(dateTime.toMSecsSinceEpoch()) + offset - 946684800000;
}

u64 Utility::getNormalTime(u64 time, u64 offset)
{
    return time + 946684800000 - offset;
}

u32 Utility::calcInitialSeed(u32 tick, u64 epoch)
{
    u32 values[4] = { tick, 0, static_cast<u32>(epoch & 0xffffffff), static_cast<u32>(epoch >> 32) };
    QByteArray input;
    for (u32 &value : values)
    {
        u32 val = changeEndian(value);
        input.append(static_cast<char>(val >> 24));
        input.append(static_cast<char>((val >> 16) & 0xff));
        input.append(static_cast<char>((val >> 8) & 0xff));
        input.append(static_cast<char>(val & 0xff));
    }

    u32 seed = QCryptographicHash::hash(input, QCryptographicHash::Sha256).toHex().left(8).toUInt(nullptr, 16);
    return changeEndian(seed);
}

QString Utility::getNature(int nature)
{
    const QStringList natures = { "Hardy", "Lonely", "Brave", "Adamant",
                                  "Naughty", "Bold", "Docile", "Relaxed",
                                  "Impish", "Lax", "Timid", "Hasty",
                                  "Serious", "Jolly", "Naive", "Modest",
                                  "Mild", "Quiet", "Bashful", "Rash",
                                  "Calm", "Gentle", "Sassy", "Careful",
                                  "Quirky"
                                };
    return natures[nature];
}

QString Utility::getHiddenPower(int hiddenPower)
{
    const QStringList hiddenPowers = { "Fighting", "Flying", "Poison", "Ground",
                                       "Rock", "Bug", "Ghost", "Steel",
                                       "Fire", "Water", "Grass", "Electric",
                                       "Psychic", "Ice", "Dragon", "Dark"
                                     };
    return hiddenPowers[hiddenPower];
}

QVector<Profile> Utility::loadProfileList()
{
    QVector<Profile> profileList;

    QFile file(QApplication::applicationDirPath() + "/profiles.json");
    if (file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QJsonDocument profiles(QJsonDocument::fromJson(file.readAll()));
        QJsonArray gen7 = profiles["gen7"].toArray();

        for (const auto &&i : gen7)
        {
            auto profile = i.toObject();
            profileList.append(Profile(profile["name"].toString(), profile["offset"].toString().toUInt(), profile["tick"].toString().toUInt(),
                                       profile["tid"].toInt(),  profile["sid"].toInt(), static_cast<Game>(profile["version"].toInt()), profile["charm"].toBool()));
        }
        file.close();
    }

    return profileList;
}

void Utility::saveProfile(const Profile &profile)
{
    QFile file(QApplication::applicationDirPath() + "/profiles.json");
    if (file.open(QIODevice::ReadWrite | QFile::Text))
    {
        QJsonObject profiles(QJsonDocument::fromJson(file.readAll()).object());
        QJsonArray gen7 = profiles["gen7"].toArray();

        gen7.append(getJson(profile));
        profiles["gen7"] = gen7;

        file.resize(0);
        file.write(QJsonDocument(profiles).toJson());
        file.close();
    }
}

void Utility::deleteProfile(const Profile &profile)
{
    QFile file(QApplication::applicationDirPath() + "/profiles.json");
    if (file.open(QIODevice::ReadWrite | QFile::Text))
    {
        QJsonObject profiles(QJsonDocument::fromJson(file.readAll()).object());
        QJsonArray gen7 = profiles["gen7"].toArray();

        for (int i = 0; i < gen7.size(); i++)
        {
            Profile old(gen7[i].toObject());

            if (profile.getName() == old.getName() && profile.getOffset() == old.getOffset() && profile.getTick() == old.getTick() &&
                    profile.getTID() == old.getTID() && profile.getSID() == old.getSID() &&
                    profile.getVersion() == old.getVersion() && profile.getShinyCharm() == old.getShinyCharm())
            {
                gen7.removeAt(i);
                profiles["gen7"] = gen7;

                file.resize(0);
                file.write(QJsonDocument(profiles).toJson());
                break;
            }
        }
        file.close();
    }
}

void Utility::updateProfile(const Profile &original, const Profile &edit)
{
    QFile file(QApplication::applicationDirPath() + "/profiles.json");
    if (file.open(QIODevice::ReadWrite | QFile::Text))
    {
        QJsonObject profiles(QJsonDocument::fromJson(file.readAll()).object());
        QJsonArray gen7 = profiles["gen7"].toArray();

        for (auto &&i : gen7)
        {
            Profile old(i.toObject());

            if (original.getName() == old.getName() && original.getOffset() == old.getOffset() && original.getTick() == old.getTick() &&
                    original.getTID() == old.getTID() && original.getSID() == old.getSID() &&
                    original.getVersion() == old.getVersion() && original.getShinyCharm() == old.getShinyCharm())
            {
                i = getJson(edit);
                profiles["gen7"] = gen7;

                file.resize(0);
                file.write(QJsonDocument(profiles).toJson());
                break;
            }
        }
        file.close();
    }
}

QJsonObject Utility::getJson(const Profile &profile)
{
    QJsonObject data;
    data["name"] = profile.getName();
    data["offset"] = QString::number(profile.getOffset());
    data["tick"] = QString::number(profile.getTick());
    data["tid"] = profile.getTID();
    data["sid"] = profile.getSID();
    data["version"] = profile.getVersion();
    data["charm"] = profile.getShinyCharm();
    return data;
}


QStringList Utility::getNatures()
{
    QStringList natures = { "None", "Hardy", "Lonely", "Brave", "Adamant",
                            "Naughty", "Bold", "Docile", "Relaxed", "Impish",
                            "Lax", "Timid", "Hasty", "Serious", "Jolly",
                            "Naive", "Modest", "Mild", "Quiet", "Bashful",
                            "Rash", "Calm", "Gentle", "Sassy", "Careful", "Quirky"
                          };
    return natures;
}

QStringList Utility::getHiddenPowers()
{
    QStringList hiddenPowers = { "None", "Fighting", "Flying", "Poison",
                                 "Ground", "Rock", "Bug", "Ghost",
                                 "Steel", "Fire", "Water", "Grass",
                                 "Electric", "Psychic", "Ice", "Dragon", "Dark"
                               };
    return hiddenPowers;
}

QStringList Utility::getGenderRatios()
{
    QStringList genderRatios = { "Genderless", "♂1 : ♀1", "♂7 : ♀1", "♂3 : ♀1",
                                 "♂1 : ♀3", "♂1 : ♀7", "♂ Only", "♀ Only"
                               };
    return genderRatios;
}
