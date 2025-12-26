#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <algorithm>

inline std::string toLower(const std::string &s) {
    std::string r = s;
    std::transform(r.begin(), r.end(), r.begin(), ::tolower);
    return r;
}

#endif 
