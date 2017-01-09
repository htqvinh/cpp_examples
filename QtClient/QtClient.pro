TEMPLATE += app
QT += quick qml
CONFIG += c++11

INCLUDEPATH += \
    ../vnet/include \
    ../vlog/include \
    ../vutil/include \
    ../chatGen/include \

LIBS += \
    -L../vnet -lVnet \
    -L../vlog -lVlog \
    -L../vutil -lVutil \
    -L../chatGen -lChatGen \
    -static-libstdc++ \

SOURCES += \
    main.cpp \
    QControlerMain.cpp

DISTFILES += \
    QViewMain.qml

HEADERS += \
    QControlerMain.h

