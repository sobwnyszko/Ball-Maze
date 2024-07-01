QT       += core gui serialport charts qml 3dcore 3drender 3dinput 3dlogic 3dquick 3dextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/gra.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/wykresy.cpp

HEADERS += \
    inc/gra.h \
    inc/mainwindow.h \
    inc/wykresy.h

FORMS += \
    ui/gra.ui \
    ui/mainwindow.ui \
    ui/wykresy.ui

TRANSLATIONS += \
    LabiryntKulkowy_pl_PL.ts \
    LabiryntKulkowy_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
