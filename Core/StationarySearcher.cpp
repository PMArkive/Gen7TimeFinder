#include "StationarySearcher.hpp"

StationarySearcher::StationarySearcher(QDateTime start, QDateTime end, u32 startFrame, u32 endFrame, u32 tick)
{
    startTime = start;
    endTime = end;
    this->startFrame = startFrame;
    this->endFrame = endFrame;
    this->tick = tick;
    cancel = false;
    progress = 0;
}

void StationarySearcher::run()
{
    u64 epochStart = Utility::getCitraTime(startTime);
    u64 epochEnd = Utility::getCitraTime(endTime);

    for (u64 epoch = epochStart; epoch <= epochEnd; epoch += 60000)
    {
        u32 values[4] = { tick, 0, static_cast<u32>(epoch & 0xffffffff), static_cast<u32>(epoch >> 32)};

        u32 initialSeed = Utility::calcInitialSeed(values);
        SFMT sfmt(initialSeed);
        sfmt.advanceFrames(startFrame);

        QVector<StationaryModel> results;
        for (u32 frame = startFrame; frame <= endFrame; frame++)
        {
            if (cancel)
                return;

            StationaryModel result(0);

            /*
            //Synchronize
            if (alwaysSynch)
                result.setSynch(true);
            else
            {
                rt.Synchronize = blink_process();
                Advance(60);
            }

            //Encryption Constant
            rt.EC = (uint)getrand;


            //PID
            for (int i = PIDroll_count; i > 0; i--)
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
            }

            //IV
            for (int i = PerfectIVCount; i > 0;)
            {
                int tmp = (int)(getrand % 6);
                if (rt.IVs[tmp] < 0)
                {
                    i--; rt.IVs[tmp] = 31;
                }
            }
            for (int i = 0; i < 6; i++)
                if (rt.IVs[i] < 0)
                    rt.IVs[i] = (int)(getrand & 0x1F);

            //Ability
            rt.Ability = Ability > 0 ? Ability : (byte)((getrand & 1) + 1);

            //Nature
            rt.Nature = rt.Synchronize && Synchro_Stat < 25 ? Synchro_Stat : (byte)(getrand % 25);

            //Gender
            rt.Gender = RandomGender ? (byte)(getrand % 252 >= Gender ? 1 : 2) : Gender;
            */

            results.append(result);
        }

        if (!results.isEmpty())
            emit resultReady(results);
        emit updateProgress(++progress);
    }
}

int StationarySearcher::maxProgress()
{
    int val = static_cast<int>((Utility::getCitraTime(endTime) - Utility::getCitraTime(startTime)) / 60000);
    return val;
}

void StationarySearcher::cancelSearch()
{
    cancel = true;
}
