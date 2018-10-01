#include "IDSearcher.hpp"

IDSearcher::IDSearcher(QDateTime start, QDateTime end, u32 startFrame, u32 endFrame, u32 tick, QVector<QPair<u32, u32>> idFilter, QVector<u32> tsvFilter, int filterType)
{
    startTime = start;
    endTime = end;
    this->startFrame = startFrame;
    this->endFrame = endFrame;
    this->tick = tick;
    this->idFilter = idFilter;
    this->tsvFilter = tsvFilter;
    this->filterType = filterType;
    cancel = false;
    progress = 0;
}

void IDSearcher::run()
{
    u64 epochStart = Utility::getCitraTime(startTime);
    u64 epochEnd = Utility::getCitraTime(endTime);

    for (u64 epoch = epochStart; epoch <= epochEnd; epoch += 60000)
    {
        u32 values[4] = { tick, 0, static_cast<u32>(epoch & 0xffffffff), static_cast<u32>(epoch >> 32)};

        u32 initialSeed = Utility::calcInitialSeed(values);
        SFMT sfmt(initialSeed);
        sfmt.advanceFrames(startFrame);

        QVector<IDModel> results;
        for (u32 frame = startFrame; frame <= endFrame; frame++)
        {
            if (cancel)
                return;

            u32 seed = sfmt.nextULong() & 0xffffffff;
            IDModel id(frame, seed);

            if (!idFilter.isEmpty())
            {
                QPair<u32, u32> tmp;
                if (filterType == 0)
                {
                    tmp.first = id.getTID();
                    tmp.second = 0;
                }
                else if (filterType == 1)
                {
                    tmp.first = id.getSID();
                    tmp.second = 0;
                }
                else if (filterType == 2)
                {
                    tmp.first = id.getTID();
                    tmp.second = id.getSID();
                }
                else
                {
                    tmp.first = id.getDisplayTID();
                    tmp.second = 0;
                }

                if (!idFilter.contains(tmp))
                    continue;
            }

            if (!tsvFilter.isEmpty())
            {
                if (!tsvFilter.contains(id.getTSV()))
                    continue;
            }

            QDateTime target = QDateTime::fromMSecsSinceEpoch(static_cast<qlonglong>(Utility::getNormalTime(epoch)), Qt::UTC);
            id.setStart(target);
            results.append(id);
        }
        if (!results.isEmpty())
            emit resultReady(results);
        emit updateProgress(++progress);
    }
}

int IDSearcher::maxProgress()
{
    int val = static_cast<int>((Utility::getCitraTime(endTime) - Utility::getCitraTime(startTime)) / 60000);
    return val;
}

void IDSearcher::cancelSearch()
{
    cancel = true;
}
