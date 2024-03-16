cmake_minimum_required(VERSION 3.27)
project(FallingSandSim)

set(CMAKE_CXX_STANDARD 23)

add_executable(FallingSandSim main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_DIR C:/cpplibraries/SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.1/lib/cmake/SFML)

find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/cpplibraries/SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.1/include)
target_link_libraries(FallingSandSim sfml-graphics sfml-window sfml-system sfml-audio sfml-network)

# Add ImGui
set(IMGUI_DIR C:/cpplibraries/imgui-master/imgui-master)
add_library(imgui
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
)
target_include_directories(imgui PUBLIC ${IMGUI_DIR})

# Add ImGui-SFML
set(IMGUI_SFML_DIR C:/cpplibraries/imgui-sfml-2.6.x/imgui-sfml-2.6.x)
add_library(imgui-sfml
        ${IMGUI_SFML_DIR}/imgui-SFML.cpp
)
target_include_directories(imgui-sfml PUBLIC ${IMGUI_SFML_DIR})
target_link_libraries(imgui-sfml imgui sfml-graphics sfml-window sfml-system)

# Link ImGui and ImGui-SFML to your executable
target_link_libraries(FallingSandSim imgui imgui-sfml)