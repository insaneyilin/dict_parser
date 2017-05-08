// Copyright 2017 Baidu Inc. All Rights Reserved.
// @author: Yilin Gui (guiyilin@baidu.com)
// @file: built_in_parser.cpp
// @brief: Implementation of some functions for parsing buiil-in types.

#include "built_in_parser.h"

namespace dictparser {

bool parse(const std::string& str, int* result) {
    if (str.empty()) {
        std::cerr << "Cannot parse an empty string to an integer!" << std::endl;
        return false;
    }

    char *ptr_end;
    *result = static_cast<int>(std::strtol(str.c_str(), &ptr_end, 10));

    if (*result != 0) {
        return true;
    }

    // check whether the input is a real zero
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] != '0') {
            std::cerr << "Failed to parse " << str << " to an integer!" << std::endl;
            return false;
        }
    }

    return true;
}

bool parse(const std::string& str, double* result) {
    if (str.empty()) {
        std::cerr << "Cannot parse an empty string to a double!" << std::endl;
        return false;
    }

    *result = std::atof(str.c_str());

    const double EPS = 1e-10;
    if (fabs(*result) > EPS) {
        return true;
    }

    // check whether the input is a real zero
    size_t dot_count = 0;
    bool is_zero = true;
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] != '0' && str[i] != '.' && str[i] != '-') {
            is_zero = false;
            break;
        }
        if (str[i] == '-' && i != 0) {
            is_zero = false;
            break;
        }
        if (str[i] == '.') {
            ++dot_count;
        }
        if (dot_count > 1) {
            is_zero = false;
            break;
        }
    }
    if (!is_zero) {
        std::cerr << "Failed to parse " << str << " to a double!" << std::endl;
        return false;
    }

    return true;
}

bool parse(const std::string& str, std::string* result) {
    if (str.empty()) {
        std::cerr << "Cannot parse an empty string!" << std::endl;
        return false;
    }

    (*result).clear();
    for (size_t i = 0; i < str.size(); ++i) {
        // '\n' should not appear in a parsed result
        if (str[i] == '\n') {
            break;
        }
        (*result) += str[i];
    }

    return true;
}

bool parse(const std::string& str, size_t max_length, char* result) {
    if (str.empty()) {
        std::cerr << "Cannot parse an empty string!" << std::endl;
        return false;
    }

    size_t len = str.length();
    for (size_t i = 0; i < len; ++i)
    {
        if (result == NULL || i >= max_length) {
            std::cerr << "Out of range! Max length of the input string is " << max_length << std::endl;
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

