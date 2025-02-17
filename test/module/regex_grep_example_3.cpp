/*
 *
 * Copyright (c) 1998-2022
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         regex_grep_example_3.cpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: regex_grep example 3: searches a cpp file for class definitions,
  *                using a bound member function callback.
  */

#if (defined(__cpp_lib_modules) || (defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 193833135))) && !defined(TEST_HEADERS)
import std;
#elif defined(MSVC_EXPERIMENTAL_STD_MODULE) && !defined(TEST_HEADERS)
import std.core;
#else
#include <string>
#include <map>
#include <functional>
#include <iostream>
#include <fstream>
#endif

#ifdef TEST_HEADERS
#include <boost/regex.hpp>
#else
import boost.regex;
#endif

// purpose:
// takes the contents of a file in the form of a string
// and searches for all the C++ class definitions, storing
// their locations in a map of strings/int's

typedef std::map<std::string, std::string::difference_type, std::less<std::string> > map_type;

const char* re = 
   // possibly leading whitespace:   
   "^[[:space:]]*" 
   // possible template declaration:
   "(template[[:space:]]*<[^;:{]+>[[:space:]]*)?"
   // class or struct:
   "(class|struct)[[:space:]]*" 
   // leading declspec macros etc:
   "("
      "\\<\\w+\\>"
      "("
         "[[:blank:]]*\\([^)]*\\)"
      ")?"
      "[[:space:]]*"
   ")*" 
   // the class name
   "(\\<\\w*\\>)[[:space:]]*" 
   // template specialisation parameters
   "(<[^;:{]+>)?[[:space:]]*"
   // terminate in { or :
   "(\\{|:[^;\\{()]*\\{)";


class class_index
{
   boost::regex expression;
   map_type index;
   std::string::const_iterator base;

   bool grep_callback(boost::match_results<std::string::const_iterator> what);
public:
   map_type& get_map() { return index; }
   void IndexClasses(const std::string& file);
   class_index()
      : expression(re) {}
};

bool class_index::grep_callback(boost::match_results<std::string::const_iterator> what)
{
   // what[0] contains the whole string
   // what[5] contains the class name.
   // what[6] contains the template specialisation if any.
   // add class name and position to map:
   index[std::string(what[5].first, what[5].second) + std::string(what[6].first, what[6].second)] =
               what[5].first - base;
   return true;
}

void class_index::IndexClasses(const std::string& file)
{
   std::string::const_iterator start, end;
   start = file.begin();
   end = file.end();
   base = start;
   boost::regex_grep([&](boost::match_results<std::string::const_iterator>const & what)->bool { return this->grep_callback(what); },
            start,
            end,
            expression);
}

using namespace std;

void load_file(std::string& s, std::istream& is)
{
   s.erase();
   if(is.bad()) return;
   s.reserve(static_cast<std::string::size_type>(is.rdbuf()->in_avail()));
   char c;
   while(is.get(c))
   {
      if(s.capacity() == s.size())
         s.reserve(s.capacity() * 3);
      s.append(1, c);
   }
}

int main(int argc, const char** argv)
{
   std::string text;
   for(int i = 1; i < argc; ++i)
   {
      cout << "Processing file " << argv[i] << endl;
      std::ifstream fs(argv[i]);
      load_file(text, fs);
      fs.close();
      class_index idx;
      idx.IndexClasses(text);
      cout << idx.get_map().size() << " matches found" << endl;
      map_type::iterator c, d;
      c = idx.get_map().begin();
      d = idx.get_map().end();
      while(c != d)
      {
         cout << "class \"" << (*c).first << "\" found at index: " << (*c).second << endl;
         ++c;
      }
   }
   return 0;
}

