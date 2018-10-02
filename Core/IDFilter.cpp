#include "IDFilter.hpp"

IDFilter::IDFilter(QString idList, QString tsvList, int filterType)
{
    this->filterType = filterType;
    checkID = !idList.isEmpty();
    checkTSV = !tsvList.isEmpty();

    if (!idList.isEmpty())
    {
        for (QString in : idList.split("\n"))
        {
            if (filterType == 0 || filterType == 1) // TID or SID
            {
                tidFilter.append(filterType == 0 ? in.toUInt() : 0);
                sidFilter.append(filterType == 0 ? 0 : in.toUInt());
            }
            else if (filterType == 2) // TID/SID
            {
                QStringList split = in.split("/");
                tidFilter.append(split[0].toUInt());
                sidFilter.append(split[1].toUInt());
            }
            else // G7 TID
            {
                tidFilter.append(in.toUInt());
                sidFilter.append(0);
            }
        }
    }

    if (!tsvList.isEmpty())
    {
        for (QString in : tsvList.split("\n"))
        {
            tsvFilter.append(in.toUInt());
        }
    }
}

bool IDFilter::compare(IDModel frame)
{
    if (checkID)
    {
        if (filterType == 0) // TID
        {
            if (!tidFilter.contains(frame.getTID()))
                return false;
        }
        else if (filterType == 1) // SID
        {
            if (!sidFilter.contains(frame.getSID()))
                return false;
        }
        else if (filterType == 2) // TID/SID
        {
            if (!tidFilter.contains(frame.getTID()) || !sidFilter.contains(frame.getSID()))
                return false;
        }
        else // G7 TID
        {
            if (!tidFilter.contains(frame.getDisplayTID()))
                return false;
        }
    }

    if (checkTSV)
    {
        if (!tsvFilter.contains(frame.getTSV()))
            return false;
    }

    return true;
}
