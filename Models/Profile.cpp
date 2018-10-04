#include "Profile.hpp"

Profile::Profile()
{
    name = "None";
    offset = 17017;
    tid = 12345;
    sid = 54321;
    version = Game::UltraSun;
}

Profile::Profile(QString name, u32 offset, u16 tid, u16 sid, Game version)
{
    this->name = name;
    this->offset = offset;
    this->tid = tid;
    this->sid = sid;
    this->version = version;
}

QString Profile::getName() const
{
    return name;
}

u32 Profile::getOffset() const
{
    return offset;
}

u16 Profile::getTID() const
{
    return tid;
}

u16 Profile::getSID() const
{
    return sid;
}

Game Profile::getVersion() const
{
    return version;
}

QString Profile::getVersionString() const
{
    switch (version)
    {
        case Game::Sun:
            return "Sun";
        case Game::Moon:
            return "Moon";
        case Game::UltraSun:
            return "Ultra Sun";
        case Game::UltraMoon:
            return "Ultra Moon";
    }
}

QVector<Profile> Profile::loadProfileList()
{
    static QVector<Profile> profileList;
    profileList.clear();

    QDomDocument doc;
    QFile file(QApplication::applicationDirPath() + "/profiles.xml");
    if (file.open(QIODevice::ReadOnly | QFile::Text))
    {
        doc.setContent(&file);

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
                    int version = 0;
                    u16 tid = 0, sid = 0;
                    u32 offset = 0;
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
                            else if (tagName == "version")
                            {
                                version = infoElement.text().toInt();
                            }
                            else if (tagName == "tid")
                            {
                                tid = infoElement.text().toUShort();
                            }
                            else if (tagName == "sid")
                            {
                                sid = infoElement.text().toUShort();
                            }
                            else if (tagName == "offset")
                            {
                                offset = infoElement.text().toUInt();
                            }

                            info = info.nextSibling();
                        }
                    }
                    profileList.append(Profile(name, offset, tid, sid, static_cast<Game>(version)));
                }
            }
            domNode = domNode.nextSibling();
        }
        file.close();
    }

    return profileList;
}

void Profile::saveProfile()
{
    QDomDocument doc;
    QFile file(QApplication::applicationDirPath() + "/profiles.xml");
    if (file.open(QIODevice::ReadOnly | QFile::Text))
    {
        doc.setContent(&file);
        file.close();

        QDomElement profiles = doc.documentElement();

        QDomElement gen7 = doc.createElement("Gen7");
        QDomElement profileName = doc.createElement("name");
        QDomElement profileOffset = doc.createElement("offset");
        QDomElement profileTID = doc.createElement("tid");
        QDomElement profileSID = doc.createElement("sid");
        QDomElement profileVersion = doc.createElement("version");

        profileName.appendChild(doc.createTextNode(name));
        profileOffset.appendChild(doc.createTextNode(QString::number(offset)));
        profileTID.appendChild(doc.createTextNode(QString::number(tid)));
        profileSID.appendChild(doc.createTextNode(QString::number(sid)));
        profileVersion.appendChild(doc.createTextNode(QString::number(version)));

        gen7.appendChild(profileName);
        gen7.appendChild(profileOffset);
        gen7.appendChild(profileTID);
        gen7.appendChild(profileSID);
        gen7.appendChild(profileVersion);

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

void Profile::deleteProfile()
{
    bool exists = false;
    QDomDocument doc;
    QFile file(QApplication::applicationDirPath() + "/profiles.xml");
    if (file.open(QIODevice::ReadOnly | QFile::Text))
    {
        doc.setContent(&file);

        file.close();

        QDomElement profiles = doc.documentElement();
        QDomNode domNode = profiles.firstChild();
        while (!domNode.isNull() && !exists)
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
                                if (this->name == infoElement.text())
                                {
                                    exists = true;
                                    domNode.parentNode().removeChild(domNode);
                                }
                                break;
                            }
                            info = info.nextSibling();
                        }
                    }
                }
            }
            domNode = domNode.nextSibling();
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

void Profile::updateProfile(Profile edit)
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

                if (original.profileName == name && original.version == ver && original.language == lang && original.tid == id && original.sid == id2 && original.deadBattery == flag)
                {
                    domElement.childNodes().at(0).toElement().firstChild().setNodeValue(profileName);
                    domElement.childNodes().at(1).toElement().firstChild().setNodeValue(QString::number(version));
                    domElement.childNodes().at(2).toElement().firstChild().setNodeValue(QString::number(language));
                    domElement.childNodes().at(3).toElement().firstChild().setNodeValue(QString::number(tid));
                    domElement.childNodes().at(4).toElement().firstChild().setNodeValue(QString::number(sid));
                    domElement.childNodes().at(5).toElement().firstChild().setNodeValue(QString::number(deadBattery));

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
