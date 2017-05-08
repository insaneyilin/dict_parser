// Copyright 2017 Baidu Inc. All Rights Reserved.
// @author: Yilin Gui (guiyilin@baidu.com)
// @file: built_in_parser.h
// @brief: Declaration of some functions for parsing buiil-in types (int, double, 
//         std::string, c-style string and std::vector)

#ifndef _GOODCODER_GUIYILIN_BUILT_IN_PARSER_H_
#define _GOODCODER_GUIYILIN_BUILT_IN_PARSER_H_

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

#include "util.h"

namespace dictparser {

using util::split;

/**
 * @brief: Parse a string to a int value
 *
 * @param [in] const std::string&: input string
 * @param [in/out] int: parsed result
 * @return bool
 */
bool parse(const std::string& str, int* result);

/**
 * @brief: Parse a string to a double value
 *
 * @param [in] const std::string&: input string
 * @param [in/out] int: parsed result
 * @return bool
 */
bool parse(const std::string& str, double* result);

/**
 * @brief: Parse a string to a string
 *
 * @param [in] const std::string&: input string
 * @param [in/out] int: parsed result
 * @return bool
 */
bool parse(const std::string& str, std::string* result);

/**
 * @brief: Parse a string to a c-style string
 *
 * @param [in] const std::string&: input string
 * @param [in/out] int: parsed result
 * @return bool
 */
bool parse(const std::string& str, size_t max_length, char* result);

/**
 * @brief: Parse a string to an array
 *
 * @param [in] const std::string&: input string
 * @param [in/out] std::vector<T>*: parsed result
 * @return bool
 *
 * @note the string format is "num:item1,item2,item3", where "num" is the number of items
 */
template<typename T>
bool parse(const std::string& str, std::vector<T>* result) {

    if (str.empty()) {
        return false;
    }

    int num_items = 0;

    // parse number of items
    std::string items_str = "";
    {
        std::vector<std::string> tmp;
        if (!split(str, ':', &tmp)) {
            return false;
        }
        if (tmp.size() < 2) {
            return false;
        }
        char* ptr_end;
        num_items = static_cast<int>(std::strtol(tmp.front().c_str(), &ptr_end, 10));
        if (num_items < 0) {
            return false;
        }

        items_str = std::accumulate(tmp.begin() + 1, tmp.end(), std::string(""));
    }

    // split each item into a vector
    std::vector<std::string> items;
    if (!split(items_str, ',', &items)) {
        return false;
    }

    if (items.size() != num_items)
    {
        return false;
    }

    // parse each item
    result->resize(num_items);
    for (size_t i = 0; i < num_items; ++i) {
        if (!parse(items[i], &(result->at(i)))) {
            return false;
        }
    }

    return true;
}

}  // namespace dictparser

#endif  // _GOODCODER_GUIYILIN_BUILT_IN_PARSER_H_
