// Copyright 2017 Baidu Inc. All Rights Reserved.
// @author: Yilin Gui (guiyilin@baidu.com)
// @file: util.h
// @brief:

#ifndef _GOODCODER_GUIYILIN_UTIL_H_
#define _GOODCODER_GUIYILIN_UTIL_H_

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

const size_t MAX_CSTR_LENGTH = 1024;

namespace util {

bool split(const std::string &str, char separator, std::vector<std::string>* result);

}  // namespace util
}  // namespace dictparser

#endif  // _GOODCODER_GUIYILIN_UTIL_H_
