TEMPLATE += app
QT += quick qml
CONFIG += c++11


SOURCES += \
    main.cpp \
    QControlerMain.cpp

DISTFILES += \
    QViewMain.qml

HEADERS += \
    QControlerMain.h \

INCLUDEPATH += \
    ../chatGen/include \
    ../vnet/include \
    ../vlog/include \
    ../vutil/include \

LIBS += \
    -L../chatGen/ -lChatGen \
    -L../vnet/ -lVnet \
    -L../vlog/ -lVlog \
    -L../vutil/ -lVutil \
