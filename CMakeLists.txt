cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

project(hls-service)

include_directories(include)

file(GLOB SOURCES
    include/*.h
    src/*.cpp
)

add_executable(hls-service ${SOURCES})

# target_link_libraries(HLS

# )
