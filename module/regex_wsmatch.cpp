
module;

#if defined(__cpp_lib_modules) || (defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 193833135))
#define BOOST_REGEX_USE_STD_MODULE
#endif

#if !defined(BOOST_REGEX_USE_STD_MODULE) && !defined(MSVC_EXPERIMENTAL_STD_MODULE)
#include <string>
#endif

module boost.regex;

#if !defined(BOOST_REGEX_USE_STD_MODULE) && defined(MSVC_EXPERIMENTAL_STD_MODULE)
import std.core;
#endif

namespace boost::re_detail_600 {

   bool factory_match(perl_matcher<std::wstring::const_iterator, match_results<std::wstring::const_iterator>::allocator_type, wregex::traits_type>& m)
   {
      return m.match();
   }

}
