TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++14
SOURCES += main.cpp \
    lambdas_and_containers.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    lambdas_and_containers.h

