#
# Copyright (c) 2019 The C++ Alliance (https://cppalliance.org)
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Official repository: https://github.com/CPPAlliance/secure
#

source_group (TREE ${PROJECT_SOURCE_DIR}/include/boost/secure PREFIX secure FILES ${PROJECT_FILES})

GroupSources(test "/")

add_executable (secure-tests
    ${PROJECT_FILES}
    ${PROJECT_SOURCE_DIR}/src/src.cpp
    Jamfile
    main.cpp
    stream.cpp
)

add_test(secure-tests secure-tests)
