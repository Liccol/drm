TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET = webserver

SOURCES += main.cpp \
    http_server.cpp \
    common/mongoose.c

HEADERS += \
    http_server.h \
    common/mongoose.h

LIBS += -lpthread libwsock32 libws2_32

#不检测定义后未使用的参数错误等
QMAKE_CXXFLAGS += -Wno-unused-parameter \
                  -Wno-unused-but-set-variable \
                  -Wno-unused-but-set-parameter \
                  -Wno-literal-suffix
                  -std=c++11
QMAKE_CFLAGS += -Wno-unused-parameter \
                -Wno-unused-but-set-variable \
                -Wno-unused-but-set-parameter
