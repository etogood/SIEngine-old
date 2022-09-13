cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(Assimp)

add_library(assimp SHARED IMPORTED GLOBAL)
set_property(TARGET assimp PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_DIR}/lib/assimp-vc143-mtd.dll")
set_property(TARGET assimp PROPERTY IMPORTED_IMPLIB "${CMAKE_CURRENT_DIR}/lib/assimp-vc143-mtd.lib")
target_include_directories(assimp INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)