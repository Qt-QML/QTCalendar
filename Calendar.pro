QT += qml quick sql network networkauth location positioning
CONFIG += c++11
TARGER = Calendar

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    src/event.h \
    src/eventmodel.h \
    src/googleauth.h

SOURCES += \
        src/event.cpp \
        src/eventmodel.cpp \
        src/googleauth.cpp \
        src/main.cpp

RESOURCES += resources.qrc
OTHER_FILES +=

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    qml/Calendar.qml \
    qml/CalendarView.qml \
    qml/EditRuleView.qml \
    qml/EditView.qml \
    qml/EventView.qml \
    qml/MapView.qml \
    qml/SelectorView.qml \
    qml/TestView.qml \
    qml/main.qml \
    src/server.js

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}
