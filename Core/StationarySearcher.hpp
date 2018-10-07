#ifndef STATIONARYSEARCHER_HPP
#define STATIONARYSEARCHER_HPP

#include <QThread>
#include <QVector>
#include <Core/SFMT.hpp>
#include <Core/StationaryFilter.hpp>
#include <Core/Utility.hpp>
#include <Models/StationaryModel.hpp>
#include <Models/Profile.hpp>

typedef uint64_t u64;

class StationarySearcher : public QThread
{
    Q_OBJECT

signals:
    void resultReady(QVector<StationaryModel> frames);
    void updateProgress(int val);

private:
    bool cancel, alwaysSynch;
    QDateTime startTime, endTime;
    u32 startFrame, endFrame;
    int progress, ivCount;
    Profile profile;
    StationaryFilter filter;

public:
    StationarySearcher(QDateTime start, QDateTime end, u32 startFrame, u32 endFrame, Profile profile, int ivCount, StationaryFilter filter);
    void run();
    int maxProgress();

public slots:
    void cancelSearch();

};

#endif // STATIONARYSEARCHER_HPP
