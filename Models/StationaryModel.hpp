#ifndef STATIONARYMODEL_HPP
#define STATIONARYMODEL_HPP

#include <QDateTime>
#include <cstdint>

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

class StationaryModel
{

private:
    QDateTime target;
    u32 pid, ec, frame;
    u16 psv;
    u8 hiddenPower, ability, nature, gender;
    int ivs[6];
    bool shiny;
    bool synch;

public:
    StationaryModel();

    QString getDateTime() const;
    void setTarget(const QDateTime &value);
    u32 getPID() const;
    void setPID(const u32 &value);
    u32 getEC() const;
    void setEC(const u32 &value);
    u32 getFrame() const;
    void setFrame(const u32 &value);
    u16 getPSV() const;
    u8 getHiddenPower() const;
    void calcHiddenPower();
    u8 getAbility() const;
    void setAbility(const u8 &value);
    u8 getNature() const;
    void setNature(const u8 &value);
    u8 getGender() const;
    void setGender(const u8 &value);
    int getIV(int i) const;
    void setIV(const int &i, const int &value);
    bool getShiny() const;
    void setShiny(bool value);
    bool getSynch() const;
    void setSynch(bool value);
};

#endif // STATIONARYMODEL_HPP
