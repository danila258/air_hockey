cmake_minimum_required(VERSION 3.5)

project(air_hockey VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Gui OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Gui OpenGLWidgets)

qt_add_resources(RESOURCES Resources.qrc)

set(PROJECT_SOURCES
    ${RESOURCES}
    GameLogic/main.cpp
    GameLogic/GameWindow.cpp
    GameLogic/GameWindow.h
    GameLogic/InputHandler.cpp
    GameLogic/InputHandler.h
    GameLogic/Physics.cpp
    GameLogic/Physics.h
    GameObjects/GameObject.cpp
    GameObjects/GameObject.h
    GameObjects/Bat.cpp
    GameObjects/Bat.h
    RenderObjects/ShaderProgram.cpp
    RenderObjects/ShaderProgram.h
    RenderObjects/SceneObject.cpp
    RenderObjects/SceneObject.h
    RenderObjects/RenderObject.cpp
    RenderObjects/RenderObject.h
    RenderObjects/ComplexObject.cpp
    RenderObjects/ComplexObject.h
    RenderObjects/RoundedRectangle.cpp
    RenderObjects/RoundedRectangle.h
    RenderObjects/Circle.cpp
    RenderObjects/Circle.h
    RenderObjects/Rectangle.cpp
    RenderObjects/Rectangle.h
    RenderObjects/Ring.cpp
    RenderObjects/Ring.h
    )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(air_hockey
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET air_hockey APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(air_hockey SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(air_hockey
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(air_hockey PRIVATE
                      Qt${QT_VERSION_MAJOR}::Widgets
                      Qt${QT_VERSION_MAJOR}::Gui
                      Qt${QT_VERSION_MAJOR}::OpenGLWidgets
                      )

set_target_properties(air_hockey PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE_EXECUTABLE_NAME Vega
    MACOSX_BUNDLE TRUE

    XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2"
    XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER my.example.com
    XCODE_ATTRIBUTE_EXECUTABLE_NAME Vega

    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(air_hockey)
endif()
