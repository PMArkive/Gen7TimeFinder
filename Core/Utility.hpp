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

namespace Utility
{
    u32 changeEndian(u32 num);
    u64 getCitraTime(QDateTime dateTime, u64 offset);
    u64 getNormalTime(u64 time, u64 offset);
    u32 calcInitialSeed(u32 *values);
    QString getNature(int nature);
    QString getHiddenPower(int hiddenPower);
    QVector<Profile> loadProfileList();
    void saveProfile(Profile profile);
    void deleteProfile(Profile profile);
    void updateProfile(Profile original, Profile edit);
    QStringList getNatures();
    QStringList getHiddenPowers();
    QStringList getGenderRatios();

}

#endif // UTILITY_HPP
