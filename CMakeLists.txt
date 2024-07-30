cmake_minimum_required(VERSION 3.19)
enable_language(CXX)

project(qwtplot3d-zjk)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# -------------- Support C++17 for using filesystem  ------------------#
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network OpenGL Gui LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network OpenGL Gui LinguistTools)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
# Create code from a list of Qt designer ui files

# find_package(Qt5 COMPONENTS Widgets REQUIRED)
# find_package(Qt5 COMPONENTS Core REQUIRED)
# find_package(Qt5 COMPONENTS Gui REQUIRED)
# find_package(Qt5 COMPONENTS OpenGL REQUIRED)


file(GLOB SOURCES "src/*.cpp" "include/*.h")
add_library(${PROJECT_NAME} STATIC ${SOURCES})


target_link_libraries(${PROJECT_NAME} Qt${QT_MAJOR_VERSION}::Core)
target_link_libraries(${PROJECT_NAME} Qt${QT_MAJOR_VERSION}::Gui)
target_link_libraries(${PROJECT_NAME} Qt${QT_MAJOR_VERSION}::Widgets)

target_link_libraries(${PROJECT_NAME} Qt${QT_MAJOR_VERSION}::OpenGL)

target_link_libraries(${PROJECT_NAME} opengl32)

target_link_libraries(${PROJECT_NAME} glu32)

add_subdirectory(examples)

add_executable(split_main split_main.cc)
target_link_libraries(split_main Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
