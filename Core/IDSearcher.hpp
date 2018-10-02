#ifndef IDSEARCHER_HPP
#define IDSEARCHER_HPP

#include <QThread>
#include <QVector>
#include <QPair>
#include <Core/Utility.hpp>
#include <Core/SFMT.hpp>
#include <Models/IDModel.hpp>

class IDSearcher : public QThread
{
    Q_OBJECT

signals:
    void resultReady(QVector<IDModel> frames);
    void updateProgress(int val);

private:
    bool cancel;
    QDateTime startTime, endTime;
    u32 startFrame, endFrame, tick;
    int filterType, progress;
    QVector<QPair<u32, u32>> idFilter;
    QVector<u32> tsvFilter;

public:
    IDSearcher(QDateTime start, QDateTime end, u32 startFrame, u32 endFrame, u32 tick, QVector<QPair<u32, u32>> idFilter, QVector<u32> tsvFilter, int filterType);
    void run();
    int maxProgress();

public slots:
    void cancelSearch();

};

#endif // IDSEARCHER_HPP
