# Copyright (c) 2013, David Keller
# All rights reserved.
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of the University of California, Berkeley nor the
#       names of its contributors may be used to endorse or promote products
#       derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY DAVID KELLER AND CONTRIBUTORS ``AS IS AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
cmake_minimum_required(VERSION 3.5)

project(
    kademlia

    VERSION
        0.0.0
    LANGUAGES
        CXX)

set_property(
    DIRECTORY
    APPEND
    PROPERTY
        COMPILE_DEFINITIONS
            PACKAGE_VERSION="${PROJECT_VERSION}"
            PACKAGE_BUGREPORT="David Keller <david.keller@litchis.fr>"
            $<$<CONFIG:Debug>:KADEMLIA_ENABLE_DEBUG>)

find_package(
    Threads

    REQUIRED)

set(Boost_USE_STATIC_LIBS "${WIN32}")
find_package(
    Boost

    REQUIRED
    COMPONENTS
        system
        filesystem
        unit_test_framework)

set_property(
    DIRECTORY
    APPEND
    PROPERTY
        COMPILE_DEFINITIONS
            $<$<NOT:$<BOOL:${Boost_USE_STATIC_LIBS}>>:BOOST_ALL_DYN_LINK>
            BOOST_ASIO_HAS_MOVE
            BOOST_ASIO_HAS_VARIADIC_TEMPLATES
            BOOST_ASIO_HAS_STD_SYSTEM_ERROR
            BOOST_ASIO_HAS_STD_ARRAY
            BOOST_ASIO_HAS_STD_SHARED_PTR
            BOOST_ASIO_HAS_STD_ATOMIC
            BOOST_ASIO_HAS_STD_CHRONO)

find_package(
    OpenSSL

    REQUIRED)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(
    DIRECTORY PROPERTY
        COMPILE_OPTIONS
            -Wall)

add_subdirectory(include)
add_subdirectory(src)

include(CTest)
if(BUILD_TESTING)
    enable_testing()

    add_subdirectory(test)
endif()
