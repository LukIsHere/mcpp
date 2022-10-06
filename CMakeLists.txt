# minimum CMake version required
cmake_minimum_required(VERSION 3.15)
project(mcpp VERSION 1.0)

#g++
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_subdirectory(libs/dpp)
add_subdirectory(libs/jpp)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/world.cpp 
    src/translation.cpp 
    src/emoji.cpp 
    src/blocks.cpp 
    src/skin.cpp 
    src/items.cpp
    src/interaction.cpp
    src/shop.cpp
    src/DB.cpp
    src/ranking.cpp
    src/money.cpp
)
target_link_libraries(${PROJECT_NAME}
    dpp
)
target_link_libraries(${PROJECT_NAME}
    jpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    libs/dpp/include
    libs/jpp/include
    include
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)