#include "Utility.hpp"

u32 Utility::changeEndian(u32 num)
{
    return ((num >> 24) & 0xff) |
           ((num << 8) & 0xff0000) |
           ((num >> 8) & 0xff00) |
           ((num << 24) & 0xff000000);
}

u64 Utility::getCitraTime(QDateTime dateTime, u64 offset)
{
    u64 val = static_cast<u64>(dateTime.toMSecsSinceEpoch()) + offset;
    return val - 946684800000;
}

u64 Utility::getNormalTime(u64 time, u64 offset)
{
    return time + 946684800000 - offset;
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

QString Utility::getNature(int nature)
{
    const QStringList natures = { "Hardy", "Lonely", "Brave", "Adamant",
                                  "Naughty", "Bold", "Docile", "Relaxed",
                                  "Impish", "Lax", "Timid", "Hasty",
                                  "Serious", "Jolly", "Naive", "Modest",
                                  "Mild", "Quiet", "Bashful", "Rash",
                                  "Calm", "Gentle", "Sassy", "Careful",
                                  "Quirky"
                                };
    return natures[nature];
}

QString Utility::getHiddenPower(int hiddenPower)
{
    const QStringList hiddenPowers = { "Fighting", "Flying", "Poison", "Ground",
                                       "Rock", "Bug", "Ghost", "Steel",
                                       "Fire", "Water", "Grass", "Electric",
                                       "Psychic", "Ice", "Dragon", "Dark"
                                     };
    return hiddenPowers[hiddenPower];
}

QVector<Profile> Utility::loadProfileList()
{
    QVector<Profile> profileList;

    QDomDocument doc;
    QFile file(QApplication::applicationDirPath() + "/profiles.xml");
    if (file.open(QIODevice::ReadOnly | QFile::Text))
    {
        doc.setContent(&file);
        file.close();

        QDomElement profiles = doc.documentElement();
        QDomNode domNode = profiles.firstChild();
        while (!domNode.isNull())
        {
            QDomElement domElement = domNode.toElement();
            if (!domElement.isNull())
            {
                if (domElement.tagName() == "Gen7")
                {
                    QDomNode info = domElement.firstChild();
                    QString name;
                    u32 offset = 0;
                    u16 tid = 0, sid = 0;
                    Game version = Game::UltraSun;
                    bool charm = false;

                    while (!info.isNull())
                    {
                        QDomElement infoElement = info.toElement();
                        if (!infoElement.isNull())
                        {
                            const QString tagName(infoElement.tagName());
                            if (tagName == "name")
                            {
                                name = infoElement.text();
                            }
                            else if (tagName == "offset")
                            {
                                offset = infoElement.text().toUInt();
                            }
                            else if (tagName == "tid")
                            {
                                tid = infoElement.text().toUShort();
                            }
                            else if (tagName == "sid")
                            {
                                sid = infoElement.text().toUShort();
                            }
                            else if (tagName == "version")
                            {
                                version = static_cast<Game>(infoElement.text().toInt());
                            }
                            else if (tagName == "charm")
                            {
                                charm = infoElement.text().toInt();
                            }

                            info = info.nextSibling();
                        }
                    }
                    profileList.append(Profile(name, offset, tid, sid, version, charm));
                }
            }
            domNode = domNode.nextSibling();
        }
    }

    return profileList;
}

void Utility::saveProfile(Profile profile)
{
    QDomDocument doc;
    QFile file(QApplication::applicationDirPath() + "/profiles.xml");
    if (file.open(QIODevice::ReadOnly | QFile::Text))
    {
        doc.setContent(&file);
        file.close();

        QDomElement profiles = doc.documentElement();

        QDomElement gen7 = doc.createElement("Gen7");
        QDomElement name = doc.createElement("name");
        QDomElement offset = doc.createElement("offset");
        QDomElement tid = doc.createElement("tid");
        QDomElement sid = doc.createElement("sid");
        QDomElement version = doc.createElement("version");
        QDomElement charm = doc.createElement("charm");

        name.appendChild(doc.createTextNode(profile.getName()));
        offset.appendChild(doc.createTextNode(QString::number(profile.getOffset())));
        tid.appendChild(doc.createTextNode(QString::number(profile.getTID())));
        sid.appendChild(doc.createTextNode(QString::number(profile.getSID())));
        version.appendChild(doc.createTextNode(QString::number(profile.getVersion())));
        charm.appendChild(doc.createTextNode(QString::number(profile.getShinyCharm())));

        gen7.appendChild(name);
        gen7.appendChild(offset);
        gen7.appendChild(tid);
        gen7.appendChild(sid);
        gen7.appendChild(version);
        gen7.appendChild(charm);

        if (profiles.isNull())
        {
            profiles = doc.createElement("Profiles");
            profiles.appendChild(gen7);
            doc.appendChild(profiles);
        }
        else
        {
            profiles.appendChild(gen7);
        }

        if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QFile::Text))
        {
            QTextStream stream(&file);
            stream.setCodec("UTF-8");
            stream << doc.toString();
        }
        file.close();
    }
}

void Utility::deleteProfile(Profile profile)
{
    QDomDocument doc;
    QFile file(QApplication::applicationDirPath() + "/profiles.xml");
    if (file.open(QIODevice::ReadOnly | QFile::Text))
    {
        doc.setContent(&file);
        file.close();

        QDomElement profiles = doc.documentElement();
        QDomNode domNode = profiles.firstChild();
        while (!domNode.isNull())
        {
            QDomElement domElement = domNode.toElement();
            if (!domElement.isNull())
            {
                if (domElement.tagName() == "Gen7")
                {
                    QDomNode info = domElement.firstChild();
                    while (!info.isNull())
                    {
                        QDomElement infoElement = info.toElement();
                        if (!infoElement.isNull())
                        {
                            const QString tagName(infoElement.tagName());
                            if (tagName == "name")
                            {
                                if (profile.getName() == infoElement.text())
                                {
                                    domNode.parentNode().removeChild(domNode);

                                    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QFile::Text))
                                    {
                                        QTextStream stream(&file);
                                        stream.setCodec("UTF-8");
                                        stream << doc.toString();
                                    }
                                    file.close();
                                    return;
                                }
                            }
                            info = info.nextSibling();
                        }
                    }
                }
            }
            domNode = domNode.nextSibling();
        }
    }
}

void Utility::updateProfile(Profile original, Profile edit)
{
    QDomDocument doc;
    QFile file(QApplication::applicationDirPath() + "/profiles.xml");
    if (file.open(QIODevice::ReadOnly | QFile::Text))
    {
        doc.setContent(&file);
        file.close();

        QDomElement profiles = doc.documentElement();
        QDomNode domNode = profiles.firstChild();
        while (!domNode.isNull())
        {
            QDomElement domElement = domNode.toElement();
            if (!domElement.isNull() && domElement.tagName() == "Gen7")
            {
                QString name = domElement.childNodes().at(0).toElement().text();
                u32 offset = domElement.childNodes().at(1).toElement().text().toUInt();
                u16 tid = domElement.childNodes().at(2).toElement().text().toUShort();
                u16 sid = domElement.childNodes().at(3).toElement().text().toUShort();
                int version = domElement.childNodes().at(4).toElement().text().toInt();
                bool charm = domElement.childNodes().at(5).toElement().text().toInt();

                if (original.getName() == name && original.getOffset() == offset && original.getTID() == tid &&
                        original.getSID() == sid && original.getVersion() == version && original.getShinyCharm() == charm)
                {
                    domElement.childNodes().at(0).toElement().firstChild().setNodeValue(edit.getName());
                    domElement.childNodes().at(1).toElement().firstChild().setNodeValue(QString::number(edit.getOffset()));
                    domElement.childNodes().at(2).toElement().firstChild().setNodeValue(QString::number(edit.getTID()));
                    domElement.childNodes().at(3).toElement().firstChild().setNodeValue(QString::number(edit.getSID()));
                    domElement.childNodes().at(4).toElement().firstChild().setNodeValue(QString::number(edit.getVersion()));
                    domElement.childNodes().at(5).toElement().firstChild().setNodeValue(QString::number(edit.getShinyCharm()));

                    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QFile::Text))
                    {
                        QTextStream stream(&file);
                        stream.setCodec("UTF-8");
                        stream << doc.toString();
                    }
                    file.close();
                    return;
                }
            }
            domNode = domNode.nextSibling();
        }
    }
}


QStringList Utility::getNatures()
{
    QStringList natures = { "None", "Hardy", "Lonely", "Brave", "Adamant",
                            "Naughty", "Bold", "Docile", "Relaxed", "Impish",
                            "Lax", "Timid", "Hasty", "Serious", "Jolly",
                            "Naive", "Modest", "Mild", "Quiet", "Bashful",
                            "Rash", "Calm", "Gentle", "Sassy", "Careful", "Quirky"
                          };
    return natures;
}

QStringList Utility::getHiddenPowers()
{
    QStringList hiddenPowers = { "None", "Fighting", "Flying", "Poison",
                                 "Ground", "Rock", "Bug", "Ghost",
                                 "Steel", "Fire", "Water", "Grass",
                                 "Electric", "Psychic", "Ice", "Dragon", "Dark"
                               };
    return hiddenPowers;
}

QStringList Utility::getGenderRatios()
{
    QStringList genderRatios = { "Genderless", "♂1 : ♀1", "♂7 : ♀1", "♂3 : ♀1",
                                 "♂1 : ♀3", "♂1 : ♀7", "♂ Only", "♀ Only"
                               };
    return genderRatios;
}
