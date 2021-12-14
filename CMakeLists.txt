# Generated from minimal.pro.

project(QSerenityIntegrationPluginProject)
cmake_minimum_required(VERSION 3.20)
find_package(Qt6 COMPONENTS Core)

find_package(Qt6 COMPONENTS Gui)
find_package(Qt6 COMPONENTS BuildInternals)
find_package(Qt6Core CONFIG REQUIRED Private)
find_package(Qt6Gui CONFIG REQUIRED Private)

include(Qt6Config)
include(QtBuild)
include(QtPluginHelpers)

set(CXX_STANDARD 20)

add_subdirectory(serenity)
