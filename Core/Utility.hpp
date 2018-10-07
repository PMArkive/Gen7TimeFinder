#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <QCryptographicHash>
#include <QDateTime>
#include <QString>
#include <QDomDocument>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <cstdint>
#include <Models/Profile.hpp>

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint8_t u8;

namespace Utility
{
    u32 changeEndian(u32 num);
    u64 getCitraTime(QDateTime dateTime, u64 offset);
    u64 getNormalTime(u64 time, u64 offset);
    u32 calcInitialSeed(u32 *values);
    QString getNature(u8 nature);
    QString getHiddenPower(u8 hiddenPower);
    QVector<Profile> loadProfileList();
    void saveProfile(Profile profile);
    void deleteProfile(Profile profile);
    void updateProfile(Profile original, Profile edit);

}

#endif // UTILITY_HPP
