cmake_minimum_required(VERSION 3.16)
project(breakout)

set(CMAKE_CXX_STANDARD 14)

find_package(glfw3 3.3 REQUIRED)
#find_package(glm REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

file(GLOB src ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB vendor ${CMAKE_CURRENT_SOURCE_DIR}/vendor/*.c ${CMAKE_CURRENT_SOURCE_DIR}/vendor/*.cpp)
add_executable(breakout ${src} ${vendor})

target_include_directories(breakout PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/include/)
target_link_libraries(breakout PRIVATE glfw)

