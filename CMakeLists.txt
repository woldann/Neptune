cmake_minimum_required(VERSION 3.10)
project(Neptune C)

set(NEPTUNE_MODULE_RULES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/modulerules)
set(NEPTUNE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(NEPTUNE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE NEPTUNE_HEADERS CONFIGURE_DEPENDS ${NEPTUNE_INCLUDE_DIR}/*.h)
file(GLOB_RECURSE NEPTUNE_SOURCES CONFIGURE_DEPENDS ${NEPTUNE_SOURCE_DIR}/*.c)

add_library(Neptune INTERFACE)

target_include_directories(Neptune INTERFACE ${NEPTUNE_INCLUDE_DIR})
target_include_directories(Neptune INTERFACE ${NEPTUNE_MODULE_RULES_DIR})
target_sources(Neptune INTERFACE ${NEPTUNE_SOURCES})

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(Neptune PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wshadow
        -Wformat=2
        -Wnull-dereference
        -Wdouble-promotion
        -Wcast-align
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(Neptune PRIVATE /W4 /permissive-)
endif()

set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

add_executable(logs ${TESTS_DIR}/logs.c)
target_link_libraries(logs PRIVATE Neptune)
target_compile_definitions(logs PRIVATE LOG_LEVEL_3 NEPTUNE_MODULERULES_HEADER="neptune_rules.h")
target_include_directories(logs PRIVATE ${NTHREAD_INCLUDE_DIR})
