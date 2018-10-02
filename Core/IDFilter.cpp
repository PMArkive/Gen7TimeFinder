#include "IDFilter.hpp"

IDFilter::IDFilter(QVector<QPair<u32, u32>> idFilter, QVector<u32> tsvFilter, int filterType)
{
    this->idFilter = idFilter;
    this->tsvFilter = tsvFilter;
    this->filterType = filterType;
    checkID = !idFilter.isEmpty();
    checkTSV = !tsvFilter.isEmpty();
}

bool IDFilter::compare(IDModel frame)
{
    if (checkID)
    {
        QPair<u32, u32> tmp;
        if (filterType == 0)
        {
            tmp.first = frame.getTID();
            tmp.second = 0;
        }
        else if (filterType == 1)
        {
            tmp.first = frame.getSID();
            tmp.second = 0;
        }
        else if (filterType == 2)
        {
            tmp.first = frame.getTID();
            tmp.second = frame.getSID();
        }
        else
        {
            tmp.first = frame.getDisplayTID();
            tmp.second = 0;
        }

        if (!idFilter.contains(tmp))
            return false;
    }

    if (checkTSV)
    {
        if (!tsvFilter.contains(frame.getTSV()))
            return false;
    }

    return true;
}
