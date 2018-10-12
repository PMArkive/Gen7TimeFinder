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

#include "IDView.hpp"

IDView::IDView(QObject *parent) : QAbstractTableModel(parent)
{
}

void IDView::addItems(QVector<IDModel> frames)
{
    int i = rowCount();
    emit beginInsertRows(QModelIndex(), i, i + frames.size() - 1);
    model.append(frames);
    emit endInsertRows();
}

void IDView::clear()
{
    if (model.empty())
        return;
    emit beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    model.clear();
    model.squeeze();
    emit endRemoveRows();
}

int IDView::rowCount(const QModelIndex &parent) const
{
    (void) parent;
    return model.size();
}

int IDView::columnCount(const QModelIndex &parent) const
{
    (void) parent;
    return 7;
}

QVariant IDView::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        IDModel frame = model[index.row()];
        switch (index.column())
        {
            case 0:
                return frame.getDateTime();
            case 1:
                return QString::number(frame.getSeed(), 16).toUpper();
            case 2:
                return frame.getFrame();
            case 3:
                return frame.getDisplayTID();
            case 4:
                return frame.getTID();
            case 5:
                return frame.getSID();
            case 6:
                return frame.getTSV();
        }
    }
    return QVariant();
}

QVariant IDView::headerData(int section, Qt::Orientation orientation, int role) const
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
                return tr("G7 TID");
            case 4:
                return tr("TID");
            case 5:
                return tr("SID");
            case 6:
                return tr("TSV");
        }
    }
    return QVariant();
}
