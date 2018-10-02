#ifndef STATIONARYSEARCHER_HPP
#define STATIONARYSEARCHER_HPP

#include <QThread>
#include <QVector>
#include <Core/Utility.hpp>
#include <Core/SFMT.hpp>
#include <Models/StationaryModel.hpp>

class StationarySearcher : public QThread
{
    Q_OBJECT

signals:
    void resultReady(QVector<StationaryModel> frames);
    void updateProgress(int val);

private:
    bool cancel, alwaysSynch;
    QDateTime startTime, endTime;
    u32 startFrame, endFrame, tick;
    int progress;

public:
    StationarySearcher(QDateTime start, QDateTime end, u32 startFrame, u32 endFrame, u32 tick);
    void run();
    int maxProgress();

public slots:
    void cancelSearch();

};

#endif // STATIONARYSEARCHER_HPP
