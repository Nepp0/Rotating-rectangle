cmake_minimum_required(VERSION 3.10)
project(YourProjectName)

# Use pkg-config to find libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW3 REQUIRED glfw3)
pkg_check_modules(GLEW REQUIRED glew)

find_package(OpenGL REQUIRED)

# Add your source files
add_executable(main main.cpp)

# Include directories
target_include_directories(main PRIVATE
  ${GLEW_INCLUDE_DIRS}
  ${GLFW3_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(main PRIVATE
  OpenGL::GL
  ${GLEW_LIBRARIES}
  ${GLFW3_LIBRARIES}
)
