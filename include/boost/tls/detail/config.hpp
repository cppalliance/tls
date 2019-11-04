//
// Copyright (c) 2019 The C++ Alliance (https://cppalliance.org)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/tls
//

#ifndef BOOST_TLS_CONFIG_HPP
#define BOOST_TLS_CONFIG_HPP

#include <boost/config.hpp>

#if defined(GENERATING_DOCUMENTATION)
# define BOOST_TLS_DECL
#elif defined(BOOST_TLS_HEADER_ONLY)
# define BOOST_TLS_DECL  inline
#else
# if (defined(BOOST_TLS_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)) && !defined(BOOST_TLS_STATIC_LINK)
#  if defined(BOOST_TLS_SOURCE)
#   define BOOST_TLS_DECL  BOOST_SYMBOL_EXPORT
#   define BOOST_TLS_BUILD_DLL
#  else
#   define BOOST_TLS_DECL  BOOST_SYMBOL_IMPORT
#  endif
# endif // shared lib
# ifndef  BOOST_TLS_DECL
#  define BOOST_TLS_DECL
# endif
# if !defined(BOOST_TLS_SOURCE) && !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_TLS_NO_LIB)
#  define BOOST_LIB_NAME boost_tls
#  if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_TLS_DYN_LINK)
#   define BOOST_DYN_LINK
#  endif
#  include <boost/config/auto_link.hpp>
# endif  // auto-linking disabled
#endif

namespace boost {
namespace asio {
namespace ssl {
} // ssl
} // asio
namespace tls {
namespace net = boost::asio;
namespace ssl = boost::asio::ssl;
} // beast
} // boost

#endif
