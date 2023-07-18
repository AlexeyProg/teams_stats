QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    obj/datacontainer.cpp \
    obj/hero.cpp \
    main.cpp \
    mainwindow.cpp \
    requester.cpp \
    obj/team.cpp \
    teamicon.cpp

HEADERS += \
    obj/datacontainer.h \
    obj/hero.h \
    mainwindow.h \
    requester.h \
    obj/team.h \
    teamicon.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img/icons.qrc
