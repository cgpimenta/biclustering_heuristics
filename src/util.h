#ifndef UTIL_H
#define UTIL_H

#include <sstream>
#include <iterator>

typedef std::vector<std::vector<double> > Matrix;

template<typename T>
using Rows = std::vector<T>;

template<typename T>
using Cols = std::vector<T>;

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

template<typename T>
std::string join(const T &v, char separator, int max_size){

    if(max_size == 0 || v.empty()) return "";

    typename T::const_iterator it = v.cbegin();
    std::string key = patch::to_string(*(it++));

    for(int i = 1; it != v.cend() && i < max_size; i++, it++){
        key += (separator + patch::to_string(*it));
    }

    return key;
}

template<typename T>
std::string join(const T &v, char separator){

    if(v.empty()) return "";

    typename T::const_iterator it = v.cbegin();
    std::string key = patch::to_string(*(it++));

    for(; it != v.cend(); it++){
        key += (separator + patch::to_string(*it));
    }

    return key;
}

/*
    Obtained from https://stackoverflow.com/questions/236129/most-elegant-way-to-split-a-string
    Author: Evan Teran
 */
template<typename T>
void split(const std::string &s, char delim, T result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;

    typename T::container_type::value_type item_type;
    while (std::getline(ss, item, delim)) {
        std::istringstream(item) >> item_type;
        *(result++) = item_type;
    }
}

template<typename T>
T split(const std::string &s, char delim) {
    T elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

#endif
