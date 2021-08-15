# Generated from minimal.pro.

#####################################################################
## QSerenityIntegrationPlugin Plugin:
#####################################################################

set(HAVE_VIDEO_SERENITY TRUE)
set(HAVE_AUDIO_SERENITY TRUE)

set(CXX_STANDARD 20)

qt_internal_add_plugin(QSerenityIntegrationPluginn
    OUTPUT_NAME qserenityn
    TYPE platforms
    DEFAULT_IF ${QT_QPA_DEFAULT_PLATFORM} MATCHES serenity # special case
    SOURCES
        main.cpp
        qserenitybackingstore.cpp qserenitybackingstore.h
        qserenityintegration.cpp qserenityintegration.h
        qserenityscreen.cpp qserenityscreen.h
        qserenitywindow.cpp qserenitywindow.h
        qserenitystring.cpp qserenitystring.h
    DEFINES
        QT_NO_FOREACH
    INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${SERENITY_INSTALL_ROOT}/usr/local/include
        ${SERENITY_INSTALL_ROOT}/usr/include
    LIBRARIES
        Qt::Core
        Qt::CorePrivate
        Qt::Gui
        Qt::GuiPrivate
        ipc 
        gui
        gfx
        core
)


#### Keys ignored in scope 1:.:.:minimal.pro:<TRUE>:
# OTHER_FILES = "minimal.json"

## Scopes:
#####################################################################

#### Keys ignored in scope 3:.:.:minimal.pro:NOT TARGET___equals____ss_QT_DEFAULT_QPA_PLUGIN:
# PLUGIN_EXTENDS = "-"
