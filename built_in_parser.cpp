// Copyright 2017 Baidu Inc. All Rights Reserved.
// @author: Yilin Gui (guiyilin@baidu.com)
// @file: built_in_parser.cpp
// @brief:

#include "built_in_parser.h"

namespace dictparser {

bool parse(const std::string& str, int* result) {
    if (str.empty()) {
        return false;
    }

    char *ptr_end;
    *result = static_cast<int>(std::strtol(str.c_str(), &ptr_end, 10));

    if (*result != 0) {
        return true;
    }

    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] != '0') {
            return false;
        }
    }

    return true;
}

bool parse(const std::string& str, double* result) {
    if (str.empty()) {
        return false;
    }

    *result = std::atof(str.c_str());

    const double EPS = 1e-10;
    if (fabs(*result) > EPS) {
        return true;
    }

    size_t dot_count = 0;
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] != '0' && str[i] != '.' && str[i] != '-') {
            return false;
        }
        if (str[i] == '-' && i != 0) {
            return false;
        }
        if (str[i] == '.') {
            ++dot_count;
        }
        if (dot_count > 1) {
            return false;
        }
    }

    return true;
}

bool parse(const std::string& str, std::string* result) {
    if (str.empty()) {
        return false;
    }

    (*result).clear();
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '\n') {
            break;
        }
        (*result) += str[i];
    }

    return true;
}

bool parse(const std::string& str, size_t max_length, char* result) {
    if (str.empty()) {
        return false;
    }

    size_t len = str.length();
    for (size_t i = 0; i < len; ++i)
    {
        if (result == NULL || i >= max_length) {
            return false;
        }
        if (str[i] == '\n') {
            break;
        }
        *result = str[i];
        ++result;
    }
    *result = '\0';

    return true;
}

}  // namespace dictparser

