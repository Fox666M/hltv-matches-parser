cmake_minimum_required(VERSION 3.15)
project(HLTV_Parser)

set(CMAKE_CXX_STANDARD 17)

# Ищем пакеты
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(CURL REQUIRED)

# Добавляем пути к заголовочным файлам 
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/table)

# Исходники
add_executable(db_engine 
    main.cpp 
    imgui/imgui.cpp 
    imgui/imgui_demo.cpp 
    imgui/imgui_draw.cpp 
    imgui/imgui_tables.cpp 
    imgui/imgui_widgets.cpp
    imgui/imgui_impl_glfw.cpp 
    imgui/imgui_impl_opengl3.cpp
)

target_link_libraries(db_engine PRIVATE glfw OpenGL::GL CURL::libcurl)