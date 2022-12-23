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
    GameLogic/Physics.cpp
    GameLogic/Physics.h
    GameLogic/InputHandler.cpp
    GameLogic/InputHandler.h
    GameLogic/GameRules.cpp
    GameLogic/GameRules.h
    GameObjects/GameObject.cpp
    GameObjects/GameObject.h
    GameObjects/CircleObject.cpp
    GameObjects/CircleObject.h
    GameObjects/Bat.cpp
    GameObjects/Bat.h
    GameObjects/Puck.cpp
    GameObjects/Puck.h
    GameObjects/Ai.cpp
    GameObjects/Ai.h
    SceneObjects/ShaderProgram.cpp
    SceneObjects/ShaderProgram.h
    SceneObjects/SceneObject.cpp
    SceneObjects/SceneObject.h
    SceneObjects/RenderObject.cpp
    SceneObjects/RenderObject.h
    SceneObjects/ComplexObject.cpp
    SceneObjects/ComplexObject.h
    SceneObjects/RoundedRectangle.cpp
    SceneObjects/RoundedRectangle.h
    SceneObjects/Circle.cpp
    SceneObjects/Circle.h
    SceneObjects/Rectangle.cpp
    SceneObjects/Rectangle.h
    SceneObjects/Ring.cpp
    SceneObjects/Ring.h
    )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(air_hockey
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(air_hockey
        ${PROJECT_SOURCES}
    )
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
    MACOSX_BUNDLE_EXECUTABLE_NAME "Air Hockey"
    MACOSX_BUNDLE TRUE

    XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2"
    XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER my.example.com
    XCODE_ATTRIBUTE_EXECUTABLE_NAME "Air Hockey"

    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(air_hockey)
endif()
