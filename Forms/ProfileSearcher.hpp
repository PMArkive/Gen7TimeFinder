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

#ifndef PROFILESEARCHER_HPP
#define PROFILESEARCHER_HPP

#include <QMainWindow>
#include <QDateTime>
#include <QThread>
#include <QList>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QPair>
#include <Core/Utility.hpp>

namespace Ui
{
    class ProfileSearcher;
}

class ProfileSearch;

class ProfileSearcher : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProfileSearcher(QWidget *parent = nullptr);
    ~ProfileSearcher();

private slots:
    void on_pushButtonSearch_clicked();
    void addResult(QPair<u32, u32> result);
    void updateProgressBar(int num);
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::ProfileSearcher *ui;
    QStandardItemModel *model;

};

class ProfileSearch : public QThread
{
    Q_OBJECT

signals:
    void resultReady(QPair<u32, u32> result);
    void updateProgress(int val);

private:
    bool cancel;
    QDateTime startDate;
    u32 initialSeed;
    u32 baseTick, baseOffset;
    u32 tickRange, offsetRange;
    int progress;

public:
    ProfileSearch(QDateTime start, u32 initialSeed, u32 baseTick, u32 baseOffset, u32 tickRange, u32 offsetRange);
    void run();
    int maxProgress();

public slots:
    void cancelSearch();

};

#endif // PROFILESEARCHER_HPP
