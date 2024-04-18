
#if defined(__cpp_lib_modules) || (defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 193933523))
#define BOOST_REGEX_USE_STD_MODULE
#endif

#ifndef BOOST_REGEX_USE_STD_MODULE
module;

#include <string>

#endif

module boost.regex;

#ifdef BOOST_REGEX_USE_STD_MODULE
import std;
#endif

namespace boost::re_detail_600 {

   bool factory_match(perl_matcher<std::string::const_iterator, match_results<std::string::const_iterator>::allocator_type, regex::traits_type>& m)
   {
      return m.match();
   }

}
