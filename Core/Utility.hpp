#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <QCryptographicHash>
#include <QDateTime>
#include <QString>
#include <cstdint>

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint8_t u8;

namespace Utility
{
    u32 changeEndian(u32 num);
    u64 getCitraTime(QDateTime dateTime);
    u64 getNormalTime(u64 time);
    u32 calcInitialSeed(u32 *values);
    QString getNature(u8 nature);
    QString getHiddenPower(u8 hiddenPower);

}

#endif // UTILITY_HPP
