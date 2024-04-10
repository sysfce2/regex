
module;

#if defined(__cpp_lib_modules) || (defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 193933523))
#define BOOST_REGEX_USE_STD_MODULE
#endif

#if defined(_WIN32) && __has_include(<windows.h>)
#include <windows.h>
#endif

#if !defined(BOOST_REGEX_USE_STD_MODULE) && !defined(MSVC_EXPERIMENTAL_STD_MODULE)
#include <cassert>
#include <cstdint>
#include <climits>
#include <cctype>
#include <cstddef>
#include <cwctype>
#include <climits>
#include <cstring>

#include <vector>
#include <set>
#include <locale>
#include <type_traits>
#include <ios>
#include <istream>
#include <functional>
#include <iterator>
#include <new>
#include <atomic>
#include <memory>
#include <map>
#include <list>
#include <stdexcept>
#include <string>
#include <functional>
#include <algorithm>
#include <locale>
#include <limits>
#include <cstdint>
#include <sstream>
#include <ios>
#ifdef BOOST_HAS_THREADS
#include <mutex>
#endif
#include <cwctype>
#include <assert.h>
#endif

#if !defined(BOOST_REGEX_USE_STD_MODULE) && defined(MSVC_EXPERIMENTAL_STD_MODULE)
#include <cwchar>
#endif

#if __has_include(<unicode/utypes.h>)
#include <unicode/utypes.h>
#include <unicode/uchar.h>
#include <unicode/coll.h>
#endif

#define BOOST_REGEX_AS_MODULE
#define BOOST_REGEX_STANDALONE
#define BOOST_REGEX_MODULE_EXPORT export

export module boost.regex;

#if defined(BOOST_REGEX_USE_STD_MODULE)
import std;
#elif defined(MSVC_EXPERIMENTAL_STD_MODULE)
import std.core;
#endif

#ifdef _MSC_FULL_VER
#pragma warning(disable:5244)
#endif

#include <boost/regex.hpp>

#if __has_include(<unicode/utypes.h>)
#include <boost/regex/icu.hpp>
#endif
