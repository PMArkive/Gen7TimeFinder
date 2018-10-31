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

#include "StationarySearcher.hpp"

StationarySearcher::StationarySearcher(QDateTime start, QDateTime end, u32 startFrame, u32 endFrame, bool ivCount, int ability, int synchNature,
                                       int gender, bool alwaysSynch, bool shinyLocked, const Profile &profile, StationaryFilter filter)
{
    startTime = std::move(start);
    endTime = std::move(end);
    this->startFrame = startFrame;
    this->endFrame = endFrame;
    this->ivCount = ivCount ? 3 : 0;
    this->ability = ability;
    this->synchNature = synchNature;
    this->gender = gender;
    this->alwaysSynch = alwaysSynch;
    this->shinyLocked = shinyLocked;
    this->profile = profile;
    this->filter = std::move(filter);

    pidCount = profile.getShinyCharm() ? 3 : 1;
    cancel = false;
    progress = 0;

    connect(this, &StationarySearcher::finished, this, &QObject::deleteLater);
}

StationarySearcher::~StationarySearcher()
{
    delete[] seeds;
}

void StationarySearcher::run()
{
    u64 epochStart = Utility::getCitraTime(startTime, profile.getOffset());
    u64 epochEnd = Utility::getCitraTime(endTime, profile.getOffset());
    seeds = new u64[endFrame - startFrame + 50];

    for (u64 epoch = epochStart; epoch <= epochEnd; epoch += 1000)
    {
        if (cancel)
            return;

        u32 initialSeed = Utility::calcInitialSeed(profile.getTick(), epoch);
        SFMT sfmt(initialSeed);
        sfmt.advanceFrames(startFrame);

        for (u32 i = 0; i < endFrame - startFrame + 50; i++)
            seeds[i] = sfmt.nextULong();

        for (u32 frame = 0; frame <= (endFrame - startFrame); frame++)
        {
            StationaryResult result(initialSeed, profile.getTID(), profile.getSID());
            u32 index = 0;

            // TODO
            /*
            //Synchronize
            if (alwaysSynch)
                result.setSynch(true);
            else
            {
                rt.Synchronize = blink_process();
                Advance(60);
            }*/

            result.setEC(seeds[frame + index++] & 0xffffffff);

            for (int i = pidCount; i > 0; i--)
            {
                result.setPID(seeds[frame + index++] & 0xffffffff);
                if (result.getShiny())
                {
                    if (shinyLocked)
                        result.setPID(result.getPID() ^ 0x10000000);
                    break;
                }
                // Handle eventually ???
                /*else if (IsForcedShiny)
                {
                    rt.Shiny = true;
                    rt.PID = (uint)((((TSV << 4) ^ (rt.PID & 0xFFFF)) << 16) + (rt.PID & 0xFFFF)); // Not accurate
                }*/
            }

            for (int i = ivCount; i > 0;)
            {
                int tmp = seeds[frame + index++] % 6;
                if (result.getIV(tmp) == -1)
                {
                    result.setIV(tmp, 31);
                    i--;
                }
            }

            for (int i = 0; i < 6; i++)
                if (result.getIV(i) == -1)
                    result.setIV(i, seeds[frame + index++] & 0x1f);

            result.calcHiddenPower();

            result.setAbility(ability == -1 ? ((seeds[frame + index++] & 1) + 1) : ability);

            result.setNature(alwaysSynch ? synchNature : seeds[frame + index++] % 25);

            result.setGender(gender > 2 ? (seeds[frame + index++] % 252 >= gender ? 1 : 2) : gender);

            if (filter.compare(result))
            {
                QDateTime target = QDateTime::fromMSecsSinceEpoch(static_cast<qlonglong>(Utility::getNormalTime(epoch, profile.getOffset())), Qt::UTC);
                result.setTarget(target);
                result.setFrame(frame + startFrame);

                mutex.lock();
                results.append(result);
                mutex.unlock();
            }
        }

        progress++;
    }
}

int StationarySearcher::maxProgress()
{
    auto val = static_cast<int>((Utility::getCitraTime(endTime, profile.getOffset()) - Utility::getCitraTime(startTime, profile.getOffset())) / 1000);
    return val + 1;
}

int StationarySearcher::currentProgress()
{
    return progress;
}

QVector<StationaryResult> StationarySearcher::getResults()
{
    mutex.lock();
    auto data(results);
    results.clear();
    mutex.unlock();

    return data;
}

void StationarySearcher::cancelSearch()
{
    cancel = true;
}
