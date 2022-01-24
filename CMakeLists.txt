cmake_minimum_required(VERSION 3.6)
project(OpenGLRay VERSION 1.0)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ")
#set (CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS}")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -flto -ftree-vectorize -march=native -O3 -mtune=generic")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -Wall -Wextra")
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

set(cimgui cimgui)
set(imgui_impl ${cimgui}/imgui/impl)
include_directories(
	src
	${cimgui} 
	${cimgui}/imgui ${imgui_impl}
    ${klib}
    )

file(GLOB 
	cimgui_files 
	"${cimgui}/*.cpp" 
	"${cimgui}/imgui/*.cpp"
	"${imgui_impl}/imgui_impl_glfw.cpp"
	"${imgui_impl}/imgui_impl_opengl3.cpp")
    add_library(cimgui ${cimgui_files})
    
    target_compile_definitions(cimgui PRIVATE 
	IMGUI_IMPL_API=extern\ \"C\"
	IMGUI_IMPL_OPENGL_LOADER_GLAD)
    
    
    file(GLOB SOURCES "src/render/*.c" "src/logic/*.c" "src/glad.c")
    
    add_executable(OpenGLRay src/main.c ${SOURCES})
    
    target_compile_definitions(OpenGLRay PRIVATE IMGUI_IMPL_API=\ )

    target_include_directories(OpenGLRay PRIVATE /include)
    
    target_link_libraries(OpenGLRay ${OPENGL_gl_LIBRARY} glfw3 dl m pthread cimgui)
    
    file(COPY ${CMAKE_CURRENT_LIST_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})