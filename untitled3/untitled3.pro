QT += sql \
    quick \
    printsupport \
    charts \
    serialport \
    widgets \
    quickwidgets \
    core \
    gui \
    multimedia \
    multimediawidgets


#INCLUDEPATH += C:/Users/asus/OneDrive/Bureau/qt/nouveau/qt/final/untitled3/zxing/common

#LIBS += -L. -lssleay32 -llibeay32
#INCLUDEPATH += C:\Users\asus\OneDrive\Bureau\qzxing-master\qzxing-master\src\QZXing
#LIBS += -L C:\Users\asus\OneDrive\Bureau\qzxing-master\qzxing-master\src\QZXing-lQZXing

#INCLUDEPATH +=C:/Users/asus/OneDrive/Bureau/cryptopp890
#LIBS += -LC:/Users/asus/OneDrive/Bureau/cryptopp890

#INCLUDEPATH += C:/Users/asus/OneDrive/Bureau/qt/nouveau/qt/final/untitled3/cryptopp890
#LIBS += -L C:\Users\asus\OneDrive\Bureau\formation_QT\add me to your project so mail works
#INCLUDEPATH += C:\Users\asus\OneDrive\Bureau\formation_QT\add me to your project so mail works
#SOURCES += C:\Users\asus\OneDrive\Bureau\formation_QT\add me to your project so mail works \smtp.cpp

#INCLUDEPATH +=C:\Users\asus\OneDrive\Bureau\SmtpClient-for-Qt-2.0\src
#SOURCES += C:\Users\asus\OneDrive\Bureau\SmtpClient-for-Qt-2.0\src
#SOURCES +=smtp.cpp \
   # oublierr.cpp


#HEADERS +=smtp.h \
  #  oublierr.h


#INCLUDEPATH += cryptopp890
#LIBS += -Lcryptopp890 -lcryptopp
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET =webview
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    connection.cpp \
    cryptage.cpp \
    decryptage.cpp \
    enregistrement.cpp \
    inscrit.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    mdp.cpp \
    sms.cpp \
    smtp.cpp\
    personnels.cpp \
    smtpp.cpp

HEADERS += \
    arduino.h \
    connection.h \
    cryptage.h \
    decryptage.h \
    enregistrement.h \
    inscrit.h \
    login.h \
    mainwindow.h \
    mdp.h \
    personnels.h \
    sms.h \
    smtp.h \
    smtpp.h

FORMS += \
    inscrit.ui \
    login.ui \
    mainwindow.ui \
    mdp.ui \
    oublierr.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#RESOURCES += \

   # ../qml.qrc \
   # ../A.qrc \
    #../b.qrc \
    #../delete.qrc \
    #../farah.qrc \
    #../farah1.qrc \
    #../farahh.qrc \
    #../farahhh.qrc \
    #../farahhhh.qrc \
    #../farahhhhhh.qrc \
   # ../farahhhhhhhhhh.qrc \
    #../farahhhhhhhhhhhhhhhh.qrc \
    #../finallllflch.qrc \
   # ../flchhh.qrc \
    #../hommmmeee.qrc \
    #../img.qrc \
    #../listttt.qrc \
    #../login1.qrc \
    #../loginn.qrc \
    #../logofinal.qrc \
   # ../mdp.qrc \
    #../modifier.qrc \
    #../paraaa.qrc \
    #../recherche.qrc \
    #../salim.qrc \
    #../sort.qrc \
    #../statttt.qrc \
    #persoo.qrc

RESOURCES += \
    Map.qrc \
    marqueur.qrc
