cmake_minimum_required(VERSION 3.16)
project(SDL3_CrossPlatform_App C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(WIN32)
    set(SDL3_DIR "C:/SDL3/lib/cmake/SDL3")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
endif()

find_package(SDL3 REQUIRED)

file(GLOB SOURCES "src/*.c")
add_executable(main ${SOURCES})

target_link_libraries(main PRIVATE SDL3::SDL3)
