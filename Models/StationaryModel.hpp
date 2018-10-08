#ifndef STATIONARYMODEL_HPP
#define STATIONARYMODEL_HPP

#include <QDateTime>
#include <cstdint>

typedef uint32_t u32;
typedef uint16_t u16;

class StationaryModel
{

private:
    QDateTime target;
    u32 seed, pid, ec, frame;
    u16 psv, tsv;
    int hiddenPower, ability, nature, gender;
    int ivs[6];
    bool shiny;
    bool synch;

public:
    StationaryModel() {}
    StationaryModel(u32 seed, u16 tid, u16 sid);
    QString getDateTime() const;
    void setTarget(const QDateTime &value);
    u32 getSeed() const;
    u32 getPID() const;
    void setPID(const u32 &value);
    u32 getEC() const;
    void setEC(const u32 &value);
    u32 getFrame() const;
    void setFrame(const u32 &value);
    u16 getPSV() const;
    int getHiddenPower() const;
    void calcHiddenPower();
    int getAbility() const;
    void setAbility(const int &value);
    int getNature() const;
    void setNature(const int &value);
    QString getGenderString() const;
    int getGender() const;
    void setGender(const int &value);
    int getIV(int i) const;
    void setIV(const int &i, const int &value);
    bool getShiny() const;
    void setShiny(bool value);
    bool getSynch() const;
    void setSynch(bool value);
};

#endif // STATIONARYMODEL_HPP
