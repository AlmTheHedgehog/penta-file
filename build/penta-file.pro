######################################################################
# Automatically generated by qmake (3.1) Mon Oct 23 23:43:16 2023
######################################################################

TEMPLATE = app
TARGET = penta-file
INCLUDEPATH += $$PWD/../include

QT += widgets
LIBS += -lcrypto

QT += widgets

MOC_DIR     = moc
OBJECTS_DIR = obj
RCC_DIR     = rcc
DESTDIR     = bin


# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#Debug arg
#QMAKE_CXXFLAGS += -g

# Input
HEADERS += ../include/* ../include/widget/*
SOURCES += ../src/main.cpp \
           ../src/widget/LineEntry.cpp \
           ../src/widget/EntriesWindow.cpp \
           ../src/widget/TopBarWidget.cpp \
           ../src/widget/MainFoldersWidget.cpp\
           ../src/widget/ChecksumDialogWindow.cpp\
           ../src/widget/AppWidget.cpp
RESOURCES += penta-file.qrc
