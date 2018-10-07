#ifndef STATIONARYFILTER_HPP
#define STATIONARYFILTER_HPP

#include <QVector>
#include <Models/StationaryModel.hpp>

class StationaryFilter
{

private:
    QVector<int> minIV;
    QVector<int> maxIV;
    u8 nature;

public:
    StationaryFilter() {}
    StationaryFilter(QVector<int> minIV, QVector<int> maxIV, u8 nature);
    bool compare(StationaryModel frame);

};

#endif // STATIONARYFILTER_HPP
