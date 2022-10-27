# minimum CMake version required
cmake_minimum_required(VERSION 3.15)
project(mcpp VERSION 1.0)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # using Clang
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using GCC
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  # using Intel C++
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # using Visual Studio C++
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

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
    src/inventory.cpp
    src/shop.cpp
    src/DB.cpp
    src/ranking.cpp
    src/money.cpp
    src/api.cpp
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