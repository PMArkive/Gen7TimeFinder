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

#ifndef IDSEARCHER_HPP
#define IDSEARCHER_HPP

#include <QMutex>
#include <QThread>
#include <QVector>
#include <Core/IDFilter.hpp>
#include <Core/SFMT.hpp>
#include <Core/Utility.hpp>
#include <Results/IDResult.hpp>
#include <Results/Profile.hpp>

class IDSearcher : public QThread
{
    Q_OBJECT

private:
    bool cancel;
    QDateTime startTime, endTime;
    u32 startFrame, endFrame;
    int progress;
    IDFilter filter;
    Profile profile;

    QVector<IDResult> results;
    QMutex mutex;

public:
    IDSearcher(QDateTime start, QDateTime end, u32 startFrame, u32 endFrame, Profile profile, IDFilter filter);
    void run() override;
    int maxProgress();
    int currentProgress();
    QVector<IDResult> getResults();

public slots:
    void cancelSearch();

};

#endif // IDSEARCHER_HPP
