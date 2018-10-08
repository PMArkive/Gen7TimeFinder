#ifndef PROFILE_HPP
#define PROFILE_HPP

#include <QString>
#include <Core/Game.hpp>
#include <cstdint>

typedef uint32_t u32;
typedef uint16_t u16;

class Profile
{

private:
    QString name;
    u32 offset;
    u16 tid, sid;
    Game version;
    bool shinyCharm;

public:
    Profile();
    Profile(QString name, u32 offset, u16 tid, u16 sid, Game version, bool shinyCharm);
    QString getName() const;
    u32 getOffset() const;
    u16 getTID() const;
    u16 getSID() const;
    Game getVersion() const;
    QString getVersionString() const;
    bool getShinyCharm() const;

};

#endif // PROFILE_HPP
