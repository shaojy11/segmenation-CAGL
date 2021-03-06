######################################################################
# Automatically generated by qmake (2.01a) Tue Jul 29 17:20:10 2014
######################################################################

TEMPLATE = app
TARGET =
DEPENDPATH += .
# include headers
INCLUDEPATH += /usr/local/Cellar/cgal/4.4/include \
               /usr/local/Cellar/gmp/6.0.0a/include \
               /usr/local/Cellar/boost/1.55.0_2/include \
	           /usr/local/Cellar/mpfr/3.1.2-p8/include \
               /usr/local/Cellar/qt/4.8.6/include
# include libraries and framework
LIBS += -L/usr/local/Cellar/cgal/4.4/lib \
        -L/usr/local/Cellar/gmp/6.0.0a/lib \
        -L/usr/local/Cellar/boost/1.55.0_2/lib \
        -L/usr/local/Cellar/mpfr/3.1.2-p8/lib\
        -L/usr/local/Cellar/qt/4.8.6/lib
LIBS += -lssl -lcrypto -lgmp
LIBS += -lCGAL
LIBS += -lboost_filesystem -lboost_system

# qt include
QT += xml opengl

# Input


SOURCES += main.cpp

CONFIG += console
CONFIG -= app_bundle
CONFIG += x86_64
#CONFIG -= i386

# compiler setting
QMAKE_CC = gcc
QMAKE_CXX = g++

QMAKE_CFLAGS_X86_64 += -mmacosx-version-min=10.9
QMAKE_CXXFLAGS_X86_64 = $$QMAKE_CFLAGS_X86_64