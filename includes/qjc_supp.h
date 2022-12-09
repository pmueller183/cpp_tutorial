//345678911234567892123456789312345678941234567895123456789612345678971234567898123456-
#pragma once

#include <sstream>

template <typename T>
std::string to_string(T const &val)
{
  std::ostringstream ss;
  ss << val;
  return ss.str();
} // to_string
