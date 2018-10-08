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
    Profile profile;
    StationaryFilter filter;
    QDateTime startTime, endTime;
    u32 startFrame, endFrame;
    int progress;
    bool cancel;

    int ivCount, ability, synchNature, pidCount, gender;
    bool alwaysSynch, shinyLocked;

public:
    StationarySearcher(QDateTime start, QDateTime end, u32 startFrame, u32 endFrame, bool ivCount, int ability, int synchNature,
                       int gender, bool alwaysSynch, bool shinyLocked, Profile profile, StationaryFilter filter);
    void run();
    int maxProgress();

public slots:
    void cancelSearch();

};

#endif // STATIONARYSEARCHER_HPP
