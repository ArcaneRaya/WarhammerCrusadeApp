QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    battlefieldroledata.cpp \
    classiccrusadewindow.cpp \
    generalcrusadedata.cpp \
    intvaluelineedit.cpp \
    main.cpp \
    mainwindow.cpp \
    oobsortfilterproxymodel.cpp \
    orderofbattle.cpp \
    orderofbattledata.cpp \
    orderofbattleunitsmodel.cpp \
    runtimedata.cpp \
    unitcrusadecard.cpp \
    unitcrusadedata.cpp

HEADERS += \
    battlefieldroledata.h \
    classiccrusadewindow.h \
    generalcrusadedata.h \
    intvaluelineedit.h \
    json.hpp \
    mainwindow.h \
    oobsortfilterproxymodel.h \
    orderofbattle.h \
    orderofbattledata.h \
    orderofbattleunitsmodel.h \
    runtimedata.h \
    unitcrusadecard.h \
    unitcrusadedata.h

FORMS += \
    classiccrusadewindow.ui \
    mainwindow.ui \
    orderofbattle.ui \
    unitcrusadecard.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    CrusadeResources.qrc
