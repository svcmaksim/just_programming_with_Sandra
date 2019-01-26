TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ode_solver.cpp

HEADERS += \
    ode_solver.h \
    common_utils.h
