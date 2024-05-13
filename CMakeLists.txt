cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    fastema
    VERSION 0.1.0
    DESCRIPTION "Fast powers of 2 exponentional moving average filter leveraging unsigneds"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(fastema_fastema INTERFACE)
add_library(fastema::fastema ALIAS fastema_fastema)

set_property(
    TARGET fastema_fastema PROPERTY
    EXPORT_NAME fastema
)

target_include_directories(
  fastema_fastema ${warning_guard}
  INTERFACE
  "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_compile_features(fastema_fastema INTERFACE cxx_std_20)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Benchmarks ----

if(PROJECT_IS_TOP_LEVEL)
  option(BUILD_BENCHMARKS "Build benchmarks tree." "${fastema_DEVELOPER_MODE}")
  if(BUILD_BENCHMARKS)
    add_subdirectory(benchmark)
  endif()
endif()

# ---- Developer mode ----

if(NOT fastema_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of fastema"
  )
endif()

include(cmake/dev-mode.cmake)
