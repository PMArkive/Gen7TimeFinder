#ifndef IDMODEL_HPP
#define IDMODEL_HPP

#include <QDateTime>
#include <QString>
#include <cstdint>

typedef uint32_t u32;
typedef uint16_t u16;

class IDModel
{

private:
    QDateTime target;
    u32 seed, frame;
    u16 tid;
    u16 sid;
    u16 tsv;
    u32 displayTID;

public:
    IDModel(u32 seed, u32 frame, u32 rand);
    IDModel() {}
    QString getDateTime();
    u32 getSeed() const;
    u32 getFrame() const;
    u16 getTID() const;
    u16 getSID() const;
    u16 getTSV() const;
    u32 getDisplayTID() const;
    void setTarget(const QDateTime &value);

};

#endif // IDMODEL_HPP
