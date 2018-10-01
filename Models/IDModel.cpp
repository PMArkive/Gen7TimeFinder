#include "IDModel.hpp"

IDModel::IDModel(u32 frame, u32 rand)
{
    this->frame = frame;
    this->start = start;
    tid = rand & 0xffff;
    sid = rand >> 16;
    tsv = (tid ^ sid) >> 4;
    displayTID = rand % 1000000;
}

QString IDModel::getDateTime()
{
    return start.toString();
}

u32 IDModel::getFrame() const
{
    return frame;
}

u16 IDModel::getTID() const
{
    return tid;
}

u16 IDModel::getSID() const
{
    return sid;
}

u16 IDModel::getTSV() const
{
    return tsv;
}

u32 IDModel::getDisplayTID() const
{
    return displayTID;
}

void IDModel::setStart(const QDateTime &value)
{
    start = value;
}
