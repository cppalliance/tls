//
// Copyright (c) 2019 The C++ Alliance (https://cppalliance.org)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/secure
//

#ifndef BOOST_SECURE_CONFIG_HPP
#define BOOST_SECURE_CONFIG_HPP

#include <boost/config.hpp>

#if defined(GENERATING_DOCUMENTATION)
# define BOOST_SECURE_DECL
#elif defined(BOOST_SECURE_HEADER_ONLY)
# define BOOST_SECURE_DECL  inline
#else
# if (defined(BOOST_SECURE_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)) && !defined(BOOST_SECURE_STATIC_LINK)
#  if defined(BOOST_SECURE_SOURCE)
#   define BOOST_SECURE_DECL  BOOST_SYMBOL_EXPORT
#   define BOOST_SECURE_BUILD_DLL
#  else
#   define BOOST_SECURE_DECL  BOOST_SYMBOL_IMPORT
#  endif
# endif // shared lib
# ifndef  BOOST_SECURE_DECL
#  define BOOST_SECURE_DECL
# endif
# if !defined(BOOST_SECURE_SOURCE) && !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_SECURE_NO_LIB)
#  define BOOST_LIB_NAME boost_json
#  if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_SECURE_DYN_LINK)
#   define BOOST_DYN_LINK
#  endif
#  include <boost/config/auto_link.hpp>
# endif  // auto-linking disabled
#endif

#endif
