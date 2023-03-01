QT += core gui widgets
QT += network
CONFIG += c++17

win32-msvc*:QMAKE_CXXFLAGS += /utf-8
# QMAKE_LFLAGS += "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\""


INCLUDEPATH += \
    $$PWD/src/class_ui \
    $$PWD/src/class_mg \

SOURCES += \
    $$PWD/src/main.cpp \
    $$files($$PWD/src/class_mg/*.cpp) \
    $$PWD/src/class_ui/mTrs.cpp \
    src/class_ui/mainwindow.cpp  \
    src/class_ui/titlebar.cpp

HEADERS += \
    $$files($$PWD/src/class_mg/*.h) \
    $$PWD/src/class_ui/mTrs.h \
    src/class_ui/mainwindow.h  \
    src/class_ui/titlebar.h

FORMS += \
    $$PWD/src/class_ui/mTrs.ui \
    src/class_ui/mainwindow.ui \
    src/class_ui/titlebar.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# RC_ICONS = $$PWD/resource/icon/main.ico

DISTFILES += \
    resource/QSS/main.qss \
    resource/icon/114619apczydedup7qqnac (2).jpg \
    resource/icon/114619apczydedup7qqnac.jpg \
    resource/icon/90 (2).jfif \
    resource/icon/90.jfif \
    resource/icon/OIP-C.jfif \
    resource/icon/c1ae3dd7e156423ca1f04775ee9f3034.jpeg \
    resource/icon/e66e16b131.jpg \
    resource/icon/t012ca18bc04b7782c4.jpg \
    resource/icon/windowIcon.png \
    resource/icon/右.png