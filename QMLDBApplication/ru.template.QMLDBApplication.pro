TARGET = ru.template.QMLDBApplication

CONFIG += \
    auroraapp \
    qml_debug

PKGCONFIG += \

SOURCES += \
    src/main.cpp \

HEADERS += \

DISTFILES += \
    rpm/ru.template.QMLDBApplication.spec \

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/ru.template.QMLDBApplication.ts \
    translations/ru.template.QMLDBApplication-ru.ts \
