cmake_minimum_required(VERSION 3.19)


get_filename_component(current_directory_name "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
message("Current directory name: ${current_directory_name}")

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(${current_directory_name} ${SOURCES})

target_link_libraries(${current_directory_name} Qt${QT_MAJOR_VERSION}::Core Qt${QT_MAJOR_VERSION}::Gui Qt${QT_MAJOR_VERSION}::Widgets)
target_link_libraries(${current_directory_name} qwtplot3d-zjk)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})