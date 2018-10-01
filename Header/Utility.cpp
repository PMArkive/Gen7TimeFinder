#include "Utility.hpp"

u32 Utility::changeEndian(u32 num)
{
    return ((num >> 24) & 0xff) |
           ((num << 8) & 0xff0000) |
           ((num >> 8) & 0xff00) |
           ((num << 24) & 0xff000000);
}

u64 Utility::getCitraTime(QDateTime dateTime)
{
    u64 val = static_cast<u64>(dateTime.toMSecsSinceEpoch()) + 17017;
    return val - 946684800000;
}

u64 Utility::getNormalTime(u64 time)
{
    return time + 946684800000 - 17017;
}

u32 Utility::calcInitialSeed(u32 *values)
{
    QByteArray input;
    for (int i = 0; i < 4; i++)
    {
        u32 val = changeEndian(values[i]);
        input.append(static_cast<char>(val >> 24));
        input.append(static_cast<char>((val >> 16) & 0xff));
        input.append(static_cast<char>((val >> 8) & 0xff));
        input.append(static_cast<char>(val & 0xff));
    }

    QByteArray hash = QCryptographicHash::hash(input, QCryptographicHash::Sha256);
    hash = hash.toHex().left(8);

    u32 seed = hash.toUInt(nullptr, 16);
    return changeEndian(seed);
}
