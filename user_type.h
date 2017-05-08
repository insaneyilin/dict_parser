// Copyright 2017 Baidu Inc. All Rights Reserved.
// @author: Yilin Gui (guiyilin@baidu.com)
// @file: user_type.h
// @brief: A user-defined struct example.

#ifndef _GOODCODER_GUIYILIN_USER_TYPE_H_
#define _GOODCODER_GUIYILIN_USER_TYPE_H_

#include <string>

namespace dictparser {

// A simple user-defined stuct
struct FooStruct {
    int a;
    double b;
    std::string c;
};

/**
 * @brief: Parse a string to a FooStruct
 *
 * @param [in] const std::string&: input string
 * @param [in/out] FooStruct*: parsed result
 * @return bool
 */
bool parse(const std::string& str, FooStruct* result);

}  // namespace dictparser

#endif // _GOODCODER_GUIYILIN_USER_TYPE_H_
