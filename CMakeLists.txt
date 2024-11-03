cmake_minimum_required(VERSION 3.16)

project(DevTrack_Mini VERSION 0.1 LANGUAGES CXX)

# Enable automatic processing of UI, MOC, and RCC files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt packages
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# List project sources
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    constants.h
    newprojectdialog.h
    newprojectdialog.cpp
    newprojectdialog.ui
    overviewdetails.h
    overviewdetails.cpp
)

# Add executable or library based on Qt version and platform
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DevTrack_Mini
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(DevTrack_Mini SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(DevTrack_Mini
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Link Qt libraries
target_link_libraries(DevTrack_Mini PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Set properties for macOS bundle
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.DevTrack_Mini)
endif()
set_target_properties(DevTrack_Mini PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Include GNUInstallDirs for installation paths
include(GNUInstallDirs)
install(TARGETS DevTrack_Mini
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize executable for Qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DevTrack_Mini)
endif()

