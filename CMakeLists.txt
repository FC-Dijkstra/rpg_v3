cmake_minimum_required(VERSION 3.8)
project(rpg)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file (GLOB_RECURSE SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/*.cpp)

file (GLOB_RECURSE HEADER_FILES
        ${CMAKE_SOURCE_DIR}/src/*.h)

configure_file(src/helpers/RootDir.h.in src/helpers/RootDir.h)
include_directories(${CMAKE_BINARY_DIR}/src)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set (OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

set(LIB_PATH "${CMAKE_SOURCE_DIR}/include")

add_library(STB_IMAGE STATIC "${LIB_PATH}/stb_image/stb_image.cpp")
target_include_directories(STB_IMAGE INTERFACE "${LIB_PATH}/stb_image/")

add_library(GLAD STATIC "${LIB_PATH}/glad/glad.c" "${LIB_PATH}/glad/glad.h" "${LIB_PATH}/glad/khrplatform.h")
target_include_directories(GLAD PUBLIC "${LIB_PATH}/glad/")

add_library(NUKLEAR STATIC "${LIB_PATH}/Nuklear/nuklear.cpp")
target_include_directories(NUKLEAR INTERFACE "${LIB_PATH}/Nuklear")

add_library(IMGUI STATIC)
target_sources(
    IMGUI
    PRIVATE
    ${LIB_PATH}/ImGUI/imgui_demo.cpp
    ${LIB_PATH}/ImGUI/imgui_draw.cpp
    ${LIB_PATH}/ImGUI/imgui_tables.cpp
    ${LIB_PATH}/ImGUI/imgui_widgets.cpp
    ${LIB_PATH}/ImGUI/imgui.cpp
    ${LIB_PATH}/ImGUI/imgui_demo.cpp
    PRIVATE
    ${LIB_PATH}/ImGUI/imgui_impl_opengl3.h
    ${LIB_PATH}/ImGUI/imgui_impl_glfw.h
)
target_include_directories(IMGUI PUBLIC "${LIB_PARTH}/ImGUI/")

set(LIBS ${GLFW3_LIBRARY} ${OPENGL_LIBRARY} GLAD ${CMAKE_DL_LIBS} STB_IMAGE IMGUI)

include_directories(
        "${CMAKE_SOURCE_DIR}/src"
        "${CMAKE_SOURCE_DIR}/include"
        "${CMAKE_SOURCE_DIR}/include/glad"
        "${CMAKE_SOURCE_DIR}/include/glm"
        "/usr/local/include"
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBS})

if(MSVC_IDE)
    # Macro to preserve source files hierarchy in the IDE
    macro(GroupSources curdir)
        file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir} ${PROJECT_SOURCE_DIR}/${curdir}/*)

        foreach(child ${children})
            if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
                GroupSources(${curdir}/${child})
            else()
                string(REPLACE "/" "\\" groupname ${curdir})
                string(REPLACE "src" "Sources" groupname ${groupname})
                source_group(${groupname} FILES ${PROJECT_SOURCE_DIR}/${curdir}/${child})
            endif()
        endforeach()
    endmacro()

    # Run macro
    GroupSources(src)
endif()

# Copy dlls
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${PROJECT_SOURCE_DIR}/dll"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()

add_custom_command(
        TARGET rpg POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/src/shaders
                ${CMAKE_CURRENT_BINARY_DIR}/shaders
)