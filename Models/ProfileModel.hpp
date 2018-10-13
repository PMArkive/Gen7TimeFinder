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

#ifndef PROFILEMODEL_HPP
#define PROFILEMODEL_HPP

#include <QAbstractTableModel>
#include <QVector>
#include <Results/Profile.hpp>

class ProfileModel : public QAbstractTableModel
{

private:
    QVector<Profile> model;

public:
    ProfileModel(QObject *parent = nullptr);
    void setModel(const QVector<Profile> &profiles);
    void addItem(const Profile &profile);
    void updateProfile(Profile profile, int row);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Profile getProfile(int index);
    void removeProfile(int index);

};

#endif // PROFILEMODEL_HPP
