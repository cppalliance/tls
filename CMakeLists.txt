#
# Copyright (c) 2019 The C++ Alliance (https://cppalliance.org)
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Official repository: https://github.com/CPPAlliance/secure
#

cmake_minimum_required (VERSION 3.5.1)

if (POLICY CMP0074)
    cmake_policy (SET CMP0074 NEW)
endif()

#-------------------------------------------------------------------------------

function (DoGroupSources curdir rootdir folder)
    file (GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir} ${PROJECT_SOURCE_DIR}/${curdir}/*)
    foreach (child ${children})
        if (IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
            DoGroupSources (${curdir}/${child} ${rootdir} ${folder})
        elseif (${child} STREQUAL "CMakeLists.txt")
            source_group("" FILES ${PROJECT_SOURCE_DIR}/${curdir}/${child})
        else()
            string (REGEX REPLACE ^${rootdir} ${folder} groupname ${curdir})
            string (REPLACE "/" "\\" groupname ${groupname})
            source_group (${groupname} FILES ${PROJECT_SOURCE_DIR}/${curdir}/${child})
        endif()
    endforeach()
endfunction()

function (GroupSources curdir folder)
    DoGroupSources (${curdir} ${curdir} ${folder})
endfunction()

#-------------------------------------------------------------------------------
#
# TLS
#
#-------------------------------------------------------------------------------

project (TLS VERSION 1)

set_property (GLOBAL PROPERTY USE_FOLDERS ON)

if (MSVC)
    set (CMAKE_VERBOSE_MAKEFILE FALSE)

    add_definitions (
        -D_WIN32_WINNT=0x0601
        -D_CRT_TLS_NO_WARNINGS
    )

    add_compile_options(
        /permissive-  # strict C++
        /W4           # enable all warnings
        /MP           # Multi-processor compilation
        )

    add_link_options(
        /INCREMENTAL:NO
    )

    set (Boost_USE_STATIC_LIBS ON)
    set (Boost_USE_STATIC_RUNTIME ON)

    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Ob2 /Oi /Ot /GL /MT")
    set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /Oi /Ot /MT")

    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")
    set (CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")

    # for RelWithDebInfo builds, disable incremental linking
    # since CMake sets it ON by default for that build type and it
    # causes warnings
    #
    string (REPLACE "/INCREMENTAL" "/INCREMENTAL:NO" replacement_flags
        ${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO})
    set (CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO ${replacement_flags})

else()
    set (THREADS_PREFER_PTHREAD_FLAG ON)
    find_package (Threads)

    set( CMAKE_CXX_FLAGS
      "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wpedantic -Wno-unused-parameter")

    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wrange-loop-analysis")
    endif ()
endif()

# Must come before Boost includes, otherwise the
# IDE sees the wrong file due to boost/ symlinks.
include_directories (include)

#-------------------------------------------------------------------------------
#
# OpenSSL
#
#-------------------------------------------------------------------------------

if (APPLE AND NOT DEFINED ENV{OPENSSL_ROOT_DIR})
  find_program(HOMEBREW brew)
  if (NOT HOMEBREW STREQUAL "HOMEBREW-NOTFOUND")
    execute_process(COMMAND brew --prefix openssl
      OUTPUT_VARIABLE OPENSSL_ROOT_DIR
      OUTPUT_STRIP_TRAILING_WHITESPACE)
  endif()
endif()

find_package(OpenSSL)

include_directories (${OPENSSL_INCLUDE_DIR})
link_libraries (${OPENSSL_LIBRARIES})

#-------------------------------------------------------------------------------
#
# Boost
#
#-------------------------------------------------------------------------------

get_filename_component (BOOST_ROOT ../../ ABSOLUTE)

# VFALCO I want static but "b2 stage" builds a minimal set which excludes static
add_definitions (-DBOOST_ALL_STATIC_LINK=1)

include_directories (${BOOST_ROOT})

link_directories(${BOOST_ROOT}/stage/lib)

#-------------------------------------------------------------------------------
#
# Static Libraries
#
#-------------------------------------------------------------------------------

add_definitions (-DBOOST_ASIO_SEPARATE_COMPILATION=1)
add_definitions (-DBOOST_BEAST_SEPARATE_COMPILATION=1)

add_library (
    lib-asio STATIC
    test/lib_asio.cpp
)

set_property(TARGET lib-asio PROPERTY FOLDER "static-libs")

add_library (
    lib-beast STATIC
    test/lib_beast.cpp
)

set_property(TARGET lib-beast PROPERTY FOLDER "static-libs")

target_link_libraries(lib-asio lib-beast)

#-------------------------------------------------------------------------------

if ("${VARIANT}" STREQUAL "debug")
    set (CMAKE_BUILD_TYPE DEBUG)

elseif ("${VARIANT}" STREQUAL "release")
    set (CMAKE_BUILD_TYPE RELEASE)

endif()

#-------------------------------------------------------------------------------
#
# Tests and examples
#

#GroupSources (test "/")

add_definitions(-DBOOST_TLS_HEADER_ONLY=1)

file (GLOB_RECURSE PROJECT_FILES
    ${PROJECT_SOURCE_DIR}/include/boost/tls/*.hpp
    ${PROJECT_SOURCE_DIR}/include/boost/tls/*.ipp
)

add_subdirectory (test)
