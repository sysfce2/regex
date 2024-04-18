
#if defined(__cpp_lib_modules) || (defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 193933523))
#define BOOST_REGEX_USE_STD_MODULE
#endif

module boost.regex;

namespace boost::re_detail_600 {

   bool factory_match(perl_matcher<std::wstring::const_iterator, match_results<std::wstring::const_iterator>::allocator_type, wregex::traits_type>& m)
   {
      return m.match();
   }

}
