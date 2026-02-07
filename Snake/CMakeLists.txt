cmake_minimum_required(VERSION 3.10)
project(Snake C)

# Set optimization flags for Release builds
if(CMAKE_BUILD_TYPE STREQUAL "Release")
  if(MSVC)
    # MSVC optimization flags
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /O2 /Oi /Ot /GL")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
  else()
    # GCC/Clang optimization flags
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -DNDEBUG")
  endif()
endif()

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

# On Windows, suppress console window in Release builds
if(WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Release")
  set_target_properties(Snake PROPERTIES
    WIN32_EXECUTABLE TRUE
  )
endif()

# include directories
target_include_directories(Snake PRIVATE ${GLFW_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# link libraries
target_link_libraries(Snake PRIVATE
  ${GLFW_LIB}
  ${CMAKE_DL_LIBS}
  ${CMAKE_THREAD_LIBS_INIT}
)

# on Linux we need additional libraries for OpenGL and X11
if (APPLE)
  target_link_libraries(Snake PRIVATE
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
    "-framework QuartzCore"
    "-framework Metal"
    "-framework OpenGL"
  )
elseif (UNIX)
  find_package(OpenGL REQUIRED)
  find_package(Threads REQUIRED)
  find_package(X11 REQUIRED)
  find_library(GL_LIB GL)
  find_library(X11_LIB X11)
  target_link_libraries(Snake PRIVATE
    ${GL_LIB}
    OpenGL::GL
    ${X11_LIB}
    Threads::Threads
    m # libm math library
    dl # dynamic loader
  )
  target_link_libraries(Snake PRIVATE OpenGL::GL)
elseif (WIN32)
  # Windows requires OpenGL and system libraries
  find_package(OpenGL REQUIRED)
  target_link_libraries(Snake PRIVATE
    OpenGL::GL
    gdi32
    user32
    shell32
  )
endif()
