QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    edge.cpp \
    figure.cpp \
    main.cpp \
    mainwindow.cpp \
    scene.cpp \
    transformMatrix.cpp \
    transformMatrixBuilder.cpp \
    vertex.cpp

HEADERS += \
    baseFileReader.h \
    edge.h \
    figure.h \
    normalizationParameters.h \
    point3D.h \
    scene.h \
    sceneObject.h \
    transformMatrix.h \
    transformMatrixBuilder.h \
    vertex.h \
    mainwindow.h

FORMS += \
    mainwindow.ui \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
