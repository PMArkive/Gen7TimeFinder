#ifndef IDFILTER_HPP
#define IDFILTER_HPP

#include <QVector>
#include <QPair>
#include <Models/IDModel.hpp>

class IDFilter
{

private:
    QVector<u32> tidFilter;
    QVector<u32> sidFilter;
    QVector<u32> tsvFilter;
    int filterType;
    bool checkID;
    bool checkTSV;

public:
    IDFilter() {}
    IDFilter(QString idList, QString tsvList, int filterType);
    bool compare(IDModel frame);

};

#endif // IDFILTER_HPP
