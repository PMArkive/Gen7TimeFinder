#include <QCoreApplication>
#include <QVector>
#include <QDateTime>
#include <QDebug>
#include <QCryptographicHash>
#include <iostream>
#include <cstdint>
#include <SFMT.hpp>

typedef uint64_t u64;
typedef uint32_t u32;
using std::cin;

u64 getCitraTime(QDateTime dateTime)
{
    u64 val = static_cast<u64>(dateTime.toMSecsSinceEpoch()) + 17017;
    return val - 946684800000;
}

u64 getNormalTime(u64 epoch)
{
    return epoch + 946684800000 - 17017;
}

u32 changeEndian(u32 num)
{
    return ((num >> 24) & 0xff) |
           ((num << 8) & 0xff0000) |
           ((num >> 8) & 0xff00) |
           ((num << 24) & 0xff000000);
}

u32 calcSeed(QByteArray input)
{
    QByteArray hash = QCryptographicHash::hash(input, QCryptographicHash::Sha256);
    hash = hash.toHex().left(8);

    u32 seed = hash.toUInt(nullptr, 16);
    return changeEndian(seed);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    u32 targetTID, targetSID, maxFrames;

    qDebug() << "Enter desired tid:";
    cin >> targetTID;

    qDebug() << "Enter desired sid:";
    cin >> targetSID;

    qDebug() << "Enter max frames:";
    cin >> maxFrames;
    maxFrames += 1132;

    qDebug() << "";

    QDateTime start = QDateTime(QDate(2000, 1, 1), QTime(0, 0, 0));
    start.setTimeSpec(Qt::UTC);
    u64 epochStart = getCitraTime(start);

    QDateTime end = QDateTime(QDate(2100, 1, 1), QTime(0, 0, 0));
    end.setTimeSpec((Qt::UTC));
    u64 epochEnd = getCitraTime(end);

    for (u64 epoch = epochStart; epoch < epochEnd; epoch += 60000)
    {
        u32 vals[4] = { 0x383e329, 0, static_cast<u32>(epoch & 0xffffffff), static_cast<u32>(epoch >> 32)};

        QByteArray values;
        for (int i = 0; i < 4; i++)
        {
            u32 val = changeEndian(vals[i]);
            values.append(static_cast<char>(val >> 24));
            values.append(static_cast<char>((val >> 16) & 0xff));
            values.append(static_cast<char>((val >> 8) & 0xff));
            values.append(static_cast<char>(val & 0xff));
        }

        u32 initialSeed = calcSeed(values);

        SFMT sfmt(initialSeed);
        sfmt.advanceFrames(1132);
        u32 frame = 1132;

        for (; frame < maxFrames; frame++)
        {
            u32 seed = sfmt.nextULong() & 0xffffffff;
            u32 tid = seed & 0xffff;
            u32 sid = seed >> 16;

            if (tid == targetTID && sid == targetSID)
            {
                QDateTime target = QDateTime::fromMSecsSinceEpoch(static_cast<qlonglong>(getNormalTime(epoch)), Qt::UTC);

                qDebug() << target;
                qDebug () << "Seed:" << QString::number(initialSeed, 16);
                qDebug() << "Frame:" << QString::number(frame);
                qDebug() << "";
            }
        }
    }

    qDebug() << "Finished.";

    /*QDateTime time(QDate(2067, 12, 18), QTime(5, 25, 0));
    u64 epoch = getCitraTime(time);

    for (u32 tick = 0; tick < 0x4000000; tick++)
    {
        u32 vals[4] = { tick, 0, static_cast<u32>(epoch & 0xffffffff), static_cast<u32>(epoch >> 32)};

        QByteArray values;
        for (int i = 0; i < 4; i++)
        {
            u32 val = changeEndian(vals[i]);
            values.append(static_cast<char>(val >> 24));
            values.append(static_cast<char>((val >> 16) & 0xff));
            values.append(static_cast<char>((val >> 8) & 0xff));
            values.append(static_cast<char>(val & 0xff));
        }

        u32 initialSeed = calcSeed(values);
        if (initialSeed == 0x5178CA42)
        {
            qDebug() << QString::number(tick, 16);
        }
    }

    qDebug() << "Done";*/

    return a.exec();
}
