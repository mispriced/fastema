project(fastemaTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(fastema REQUIRED)
  find_package(Catch2 REQUIRED)
  enable_testing()
endif()

# ---- Tests ----

add_executable(fastema_test src/fastema_test.cpp)
target_include_directories(fastema_test PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(fastema_test PRIVATE fastema::fastema Catch2::Catch2WithMain)
target_compile_features(fastema_test PRIVATE cxx_std_20)

add_test(NAME fastema_test COMMAND fastema_test)

# ---- End-of-file commands ----

add_folders(Test)