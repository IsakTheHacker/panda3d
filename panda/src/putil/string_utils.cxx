// Filename: string_utils.cxx
// Created by:  drose (18Jan99)
// 
////////////////////////////////////////////////////////////////////

#include "string_utils.h"

#include <ctype.h>

// Case-insensitive string comparison, from Stroustrup's C++ third edition.
// Works like strcmp().
int
cmp_nocase(const string &s, const string &s2) {
  string::const_iterator p = s.begin();
  string::const_iterator p2 = s2.begin();

  while (p != s.end() && p2 != s2.end()) {
    if (toupper(*p) != toupper(*p2)) {
      return (toupper(*p) < toupper(*p2)) ? -1 : 1;
    }
    ++p;
    ++p2;
  }
  
  return (s2.size() == s.size()) ? 0 :
    (s.size() < s2.size()) ? -1 : 1;  // size is unsigned
}

INLINE int 
toupper_uh(int ch) {
  return (ch == '_') ? '-' : toupper(ch);
}


int
cmp_nocase_uh(const string &s, const string &s2) {
  string::const_iterator p = s.begin();
  string::const_iterator p2 = s2.begin();

  while (p != s.end() && p2 != s2.end()) {
    if (toupper_uh(*p) != toupper_uh(*p2)) {
      return (toupper_uh(*p) < toupper_uh(*p2)) ? -1 : 1;
    }
    ++p;
    ++p2;
  }
  
  return (s2.size() == s.size()) ? 0 :
    (s.size() < s2.size()) ? -1 : 1;  // size is unsigned
}



string
downcase(const string &s) {
  string result;
  string::const_iterator p;
  for (p = s.begin(); p != s.end(); ++p) {
    result += tolower(*p);
  }
  return result;
}


////////////////////////////////////////////////////////////////////
//     Function: extract_words
//  Description: Divides the string into a number of words according
//               to whitespace.  The words vector should be cleared by
//               the user before calling; otherwise, the list of words
//               in the string will be appended to the end of whatever
//               was there before.
//
//               The return value is the number of words extracted.
////////////////////////////////////////////////////////////////////
int
extract_words(const string &str, vector_string &words) {
  int num_words = 0;

  size_t pos = 0;
  while (pos < str.length() && isspace(str[pos])) {
    pos++;
  }
  while (pos < str.length()) {
    size_t word_start = pos;
    while (pos < str.length() && !isspace(str[pos])) {
      pos++;
    }
    words.push_back(str.substr(word_start, pos - word_start));
    num_words++;

    while (pos < str.length() && isspace(str[pos])) {
      pos++;
    }
  }

  return num_words;
}

////////////////////////////////////////////////////////////////////
//     Function: trim_left
//  Description: Returns a new string representing the contents of the
//               given string with the leading whitespace removed.
////////////////////////////////////////////////////////////////////
string 
trim_left(const string &str) {
  size_t begin = 0;
  while (begin < str.size() && isspace(str[begin])) {
    begin++;
  }

  return str.substr(begin);
}

////////////////////////////////////////////////////////////////////
//     Function: trim_right
//  Description: Returns a new string representing the contents of the
//               given string with the trailing whitespace removed.
////////////////////////////////////////////////////////////////////
string 
trim_right(const string &str) {
  size_t begin = 0;
  size_t end = str.size();
  while (end > begin && isspace(str[end - 1])) {
    end--;
  }

  return str.substr(begin, end - begin);
}

////////////////////////////////////////////////////////////////////
//     Function: string_to_int
//  Description: A string-interface wrapper around the C library
//               strtol().  This parses the ASCII representation of an
//               integer, and then sets tail to everything that
//               follows the first valid integer read.  If, on exit,
//               str == tail, there was no valid integer in the
//               source string; if !tail.empty(), there was garbage
//               after the integer.
//
//               It is legal if str and tail refer to the same string.
////////////////////////////////////////////////////////////////////
int
string_to_int(const string &str, string &tail) {
  const char *nptr = str.c_str();
  char *endptr;
  int result = strtol(nptr, &endptr, 10);
  tail = endptr;
  return result;
}

////////////////////////////////////////////////////////////////////
//     Function: string_to_int
//  Description: Another flavor of string_to_int(), this one returns
//               true if the string is a perfectly valid integer (and
//               sets result to that value), or false otherwise.
////////////////////////////////////////////////////////////////////
bool
string_to_int(const string &str, int &result) {
  string tail;
  result = string_to_int(str, tail);
  return tail.empty();
}

////////////////////////////////////////////////////////////////////
//     Function: string_to_double
//  Description: A string-interface wrapper around the C library
//               strtol().  This parses the ASCII representation of an
//               floating-point number, and then sets tail to
//               everything that follows the first valid integer read.
//               If, on exit, str == tail, there was no valid integer
//               in the source string; if !tail.empty(), there was
//               garbage after the number.
//
//               It is legal if str and tail refer to the same string.
////////////////////////////////////////////////////////////////////
double
string_to_double(const string &str, string &tail) {
  const char *nptr = str.c_str();
  char *endptr;
  double result = strtod(nptr, &endptr);
  tail = endptr;
  return result;
}

////////////////////////////////////////////////////////////////////
//     Function: string_to_double
//  Description: Another flavor of string_to_double(), this one
//               returns true if the string is a perfectly valid
//               number (and sets result to that value), or false
//               otherwise.
////////////////////////////////////////////////////////////////////
bool
string_to_double(const string &str, double &result) {
  string tail;
  result = string_to_double(str, tail);
  return tail.empty();
}
