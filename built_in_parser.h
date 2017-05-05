// Copyright 2017 Baidu Inc. All Rights Reserved.
// @author: Yilin Gui (guiyilin@baidu.com)
// @file: built_in_parser.h
// @brief:

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

bool parse(const std::string& str, int* result);
bool parse(const std::string& str, double* result);   
bool parse(const std::string& str, std::string* result);
bool parse(const std::string& str, size_t max_length, char* result);

/* Goodcoder 中没有要求解析自定义类型的数组。。。 */
// template<typename T>
// bool parse_array(
//         const std::string& str, 
//         bool (*parse_func)(const std::string&, T*), 
//         std::vector<T>* result) {

//     if (str.empty()) {
//         return false;
//     }

//     int num_items = 0;
//     std::string items_str = "";
//     {
//         std::vector<std::string> tmp;
//         if (!split(str, ':', &tmp)) {
//             return false;
//         }
//         if (tmp.size() < 2) {
//             return false;
//         }
//         char* ptr_end;
//         num_items = static_cast<int>(std::strtol(tmp.front().c_str(), &ptr_end, 10));
//         if (num_items < 0) {
//             return false;
//         }

//         items_str = std::accumulate(tmp.begin() + 1, tmp.end(), std::string(""));
//     }

//     std::vector<std::string> items;
//     if (!split(items_str, ',', &items)) {
//         return false;
//     }

//     if (items.size() != num_items)
//     {
//         return false;
//     }

//     result->resize(num_items);
//     for (size_t i = 0; i < num_items; ++i) {
//         if (!parse_func(items[i], &(result->at(i)))) {
//             return false;
//         }
//     }

//     return true;
// }

template<typename T>
bool parse(const std::string& str, std::vector<T>* result) {

    if (str.empty()) {
        return false;
    }

    int num_items = 0;
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

    std::vector<std::string> items;
    if (!split(items_str, ',', &items)) {
        return false;
    }

    if (items.size() != num_items)
    {
        return false;
    }

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
