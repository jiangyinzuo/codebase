cmake_minimum_required(VERSION 3.16)

project(codebase_cpp LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
-Werror \
-Wall -Wextra -Wnon-virtual-dtor -Wpedantic \
-Wunused -Wshadow -Woverloaded-virtual")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1 -fsanitize=address")

file(GLOB_RECURSE SRC src/*.cpp)

foreach (src ${SRC})
    # Create a human readable name.
    get_filename_component(src_file_path ${src} NAME)
    string(REPLACE ".cpp" "" src_file_name ${src_file_path})
    add_executable(${src_file_name} ${src})
endforeach (src ${SRC})
