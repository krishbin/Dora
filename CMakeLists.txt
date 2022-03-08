cmake_minimum_required( VERSION 3.0 )
project(Dora)

set(OpenGL_GL_PREFERENCE GLVND)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)
# Compile external dependencies 
add_subdirectory (Libraries)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Libraries/rpavlik-cmake-modules-fe2273")
include(CreateLaunchers)

configure_file(config/root_directory.h.in config/root_directory.h)

include_directories(
    Libraries/glfw-3.1.2/include/
	Libraries/glm-0.9.7.1/
	Libraries/glew-1.13.0/include/
    Libraries/stb_image/src/
	Libraries/assimp-3.0.1270/include/
    ${CMAKE_BINARY_DIR}/config
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_1130
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

add_executable(dora src/main.cpp
    common/shader.cpp
    common/shader.hpp
    common/texture.cpp
    common/texture.hpp
    common/controls.cpp
    common/controls.hpp
    common/mesh.h
    common/model.cpp
    common/model.hpp

    src/VertexShader.glsl
    src/FragmentShader.glsl
    src/vertexBuffer.cpp
    src/vertexBuffer.hpp
    src/indexBuffer.cpp
    src/indexBuffer.hpp
    src/polygons.cpp
    src/dijkstra.cpp
    src/dijkstra.hpp
)

target_link_libraries(dora 
    ${ALL_LIBS}
    assimp
    STB_IMAGE
)
