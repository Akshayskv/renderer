cmake_minimum_required(VERSION 3.24.0)


project(renderer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 QUIET)

if(NOT glfw3_FOUND)
    message("glfw not found! fetching from github...")
    include(FetchContent)

    #set build options
    set(GLFW_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_USE_WAYLAND ON CACHE BOOL "" FORCE)
    
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.9
    )

    FetchContent_MakeAvailable(glfw)
else()
    set(GLFW_TARGET glfw3::glfw)
endif()

add_executable(renderer)

file(GLOB src_files "src/*.cpp")
target_sources(renderer PRIVATE ${src_files})
target_include_directories(renderer PRIVATE "includes/")
target_link_libraries(renderer PRIVATE glfw)