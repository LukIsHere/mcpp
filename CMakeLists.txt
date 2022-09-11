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
add_subdirectory(libs/lsudms)

add_executable(${PROJECT_NAME}
    main.cpp world.cpp translation.cpp emoji.cpp blocks.cpp
)
target_link_libraries(${PROJECT_NAME}
    lsudms
)

target_link_libraries(${PROJECT_NAME}
    dpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    libs/dpp/include
    libs/lsudms/include
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)