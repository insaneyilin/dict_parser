// Copyright 2017 Baidu Inc. All Rights Reserved.
// @author: Yilin Gui (guiyilin@baidu.com)
// @file: user_type.cpp
// @brief: A user-defined struct example.

#include "user_type.h"

#include <iostream>
#include <sstream>

#include "dict_parser.h"

namespace dictparser {

FooStructPrinter::FooStructPrinter(DictParser* parser) {
    _parser = parser;
}

FooStructPrinter::~FooStructPrinter() {
    _parser = NULL;
}

bool FooStructPrinter::print_column_data(const int index) {
    FooStruct foo;

    if (_parser->get_column_data(index, &foo) != RET_SUCCESS) {
        std::cerr << "Failed to get column data at index: " << index << std::endl;
        return false;
    }
    std::cout << "Column " << index << ": ";
    std::cout << foo.a << " " << foo.b << " " << foo.c << std::endl;

    return true;
}

ERROR_CODE parse(const std::string& str, FooStruct* result) {
    if (str.empty()) {
        return EMPTY_INPUT;
    }

    std::istringstream iss(str);
    if (!iss.good()) {
        return RET_FAILURE;
    }

    iss >> result->a >> result->b >> result->c;

    return RET_SUCCESS;
}

}  // namespace dictparser
