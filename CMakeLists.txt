cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

project(hls-service)

include_directories("include")

file(GLOB SOURCES
    include/*.h
    src/*.cpp
)

find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(Threads REQUIRED)

add_executable(hls-service ${SOURCES})

target_link_libraries(hls-service PRIVATE
    Threads::Threads
    ${Boost_LIBRARIES}
)
target_include_directories(hls-service PRIVATE ${Boost_INCLUDE_DIRS})
