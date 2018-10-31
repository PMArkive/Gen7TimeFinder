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

#ifndef STATIONARYSEARCHER_HPP
#define STATIONARYSEARCHER_HPP

#include <QMutex>
#include <QThread>
#include <QVector>
#include <Core/SFMT.hpp>
#include <Core/StationaryFilter.hpp>
#include <Core/Utility.hpp>
#include <Results/StationaryResult.hpp>
#include <Results/Profile.hpp>

using u64 = uint64_t;

class StationarySearcher : public QThread
{
    Q_OBJECT

private:
    Profile profile;
    StationaryFilter filter;
    QDateTime startTime, endTime;
    u32 startFrame, endFrame;
    int progress;
    bool cancel;
    u64 *seeds;

    int ivCount, ability, synchNature, pidCount, gender;
    bool alwaysSynch, shinyLocked;

    QVector<StationaryResult> results;
    QMutex mutex;

public:
    StationarySearcher(QDateTime start, QDateTime end, u32 startFrame, u32 endFrame, bool ivCount, int ability, int synchNature,
                       int gender, bool alwaysSynch, bool shinyLocked, const Profile &profile, StationaryFilter filter);
    ~StationarySearcher() override;
    void run() override;
    int maxProgress();
    int currentProgress();
    QVector<StationaryResult> getResults();

public slots:
    void cancelSearch();

};

#endif // STATIONARYSEARCHER_HPP
