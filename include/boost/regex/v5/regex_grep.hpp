/*
 *
 * Copyright (c) 1998-2002
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         regex_grep.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Provides regex_grep implementation.
  */

#ifndef BOOST_REGEX_V5_REGEX_GREP_HPP
#define BOOST_REGEX_V5_REGEX_GREP_HPP

#include <boost/regex/v5/basic_regex.hpp>
#include <boost/regex/v5/match_flags.hpp>
#include <boost/regex/v5/match_results.hpp>
#include <boost/regex/v5/perl_matcher.hpp>

namespace boost{

//
// regex_grep:
// find all non-overlapping matches within the sequence first last:
//
BOOST_REGEX_MODULE_EXPORT template <class Predicate, class BidiIterator, class charT, class traits>
inline unsigned int regex_grep(Predicate foo, 
                               BidiIterator first, 
                               BidiIterator last, 
                               const basic_regex<charT, traits>& e, 
                               match_flag_type flags = match_default)
{
   if(e.flags() & regex_constants::failbit)
      return false;

   typedef typename match_results<BidiIterator>::allocator_type match_allocator_type;

   match_results<BidiIterator> m;
   BOOST_REGEX_DETAIL_NS::perl_matcher<BidiIterator, match_allocator_type, traits> matcher(first, last, m, e, flags, first);
   unsigned int count = 0;
   while(BOOST_REGEX_DETAIL_NS::factory_find(matcher))
   {
      ++count;
      if(0 == foo(m))
         return count; // caller doesn't want to go on
      if(m[0].second == last)
         return count; // we've reached the end, don't try and find an extra null match.
      if(m.length() == 0)
      {
         if(m[0].second == last)
            return count;
         // we found a NULL-match, now try to find
         // a non-NULL one at the same position:
         match_results<BidiIterator, match_allocator_type> m2(m);
         matcher.setf(match_not_null | match_continuous);
         if(BOOST_REGEX_DETAIL_NS::factory_find(matcher))
         {
            ++count;
            if(0 == foo(m))
               return count;
         }
         else
         {
            // reset match back to where it was:
            m = m2;
         }
         matcher.unsetf((match_not_null | match_continuous) & ~flags);
      }
   }
   return count;
}

//
// regex_grep convenience interfaces:
//
BOOST_REGEX_MODULE_EXPORT template <class Predicate, class charT, class traits>
inline unsigned int regex_grep(Predicate foo, const charT* str, 
                        const basic_regex<charT, traits>& e, 
                        match_flag_type flags = match_default)
{
   return regex_grep(foo, str, str + traits::length(str), e, flags);
}

BOOST_REGEX_MODULE_EXPORT template <class Predicate, class ST, class SA, class charT, class traits>
inline unsigned int regex_grep(Predicate foo, const std::basic_string<charT, ST, SA>& s, 
                 const basic_regex<charT, traits>& e, 
                 match_flag_type flags = match_default)
{
   return regex_grep(foo, s.begin(), s.end(), e, flags);
}

} // namespace boost

#endif  // BOOST_REGEX_V5_REGEX_GREP_HPP

