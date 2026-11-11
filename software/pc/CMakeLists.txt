
cmake_minimum_required(VERSION 3.22)

project(XiangqiPC LANGUAGES C CXX)

# 使用 C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 下载 raylib
include(FetchContent) 

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 6.2
    GIT_SHALLOW TRUE
)

# 不编译 raylib 自带的示例
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(raylib)

# 创建我们的程序
add_executable(xiangqi_pc
    src/main.cpp
    src/BoardView.cpp
)
target_include_directories(xiangqi_pc PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
# 链接 raylib
target_link_libraries(xiangqi_pc PRIVATE raylib)
