# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

# This is a reminder that you are using a generated .pro file.
# Remove it when you are finished editing this file.
message("You are running qmake on a generated .pro file. This may not work!")


HEADERS += ./resource.h \
    ./stdafx.h \
    ./Foundation/Control/SystemTray.h \
    ./MainView.h \
    ./Foundation/View/BaseView.h \
    ./Foundation/View/AboutView.h \
    ./Foundation/View/SettingView.h \
    ./Foundation/View/InformationView.h \
    ./Foundation/Effect/WindowCompositionAttribute.h \
    ./Foundation/Effect/CustomShadowEffect.h \
    ./Foundation/Control/CaptionButton.h \
    ./Foundation/Control/ActionButton.h \
    ./Foundation/Control/ImageWidget.h \
    ./Foundation/Control/Label.h \
    ./Foundation/Control/Slider.h \
    ./Foundation/Control/Menu.h \
    ./Foundation/Core/MUSIC_TAG_INFO.h \
    ./Foundation/Core/MUSIC_PLAYER.h
SOURCES += ./Foundation/Control/SystemTray.cpp \
    ./main.cpp \
    ./MainView.cpp \
    ./stdafx.cpp \
    ./Foundation/View/AboutView.cpp \
    ./Foundation/View/BaseView.cpp \
    ./Foundation/View/InformationView.cpp \
    ./Foundation/View/SettingView.cpp \
    ./Foundation/Effect/CustomShadowEffect.cpp \
    ./Foundation/Control/CaptionButton.cpp \
    ./Foundation/Control/ActionButton.cpp \
    ./Foundation/Control/ImageWidget.cpp \
    ./Foundation/Control/Label.cpp \
    ./Foundation/Control/Slider.cpp \
    ./Foundation/Control/Menu.cpp \
    ./Foundation/Core/MUSIC_PLAYER.cpp \
    ./Foundation/Core/MUSIC_TAG_INFO.cpp
FORMS += ./Foundation/View/AboutView.ui \
    ./Foundation/View/SettingView.ui
RESOURCES += MainView.qrc \
    Resources/icons.qrc
