// Copyright 2017 Baidu Inc. All Rights Reserved.
// @author: Yilin Gui (guiyilin@baidu.com)
// @file: util.cpp
// @brief: Utility functions.

#include "util.h"

namespace dictparser {
namespace util {

bool split(const std::string &str, char separator, std::vector<std::string>* result) {
    if (str.empty()) {
        return false;
    }

    std::string::size_type pos;
    result->clear();
    std::string str_clone = str;
    str_clone += separator;
    size_t len = str_clone.length();

    for (size_t i = 0; i < len; ++i)
    {
        pos = str_clone.find(separator, i);
        if (pos < len) {
            std::string tmp = str_clone.substr(i, pos - i);
            result->push_back(tmp);
            i = pos;
        }
    }

    return true;
}

}  // namespace util
}  // namespace dictparser
