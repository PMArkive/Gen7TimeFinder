#include "StationaryFilter.hpp"

StationaryFilter::StationaryFilter(QVector<int> minIV, QVector<int> maxIV, int nature, int hiddenPower, int ability, bool shiny, int gender)
{
    this->minIV = minIV;
    this->maxIV = maxIV;
    this->nature = nature;
    this->hiddenPower = hiddenPower;
    this->ability = ability;
    this->shiny = shiny;
    this->gender = gender;
}

bool StationaryFilter::compare(StationaryModel frame)
{
    for (int i = 0; i < 6; i++)
    {
        int iv = frame.getIV(i);
        if (iv < minIV[i] || iv > maxIV[i])
            return false;
    }

    if (nature != -1)
    {
        if (nature != frame.getNature())
            return false;
    }

    if (hiddenPower != -1)
    {
        if (hiddenPower != frame.getHiddenPower())
            return false;
    }

    if (ability != -1)
    {
        if (ability != frame.getAbility())
            return false;
    }

    if (shiny)
    {
        if (!frame.getShiny())
            return false;
    }

    if (gender != 0)
    {
        if (gender != frame.getGender() && frame.getGender() != 0)
            return false;
    }

    return true;
}
