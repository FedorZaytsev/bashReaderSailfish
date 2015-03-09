# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-bashreader

CONFIG += sailfishapp c++11

SOURCES += src/harbour-bashreader.cpp \
    src/htmlparse.cpp \
    src/fileio.cpp \
    src/translator.cpp \
    src/storage.cpp \
    src/curlproxy.cpp \
    src/curlthread.cpp \
    src/debuginfo.cpp


OTHER_FILES += qml/harbour-bashreader.qml \
    rpm/$${TARGET}.spec \
    rpm/$${TARGET}.yaml \
#    translations/*.ts \
    $${TARGET}.desktop \
    qml/pages/Main.js \
    qml/pages/Menu.qml \
    qml/pages/ListElements.qml \
    qml/pages/QuoteComponent.qml \
    qml/pages/LoadMoreButton.qml \
    qml/pages/InfoPopup.qml \
    qml/pages/CoverPage.qml \
    qml/pages/About.qml \
    qml/pages/QuotePage.qml

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n
TRANSLATIONS += translations/$${TARGET}-ru.ts

HEADERS += \
    src/htmlparse.h \
    src/fileio.h \
    src/translator.h \
    src/storage.h \
    src/curlproxy.h \
    src/curlthread.h \
    src/debuginfo.h



