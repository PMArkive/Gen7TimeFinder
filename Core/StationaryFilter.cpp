#include "StationaryFilter.hpp"

StationaryFilter::StationaryFilter(QVector<int> minIV, QVector<int> maxIV, u8 nature)
{
    this->minIV = minIV;
    this->maxIV = maxIV;
    this->nature = nature;
}

bool StationaryFilter::compare(StationaryModel frame)
{
    for (int i = 0; i < 6; i++)
    {
        int iv = frame.getIV(i);
        if (iv < minIV[i] || iv > maxIV[i])
            return false;
    }

    return true;
}
