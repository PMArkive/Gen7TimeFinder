#include "StationarySearcher.hpp"

StationarySearcher::StationarySearcher(QDateTime start, QDateTime end, u32 startFrame, u32 endFrame, Profile profile, int ivCount, StationaryFilter filter)
{
    startTime = start;
    endTime = end;
    this->startFrame = startFrame;
    this->endFrame = endFrame;
    this->profile = profile;
    this->ivCount = ivCount;
    this->filter = filter;
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

            StationaryModel result(initialSeed);
            int index = 0;

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

            //Encryption Constant
            result.setEC(seeds[index++] & 0xffffffff);


            // TODO add pid roll count
            /*for (int i = PIDroll_count; i > 0; i--)
            {
                rt.PID = (uint)getrand;
                if (rt.PSV == TSV)
                {
                    if (IsShinyLocked)
                        rt.PID ^= 0x10000000;
                    else
                        rt.Shiny = true;
                    break;
                }
                else if (IsForcedShiny)
                {
                    rt.Shiny = true;
                    rt.PID = (uint)((((TSV << 4) ^ (rt.PID & 0xFFFF)) << 16) + (rt.PID & 0xFFFF)); // Not accurate
                }
            }*/
            result.setPID(seeds[index++] & 0xffffffff);

            //IV
            for (int i = ivCount; i > 0;)
            {
                int tmp = seeds[index++] % 6;
                if (result.getIV(tmp) == -1)
                {
                    result.setIV(tmp, 31);
                    i--;
                }
            }

            for (int i = 0; i < 6; i++)
                if (result.getIV(i) == -1)
                    result.setIV(i, seeds[index++] & 0x1f);

            //Ability
            result.setAbility((seeds[index++] & 1) + 1);
            //rt.Ability = Ability > 0 ? Ability : (byte)((getrand & 1) + 1);

            //Nature
            result.setNature(seeds[index++] % 25);

            // TODO Gender
            //rt.Gender = RandomGender ? (byte)(getrand % 252 >= Gender ? 1 : 2) : Gender;

            if (filter.compare(result))
            {
                QDateTime target = QDateTime::fromMSecsSinceEpoch(static_cast<qlonglong>(Utility::getNormalTime(epoch, profile.getOffset())), Qt::UTC);
                result.setTarget(target);
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
