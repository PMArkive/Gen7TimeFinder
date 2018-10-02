#ifndef IDFILTER_HPP
#define IDFILTER_HPP

#include <QVector>
#include <QPair>
#include <Models/IDModel.hpp>

class IDFilter
{

private:
    QVector<QPair<u32, u32>> idFilter;
    QVector<u32> tsvFilter;
    int filterType;
    bool checkID;
    bool checkTSV;

public:
    IDFilter() {}
    IDFilter(QVector<QPair<u32, u32>> idFilter, QVector<u32> tsvFilter, int filterType);
    bool compare(IDModel frame);

};

#endif // IDFILTER_HPP
