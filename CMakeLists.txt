cmake_minimum_required( VERSION 3.0 )
project(Dora)
set(OpenGL_GL_PREFERENCE GLVND)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)

find_package(GLEW REQUIRED)

include_directories(
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
    ${GLEW_LIBRARIES}
	glfw
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

    src/VertexShader.glsl
    src/FragmentShader.glsl
    src/vertexBuffer.cpp
    src/vertexBuffer.hpp
    src/indexBuffer.cpp
    src/indexBuffer.hpp
    src/polygons.cpp
    src/polygons.hpp
)

target_link_libraries(dora 
    ${ALL_LIBS}
)
