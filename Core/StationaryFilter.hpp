#ifndef STATIONARYFILTER_HPP
#define STATIONARYFILTER_HPP

#include <QVector>
#include <Models/StationaryModel.hpp>

class StationaryFilter
{

private:
    QVector<int> minIV, maxIV;
    int nature, hiddenPower, ability, gender;
    bool shiny;

public:
    StationaryFilter() {}
    StationaryFilter(QVector<int> minIV, QVector<int> maxIV, int nature, int hiddenPower, int ability, bool shiny, int gender);
    bool compare(StationaryModel frame);

};

#endif // STATIONARYFILTER_HPP
