QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    graphwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    s21_calculator.c \
    s21_smartcalc.c \
    s21_stack.c \
    s21_validators.c \
    s21_credit.c \
    s21_deposit.c \

HEADERS += \
    graphwidget.h \
    mainwindow.h \
    qcustomplot.h \
    s21_smartcalc.h \


FORMS += \
    graphwidget.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
