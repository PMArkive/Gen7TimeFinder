#ifndef IDSEARCHER_HPP
#define IDSEARCHER_HPP

#include <QThread>
#include <QVector>
#include <QPair>
#include <Core/IDFilter.hpp>
#include <Core/SFMT.hpp>
#include <Core/Utility.hpp>
#include <Models/IDModel.hpp>
#include <Models/Profile.hpp>

class IDSearcher : public QThread
{
    Q_OBJECT

signals:
    void resultReady(QVector<IDModel> frames);
    void updateProgress(int val);

private:
    bool cancel;
    QDateTime startTime, endTime;
    u32 startFrame, endFrame;
    int progress;
    IDFilter filter;
    Profile profile;

public:
    IDSearcher(QDateTime start, QDateTime end, u32 startFrame, u32 endFrame, Profile profile, IDFilter filter);
    void run();
    int maxProgress();

public slots:
    void cancelSearch();

};

#endif // IDSEARCHER_HPP
