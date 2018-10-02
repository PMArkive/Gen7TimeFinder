#ifndef IDSEARCHER_HPP
#define IDSEARCHER_HPP

#include <QThread>
#include <QVector>
#include <QPair>
#include <Core/Utility.hpp>
#include <Core/SFMT.hpp>
#include <Core/IDFilter.hpp>
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
    int progress;
    IDFilter compare;

public:
    IDSearcher(QDateTime start, QDateTime end, u32 startFrame, u32 endFrame, u32 tick, IDFilter compare);
    void run();
    int maxProgress();

public slots:
    void cancelSearch();

};

#endif // IDSEARCHER_HPP
