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
