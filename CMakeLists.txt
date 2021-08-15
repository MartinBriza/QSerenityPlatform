# Generated from minimal.pro.

project(QSerenityIntegrationPlugin)
cmake_minimum_required(VERSION 3.20)
find_package(Qt6 COMPONENTS Core)

find_package(Qt6 COMPONENTS Gui)
find_package(Qt6 COMPONENTS BuildInternals)
find_package(Qt6Core CONFIG REQUIRED Private)
find_package(Qt6Gui CONFIG REQUIRED Private)

include(Qt6Config)
include(QtBuild)
include(QtPluginHelpers)

# TODO figure out an out of tree build
# add_subdirectory(serenity)

message(FATAL_ERROR "This project can't be built on its own now, you need to insert the contents of the 'serenity' folder into {qtbase_dir}/src/plugins/platforms/serenity to build it")
