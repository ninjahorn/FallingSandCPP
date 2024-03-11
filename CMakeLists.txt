cmake_minimum_required(VERSION 3.27)
project(FallingSandSim)

set(CMAKE_CXX_STANDARD 23)

add_executable(FallingSandSim main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/cpplibraries/SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/cpplibraries/SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.1/include)
target_link_libraries(FallingSandSim sfml-graphics sfml-window sfml-system sfml-audio sfml-network)