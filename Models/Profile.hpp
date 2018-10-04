#ifndef PROFILE_HPP
#define PROFILE_HPP

#include <QString>
#include <QDomDocument>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QVector>
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

public:
    Profile();
    Profile(QString name, u32 offset, u16 tid, u16 sid, Game version);
    QString getName() const;
    u32 getOffset() const;
    u16 getTID() const;
    u16 getSID() const;
    Game getVersion() const;
    QString getVersionString() const;
    static QVector<Profile> loadProfileList();
    void saveProfile();
    void deleteProfile();
    void updateProfile(Profile edit);

};

#endif // PROFILE_HPP
