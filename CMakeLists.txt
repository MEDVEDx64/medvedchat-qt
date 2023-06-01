cmake_minimum_required(VERSION 3.10)

project("medvedchat-qt")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

message("Looking for Qt...")
find_package(Qt5 REQUIRED Widgets Network)
if (${Qt5_FOUND})
    message("Found Qt "${Qt5_VERSION})
else()
    message("Couldn't find Qt")
endif()

set(sources
    protocol.cpp
    client.cpp
    value.cpp
    mainwindow.cpp
    main.cpp
    )

add_executable(${CMAKE_PROJECT_NAME} WIN32 ${sources})

target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    Qt5::Widgets
    Qt5::Network
    )
