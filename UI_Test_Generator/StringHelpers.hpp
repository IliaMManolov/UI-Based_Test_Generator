#ifndef STRINGHELPERS_HPP
#define STRINGHELPERS_HPP

//some helper functions for dealing with strings

#include <sstream>


template <typename T>
    std::wstring toString(const T& value);          //transforms the type T into wstring

template <typename T>
    T toValue(const std::wstring& str);             //and vice versa



#include "StringHelpers.inl"
#endif // STRINGHELPERS_HPP
