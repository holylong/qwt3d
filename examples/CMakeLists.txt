cmake_minimum_required(VERSION 3.19)

project(examples)


# 定义一个函数，用于查找并递归添加含有 CMakeLists.txt 的子目录
function(add_cmakelists_subdirectories)
    # 添加子目录
    file(GLOB_RECURSE sub_dirs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} */CMakeLists.txt)

    foreach(sub_dir ${sub_dirs})
      get_filename_component(dir ${sub_dir} DIRECTORY)
      add_subdirectory(${dir})
    endforeach()
endfunction()

add_cmakelists_subdirectories()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})