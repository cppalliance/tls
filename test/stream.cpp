//
// Copyright (c) 2019 The C++ Alliance (https://cppalliance.org)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/tls
//

// Test that header file is self-contained.
#include <boost/tls/stream.hpp>

#include <boost/asio/ssl/context.hpp>

#include <boost/beast/_experimental/unit_test/suite.hpp>

namespace boost {
namespace tls {

class stream_test : public beast::unit_test::suite
{
public:
    void
    testContext()
    {
        boost::asio::ssl::context ctx(ssl::context::tlsv12_client);
    }

    void
    run() override
    {
        testContext();
        pass();
    }
};

BEAST_DEFINE_TESTSUITE(boost,tls,stream);

} // tls
} // boost
