cmake_minimum_required(VERSION 3.10)
project(Snake C)

# find installed GLFW headers and libraries
find_path(
  GLFW_INCLUDE_DIR
  NAMES GLFW/glfw3.h
  HINTS ${GLFW_INCLUDE_DIR}
)
find_library(
  GLFW_LIB
  NAMES glfw3
  HINTS ${GLFW_LIB_DIR}
)

# source files
add_executable(Snake
  main.c
  include/glad/gl.c
  window.c
  game.c
  file.c
  images.c
  input.c
  point.c
  renderer.c
  shaders.c
  sprite.c
)

# include directories
target_include_directories(Snake PRIVATE ${GLFW_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# link libraries
target_link_libraries(Snake PRIVATE ${GLFW_LIB}
  ${CMAKE_DL_LIBS}
  ${CMAKE_THREAD_LIBS_INIT}
)

# on Linux we need additional libraries for OpenGL and X11
if (UNIX)
  find_package(OpenGL REQUIRED)
  find_package(X11 REQUIRED)
  find_library(GL_LIB GL)
  find_library(X11_LIB X11)
  target_link_libraries(Snake PRIVATE OpenGL::GL
    ${GL_LIB}
    ${X11_LIB}
  )
endif()
