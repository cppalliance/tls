//
// Copyright (c) 2019 The C++ Alliance (https://cppalliance.org)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/secure
//

// Test that header file is self-contained.
#include <boost/secure/stream.hpp>

#include <boost/beast/_experimental/unit_test/suite.hpp>

namespace boost {
namespace stream {

class stream_test : public beast::unit_test::suite
{
public:
    void
    run() override
    {
        pass();
    }
};

BEAST_DEFINE_TESTSUITE(boost,secure,stream);

} // json
} // boost
