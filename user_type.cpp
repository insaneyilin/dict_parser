// Copyright 2017 Baidu Inc. All Rights Reserved.
// @author: Yilin Gui (guiyilin@baidu.com)
// @file: user_type.cpp
// @brief:

#include "user_type.h"

#include <iostream>
#include <sstream>

namespace dictparser {

bool parse(const std::string& str, FooStruct* result) {
    if (str.empty()) {
        return false;
    }

    std::istringstream iss(str);
    if (!iss.good()) {
        return false;
    }

    iss >> result->a >> result->b >> result->c;

    return true;
}

}  // namespace dictparser
