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

StationaryModel::StationaryModel(QObject *parent) : QAbstractTableModel(parent)
{
}

void StationaryModel::addItems(const QVector<StationaryResult> &frames)
{
    int i = rowCount();
    emit beginInsertRows(QModelIndex(), i, i + frames.size() - 1);
    model.append(frames);
    emit endInsertRows();
}

void StationaryModel::clear()
{
    if (model.isEmpty())
        return;
    emit beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    model.clear();
    model.squeeze();
    emit endRemoveRows();
}

int StationaryModel::rowCount(const QModelIndex &parent) const
{
    (void) parent;
    return model.size();
}

int StationaryModel::columnCount(const QModelIndex &parent) const
{
    (void) parent;
    return 14;
}

QVariant StationaryModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        auto &frame = model.at(index.row());
        switch (index.column())
        {
            case 0:
                return frame.getDateTime();
            case 1:
                return QString::number(frame.getSeed(), 16).toUpper();
            case 2:
                return frame.getFrame();
            case 3:
                return frame.getIV(0);
            case 4:
                return frame.getIV(1);
            case 5:
                return frame.getIV(2);
            case 6:
                return frame.getIV(3);
            case 7:
                return frame.getIV(4);
            case 8:
                return frame.getIV(5);
            case 9:
                return Utility::getNature(frame.getNature());
            case 10:
                return Utility::getHiddenPower(frame.getHiddenPower());
            case 11:
                return frame.getPSV();
            case 12:
                return frame.getGenderString();
            case 13:
                return frame.getAbility();
        }
    }
    return QVariant();
}

QVariant StationaryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section)
        {
            case 0:
                return tr("Date/Time");
            case 1:
                return tr("Initial Seed");
            case 2:
                return tr("Frame");
            case 3:
                return tr("HP");
            case 4:
                return tr("Atk");
            case 5:
                return tr("Def");
            case 6:
                return tr("SpA");
            case 7:
                return tr("SpD");
            case 8:
                return tr("Spe");
            case 9:
                return tr("Nature");
            case 10:
                return tr("HP Type");
            case 11:
                return tr("PSV");
            case 12:
                return tr("Gender");
            case 13:
                return tr("Ability");
        }
    }
    return QVariant();
}
