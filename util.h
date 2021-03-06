// Copyright 2017 Baidu Inc. All Rights Reserved.
// @author: Yilin Gui (guiyilin@baidu.com)
// @file: util.h
// @brief: Some utility functions and constants definitions.

#ifndef GOODCODER_GUIYILIN_DICT_PARSER_UTIL_H
#define GOODCODER_GUIYILIN_DICT_PARSER_UTIL_H

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
        TypeName(const TypeName&); \
        TypeName& operator=(const TypeName&)

namespace dictparser {

enum ERROR_CODE {
    RET_SUCCESS = 0,
    RET_FAILURE = 1,
    EMPTY_INPUT = 2,
    WRONG_ARRAY_SIZE = 3,
    OUT_OF_RANGE = 4,
    ERROR_CODE_COUNT = 5
};

// Maximum length of a c-style string
const size_t MAX_CSTR_LENGTH = 1024;

class ColumnPrinter {
public:
    ColumnPrinter() = default;
    virtual ~ColumnPrinter() = default;
    virtual bool print_column_data(const int index) = 0;
};

namespace util {

/**
 * @brief: split a string 
 *
 * @param [in] const std::string&: input string
 * @param [in] char: separator to split input string
 * @param [in/out] std::vector<std::string>*: split result
 * @return bool
 */
bool split(const std::string &str, char separator, std::vector<std::string>* result);

}  // namespace util
}  // namespace dictparser

#endif  // GOODCODER_GUIYILIN_DICT_PARSER_UTIL_H
