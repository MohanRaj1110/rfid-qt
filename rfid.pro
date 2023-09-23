QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Arduino.cpp \
    MFRC522.cpp \
    ReadUidMultiReader.cpp \
    Serial.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Arduino.h \
    MFRC522.h \
    SPI.h \
    Serial.h \
    deprecated.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH    += /usr/local/include
LIBS += -L/usr/local/lib -lbcm2835
