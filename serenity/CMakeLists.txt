# Generated from minimal.pro.

#####################################################################
## QSerenityIntegrationPlugin Plugin:
#####################################################################

set(HAVE_VIDEO_SERENITY TRUE)
set(HAVE_AUDIO_SERENITY TRUE)

set(CXX_STANDARD 20)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

qt_add_plugin(QSerenityIntegrationPlugin
    SHARED
    OUTPUT_NAME qserenity
    PLUGIN_TYPE platforms
    # DEFAULT_IF ${QT_QPA_DEFAULT_PLATFORM} MATCHES serenity # special case
)

target_include_directories(QSerenityIntegrationPlugin PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SYSROOT}/usr/local/include
    ${CMAKE_SYSROOT}/usr/include
    ${CMAKE_SYSROOT}/usr/local/include/QtCore
    ${CMAKE_SYSROOT}/usr/local/include/QtGui
    ${CMAKE_SYSROOT}/usr/local/include/QtGui/6.2.1/QtGui/
    ${CMAKE_SYSROOT}/usr/local/include/QtGui/6.2.1/
    ${CMAKE_SYSROOT}/usr/local/include/QtCore/6.2.1/QtCore/
    ${CMAKE_SYSROOT}/usr/local/include/QtCore/6.2.1/
    ${CMAKE_SYSROOT}/usr/local/mkspecs/serenity-g++
)

target_sources(QSerenityIntegrationPlugin PRIVATE
    main.cpp serenity.json
    qserenitybackingstore.cpp qserenitybackingstore.h
    qserenityintegration.cpp qserenityintegration.h
    qserenityscreen.cpp qserenityscreen.h
    qserenitywindow.cpp qserenitywindow.h
    qserenitystring.cpp qserenitystring.h
)

# TODO figure out why just CXX_STANDARD 20 is not enough
target_compile_options(QSerenityIntegrationPlugin PRIVATE
    -std=c++20)

target_link_libraries(QSerenityIntegrationPlugin PUBLIC
    Qt::Core
    Qt::CorePrivate
    Qt::Gui
    Qt::GuiPrivate
    ipc
    gui
    gfx
    core
    gui
)

install_targets(${CMAKE_INSTALL_PREFIX}/plugins/platforms QSerenityIntegrationPlugin)
