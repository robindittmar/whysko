cmake_minimum_required(VERSION 3.24)
project(whysko)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(SFML)

add_subdirectory(src)


target_link_libraries(whysko sfml-window sfml-graphics)
