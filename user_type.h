// Copyright 2017 Baidu Inc. All Rights Reserved.
// @author: Yilin Gui (guiyilin@baidu.com)
// @file: user_type.h
// @brief:

#ifndef _GOODCODER_GUIYILIN_USER_TYPE_H_
#define _GOODCODER_GUIYILIN_USER_TYPE_H_

#include <string>

namespace dictparser {

struct FooStruct {
    int a;
    double b;
    std::string c;
};

bool parse(const std::string& str, FooStruct* result);

}  // namespace dictparser

#endif // _GOODCODER_GUIYILIN_USER_TYPE_H_
