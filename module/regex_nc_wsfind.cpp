
#if defined(__cpp_lib_modules) || (defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 193933523))
#define BOOST_REGEX_USE_STD_MODULE
#endif

module boost.regex;

namespace boost::re_detail_600 {

   bool factory_find(perl_matcher<std::wstring::iterator, match_results<std::wstring::iterator>::allocator_type, wregex::traits_type>& m)
   {
      return m.find();
   }

}
