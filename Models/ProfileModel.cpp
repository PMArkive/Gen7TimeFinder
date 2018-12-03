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

#include "ProfileModel.hpp"

ProfileModel::ProfileModel(QObject *parent) : QAbstractTableModel(parent)
{
}

void ProfileModel::setModel(const QVector<Profile> &profiles)
{
    if (profiles.isEmpty())
        return;
    int i = rowCount();
    emit beginInsertRows(QModelIndex(), i, i + profiles.size() - 1);
    model.append(profiles);
    emit endInsertRows();
}

void ProfileModel::addItem(const Profile &profile)
{
    int i = rowCount();
    emit beginInsertRows(QModelIndex(), i, i);
    model.push_back(profile);
    emit endInsertRows();
}

void ProfileModel::updateProfile(const Profile &profile, int row)
{
    model[row] = profile;
    emit dataChanged(index(row, 0), index(row, columnCount()));
}

int ProfileModel::rowCount(const QModelIndex &parent) const
{
    (void) parent;
    return model.size();
}

int ProfileModel::columnCount(const QModelIndex &parent) const
{
    (void) parent;
    return 7;
}

QVariant ProfileModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        auto &profile = model.at(index.row());
        switch (index.column())
        {
            case 0:
                return profile.getName();
            case 1:
                return profile.getVersionString();
            case 2:
                return profile.getTID();
            case 3:
                return profile.getSID();
            case 4:
                return profile.getShinyCharm() ? "Yes" : "No";
            case 5:
                return QString::number(profile.getTick(), 16);
            case 6:
                return profile.getOffset();
        }
    }
    return QVariant();
}

QVariant ProfileModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section)
        {
            case 0:
                return tr("Profile Name");
            case 1:
                return tr("Version");
            case 2:
                return tr("TID");
            case 3:
                return tr("SID");
            case 4:
                return tr("Shiny Charm");
            case 5:
                return tr("Tick");
            case 6:
                return tr("Offset");
        }
    }
    return QVariant();
}

Profile ProfileModel::getProfile(int index)
{
    return model[index];
}

void ProfileModel::removeProfile(int index)
{
    emit beginRemoveRows(QModelIndex(), index, index);
    model.erase(model.begin() + index);
    model.squeeze();
    emit endRemoveRows();
}
