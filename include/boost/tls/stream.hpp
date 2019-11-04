//
// Copyright (c) 2019 The C++ Alliance (https://cppalliance.org)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/tls
//

#ifndef BOOST_TLS_STREAM_HPP
#define BOOST_TLS_STREAM_HPP

#include <boost/tls/detail/config.hpp>

namespace boost {
namespace tls {

template<class NextLayer>
class stream
{
public:
};

BOOST_TLS_DECL
int
forty_two() noexcept;

} // tls
} // boost

#ifdef BOOST_TLS_HEADER_ONLY
#include <boost/tls/impl/stream.ipp>
#endif

#endif
