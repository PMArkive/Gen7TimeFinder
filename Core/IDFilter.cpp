#include "IDFilter.hpp"

IDFilter::IDFilter(QString idList, QString tsvList, int filterType)
{
    this->filterType = static_cast<FilterType>(filterType);
    checkID = !idList.isEmpty();
    checkTSV = !tsvList.isEmpty();

    if (!idList.isEmpty())
    {
        for (QString in : idList.split("\n"))
        {
            switch (this->filterType)
            {
                case FilterType::TID:
                    tidFilter.append(in.toUInt());
                    sidFilter.append(0);
                    break;
                case FilterType::SID:
                    tidFilter.append(0);
                    sidFilter.append(in.toUInt());
                    break;
                case FilterType::TIDSID:
                    {
                        QStringList split = in.split("/");
                        tidFilter.append(split[0].toUInt());
                        sidFilter.append(split[1].toUInt());
                        break;
                    }
                case FilterType::G7TID:
                    tidFilter.append(in.toUInt());
                    sidFilter.append(0);
                    break;
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
        switch (filterType)
        {
            case FilterType::TID:
                if (!tidFilter.contains(frame.getTID()))
                    return false;
                break;
            case FilterType::SID:
                if (!sidFilter.contains(frame.getSID()))
                    return false;
                break;
            case FilterType::TIDSID:
                if (!tidFilter.contains(frame.getTID()) || !sidFilter.contains(frame.getSID()))
                    return false;
                break;
            case FilterType::G7TID:
                if (!tidFilter.contains(frame.getDisplayTID()))
                    return false;
                break;
        }
    }

    if (checkTSV)
    {
        if (!tsvFilter.contains(frame.getTSV()))
            return false;
    }

    return true;
}
