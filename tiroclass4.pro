#-------------------------------------------------
#
# Project created by Bouns
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tiroclass4
TEMPLATE = app


SOURCES += main.cpp\
        ihmtiroclass.cpp \
        dal.cpp

HEADERS  += ihmtiroclass.h \
        dal.h

FORMS    += ihmtiroclass.ui


RC_FILE = myapp.rc

QT += serialport        #port pour communication XBEE
