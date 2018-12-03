#-------------------------------------------------
#
# Project created by QtCreator 2018-09-30T12:13:07
#
#-------------------------------------------------

lessThan(QT_MAJOR_VERSION, 5): error("You need at least Qt 5.11 to build Gen7TimeFinder")
equals(QT_MAJOR_VERSION, 5):lessThan(QT_MINOR_VERSION, 11): error("You need at least Qt 5.11 to build Gen7TimeFinder")

QT += widgets

TARGET = Gen7TimeFinder
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++14

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    Forms/MainWindow.ui \
    Forms/ProfileCalibrater.ui \
    Forms/ProfileEditor.ui \
    Forms/ProfileManager.ui

HEADERS += \
    Core/Game.hpp \
    Core/IDFilter.hpp \
    Core/IDSearcher.hpp \
    Core/ProfileSearcher.hpp \
    Core/SFMT.hpp \
    Core/StationaryFilter.hpp \
    Core/StationarySearcher.hpp \
    Core/Utility.hpp \
    Forms/MainWindow.hpp \
    Forms/ProfileCalibrater.hpp \
    Forms/ProfileEditor.hpp \
    Forms/ProfileManager.hpp \
    Models/IDModel.hpp \
    Models/ProfileModel.hpp \
    Models/StationaryModel.hpp \
    Results/IDResult.hpp \
    Results/Profile.hpp \
    Results/StationaryResult.hpp

SOURCES += \
    Core/IDFilter.cpp \
    Core/IDSearcher.cpp \
    Core/ProfileSearcher.cpp \
    Core/SFMT.cpp \
    Core/StationaryFilter.cpp \
    Core/StationarySearcher.cpp \
    Core/Utility.cpp \
    Forms/MainWindow.cpp \
    Forms/ProfileCalibrater.cpp \
    Forms/ProfileEditor.cpp \
    Forms/ProfileManager.cpp \
    Models/IDModel.cpp \
    Models/ProfileModel.cpp \
    Models/StationaryModel.cpp \
    Results/IDResult.cpp \
    Results/Profile.cpp \
    Results/StationaryResult.cpp \
    main.cpp
