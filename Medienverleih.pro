QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AusleihVerwaltung.cpp \
    Ausleihe.cpp \
    Buch.cpp \
    Daten.cpp \
    Film.cpp \
    Medium.cpp \
    Person.cpp \
    main.cpp \
    mainWindowAusleihen.cpp \
    verwalteDatenTabelle.cpp \
    verwalteMedienDialog.cpp \
    verwaltePersonenDialog.cpp

HEADERS += \
    AusleihVerwaltung.h \
    Ausleihe.h \
    Buch.h \
    Daten.h \
    Film.h \
    Medium.h \
    Person.h \
    mainWindowAusleihen.h \
    verwalteDatenTabelle.h \
    verwalteMedienDialog.h \
    verwaltePersonenDialog.h

FORMS += \
    mainWindowAusleihen.ui \
    verwalteMedienDialog.ui \
    verwaltePersonenDialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
