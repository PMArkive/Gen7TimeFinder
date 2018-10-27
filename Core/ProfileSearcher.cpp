#include "ProfileSearcher.hpp"

ProfileSearcher::ProfileSearcher(QDateTime start, u32 initialSeed, u32 baseTick, u32 baseOffset, u32 tickRange, u32 offsetRange)
{
    startDate = std::move(start);
    this->initialSeed = initialSeed;
    this->baseTick = baseTick;
    this->baseOffset = baseOffset;
    this->tickRange = tickRange;
    this->offsetRange = offsetRange;
    progress = 0;
    cancel = false;

    connect(this, &ProfileSearcher::finished, this, &QObject::deleteLater);
}

void ProfileSearcher::run()
{
    for (u32 tick = 0; tick <= tickRange; tick++)
    {
        for (u32 offset = 0; offset <= offsetRange; offset++)
        {
            if (cancel)
                return;

            // Plus offset
            u64 epochPlus = Utility::getCitraTime(startDate, baseOffset + offset);
            u32 seedPlus = Utility::calcInitialSeed(baseTick + tick, epochPlus);
            if (seedPlus == initialSeed)
            {
                mutex.lock();
                results.append(QPair<u32, u32>(baseTick + tick, baseOffset + offset));
                mutex.unlock();
            }

            // Minus offset
            u64 epochMinus = Utility::getCitraTime(startDate, baseOffset - offset);
            u32 seedMinus = Utility::calcInitialSeed(baseTick - tick, epochMinus);
            if (seedMinus == initialSeed)
            {
                mutex.lock();
                results.append(QPair<u32, u32>(baseTick - tick, baseOffset - offset));
                mutex.unlock();
            }
        }
        progress++;
    }
}

int ProfileSearcher::maxProgress()
{
    return static_cast<int>(tickRange + 1);
}

int ProfileSearcher::currentProgress()
{
    return progress;
}

QVector<QPair<u32, u32>> ProfileSearcher::getResults()
{
    mutex.lock();
    auto data(results);
    results.clear();
    mutex.unlock();

    return data;
}

void ProfileSearcher::cancelSearch()
{
    cancel = true;
}
