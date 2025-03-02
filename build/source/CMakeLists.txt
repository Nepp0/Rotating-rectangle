cmake_minimum_required(VERSION 3.10)
project(YourProjectName)

# Use pkg-config to find libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW3 REQUIRED glfw3)
pkg_check_modules(GLEW REQUIRED glew)
find_package(glad REQUIRED)
include_directories(${CMAKE_SOURCE_DIR}/include)
add_library(glad ${CMAKE_SOURCE_DIR}/src/glad.c)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Add your source files
add_executable(main main.cpp)

# Include directories
target_include_directories(main PRIVATE
  ${GLEW_INCLUDE_DIRS}
  ${GLFW3_INCLUDE_DIRS}
)

# Link Glad and OpenGL to your executable
target_link_libraries(MyOpenGLApp glad ${OPENGL_LIBRARIES} glfw) # glfw is optional


# Link libraries
target_link_libraries(main PRIVATE
  OpenGL::GL
  ${GLEW_LIBRARIES}
  ${GLFW3_LIBRARIES}
)
