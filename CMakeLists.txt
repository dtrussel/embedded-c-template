cmake_minimum_required(VERSION 3.11)

project(mbed VERSION 2021.1)

#####################################################################
# DEPENDENCIES
#####################################################################

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR}
    EXCLUDE_FROM_ALL)
endif()

#####################################################################
# LIBRARY
#####################################################################

if(NOT MBED_DISABLE_CHECKS)
set(CMAKE_C_CLANG_TIDY "clang-tidy;-checks=-*,bugprone-*")
set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=-*,bugprone-*")
set(CMAKE_C_CPPCHECK "cppcheck;--enable=style")
set(CMAKE_CPP_CPPCHECK "cppcheck;--enable=style")
set(CMAKE_C_CPPLINT "cpplint;--verbose=5")
set(CMAKE_CXX_CPPLINT "cpplint;--verbose=5")
endif()

add_library(${PROJECT_NAME} STATIC
  src/mbed/containers/queue.c
  src/mbed/hash/crc32lookup.c)

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION})

target_include_directories(${PROJECT_NAME}
  PUBLIC include
  PRIVATE src)

target_compile_options(${PROJECT_NAME}
  PRIVATE ${MBED_FLAGS})

target_compile_features(${PROJECT_NAME}
  PRIVATE c_std_11)

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
  EXPORT MbedTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#####################################################################
# UNIT TESTS
#####################################################################

if(NOT MBED_DISABLE_TESTS)

add_executable(${PROJECT_NAME}-tests
  test/containers/queue.cpp
  test/hash/crc32lookup.cpp)

target_link_libraries(${PROJECT_NAME}-tests
  PRIVATE gtest_main ${PROJECT_NAME}::${PROJECT_NAME})

target_compile_options(${PROJECT_NAME}-tests
  PRIVATE ${MBED_FLAGS})

target_compile_features(${PROJECT_NAME}
  PRIVATE cxx_std_17)

add_test(NAME ${PROJECT_NAME}-test COMMAND ${PROJECT_NAME}-tests)

endif()
