
module;

#if defined(__cpp_lib_modules) || (defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 193933523))
#define BOOST_REGEX_USE_STD_MODULE
#endif

#ifndef BOOST_REGEX_DETAIL_NS
#define BOOST_REGEX_DETAIL_NS re_detail_600
#endif

#ifndef BOOST_REGEX_USE_STD_MODULE
#include <memory>
#endif

module boost.regex;

namespace boost::detail {

   std::shared_ptr<BOOST_REGEX_DETAIL_NS::basic_regex_implementation<char, basic_regex<char>::traits_type> >
      create_implemenation(const char* p1, const char* p2, basic_regex<char>::flag_type f, std::shared_ptr<boost::regex_traits_wrapper<basic_regex<char>::traits_type> > ptraits)
   {
      return create_implemenation<char, basic_regex<char>::flag_type, basic_regex<char>::traits_type>(p1, p2, f, ptraits);
   }

}
