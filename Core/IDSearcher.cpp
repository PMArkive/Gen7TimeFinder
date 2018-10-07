#include "IDSearcher.hpp"

IDSearcher::IDSearcher(QDateTime start, QDateTime end, u32 startFrame, u32 endFrame, Profile profile, IDFilter filter)
{
    startTime = start;
    endTime = end;
    this->startFrame = startFrame;
    this->endFrame = endFrame;
    this->profile = profile;
    this->filter = filter;
    cancel = false;
    progress = 0;
}

void IDSearcher::run()
{
    u64 epochStart = Utility::getCitraTime(startTime, profile.getOffset());
    u64 epochEnd = Utility::getCitraTime(endTime, profile.getOffset());

    for (u64 epoch = epochStart; epoch <= epochEnd; epoch += 60000)
    {
        // TODO change to also work for sm
        u32 values[4] = { 0x383e329, 0, static_cast<u32>(epoch & 0xffffffff), static_cast<u32>(epoch >> 32)};

        u32 initialSeed = Utility::calcInitialSeed(values);
        SFMT sfmt(initialSeed);
        sfmt.advanceFrames(startFrame);

        QVector<IDModel> results;
        for (u32 frame = startFrame; frame <= endFrame; frame++)
        {
            if (cancel)
                return;

            IDModel id(initialSeed, frame, sfmt.nextULong() & 0xffffffff);
            if (filter.compare(id))
            {
                QDateTime target = QDateTime::fromMSecsSinceEpoch(static_cast<qlonglong>(Utility::getNormalTime(epoch, profile.getOffset())), Qt::UTC);
                id.setTarget(target);
                results.append(id);
            }
        }

        if (!results.isEmpty())
            emit resultReady(results);
        emit updateProgress(++progress);
    }
}

int IDSearcher::maxProgress()
{
    int val = static_cast<int>((Utility::getCitraTime(endTime, profile.getOffset()) - Utility::getCitraTime(startTime, profile.getOffset())) / 60000);
    return val;
}

void IDSearcher::cancelSearch()
{
    cancel = true;
}
