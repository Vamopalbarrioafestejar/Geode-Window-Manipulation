cmake_minimum_required(VERSION 3.21)
project(WindowFXTrigger VERSION 0.1.0)

if(NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "GEODE_SDK environment variable not set. Point it at your Geode SDK checkout.")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_BINARY_DIR}/geode)

file(GLOB SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

if(WIN32)
    target_link_libraries(${PROJECT_NAME} user32)
endif()

setup_geode_mod(${PROJECT_NAME})
