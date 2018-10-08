#include "StationarySearcher.hpp"

StationarySearcher::StationarySearcher(QDateTime start, QDateTime end, u32 startFrame, u32 endFrame, bool ivCount, int ability, int synchNature,
                                       int gender, bool alwaysSynch, bool shinyLocked, Profile profile, StationaryFilter filter)
{
    startTime = start;
    endTime = end;
    this->startFrame = startFrame;
    this->endFrame = endFrame;
    this->ivCount = ivCount ? 3 : 0;
    this->ability = ability;
    this->synchNature = synchNature;
    this->gender = gender;
    this->alwaysSynch = alwaysSynch;
    this->shinyLocked = shinyLocked;
    this->profile = profile;
    this->filter = filter;

    pidCount = profile.getShinyCharm() ? 3 : 1;
    cancel = false;
    progress = 0;
}

void StationarySearcher::run()
{
    u64 epochStart = Utility::getCitraTime(startTime, profile.getOffset());
    u64 epochEnd = Utility::getCitraTime(endTime, profile.getOffset());

    for (u64 epoch = epochStart; epoch <= epochEnd; epoch += 60000)
    {
        // TODO change to also work for SM
        u32 values[4] = { 0x383e329, 0, static_cast<u32>(epoch & 0xffffffff), static_cast<u32>(epoch >> 32)};

        u32 initialSeed = Utility::calcInitialSeed(values);
        SFMT sfmt(initialSeed);
        sfmt.advanceFrames(startFrame);

        u64 *seeds = new u64[endFrame];
        for (u32 i = 0; i < endFrame; i++)
            seeds[i] = sfmt.nextULong();

        QVector<StationaryModel> results;
        for (u32 frame = 0; frame <= (endFrame - startFrame); frame++)
        {
            if (cancel)
                return;

            StationaryModel result(initialSeed, profile.getTID(), profile.getSID());
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
                results.append(result);
            }
        }

        delete[] seeds;

        if (!results.isEmpty())
            emit resultReady(results);
        emit updateProgress(++progress);
    }
}

int StationarySearcher::maxProgress()
{
    int val = static_cast<int>((Utility::getCitraTime(endTime, profile.getOffset()) - Utility::getCitraTime(startTime, profile.getOffset())) / 60000);
    return val;
}

void StationarySearcher::cancelSearch()
{
    cancel = true;
}
