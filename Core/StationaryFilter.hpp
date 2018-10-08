#ifndef STATIONARYFILTER_HPP
#define STATIONARYFILTER_HPP

#include <QVector>
#include <Models/StationaryModel.hpp>

class StationaryFilter
{

private:
    QVector<int> minIV, maxIV;
    int nature, hiddenPower, ability;
    bool shiny;

public:
    StationaryFilter() {}
    StationaryFilter(QVector<int> minIV, QVector<int> maxIV, int nature, int hiddenPower, int ability, bool shiny);
    bool compare(StationaryModel frame);

};

#endif // STATIONARYFILTER_HPP
