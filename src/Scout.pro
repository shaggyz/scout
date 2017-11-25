#-------------------------------------------------
#
# Project created by QtCreator 2017-05-20T16:54:43
#
#-------------------------------------------------

QT += core gui
QT += webkit webkitwidgets positioning

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Scout
TEMPLATE = app

SOURCES += main.cpp\
        ui/mainwindow.cpp \
        ui/scoutwidget.cpp \
    ui/hoststreewidget.cpp \
    ui/discovertabswidget.cpp \
    net/nbtscan.cpp \
    net/host.cpp \
    ui/scanners/smbscanner.cpp \
    net/smbclient.cpp \
    ui/hostdetails.cpp \
    net/geoip.cpp \
    ui/hostshares.cpp \
    ui/scanners/basediscover.cpp \
    ui/actions/togglediscoveraction.cpp

HEADERS  += ui/mainwindow.h \
        ui/scoutwidget.h \
    ui/hoststreewidget.h \
    ui/discovertabswidget.h \
    net/nbtscan.h \
    net/host.h \
    ui/scanners/smbscanner.h \
    net/smbclient.h \
    ui/hostdetails.h \
    net/geoip.h \
    ui/hostshares.h \
    ui/scanners/basediscover.h \
    ui/actions/togglediscoveraction.h

FORMS += \
    ui/scanners/smbscanner.ui \
    ui/hostdetails.ui \
    ui/hostshares.ui
