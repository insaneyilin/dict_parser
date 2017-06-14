// Copyright 2017 Baidu Inc. All Rights Reserved.
// @author: Yilin Gui (guiyilin@baidu.com)
// @file: user_type.h
// @brief: A user-defined struct example.

#ifndef GOODCODER_GUIYILIN_DICT_PARSER_USER_TYPE_H
#define GOODCODER_GUIYILIN_DICT_PARSER_USER_TYPE_H

#include <string>
#include "util.h"

namespace dictparser {

const std::string FOO_STRUCT_TYPE_NAME = "FooStruct";

// A simple user-defined stuct
struct FooStruct {
    int a;
    double b;
    std::string c;
};

class DictParser;

// A helper class to print FooStruct objects
class FooStructPrinter : public ColumnPrinter {
public:
    FooStructPrinter(DictParser* parser);
    virtual ~FooStructPrinter();

    bool print_column_data(const int index);

private:
    DictParser* _parser;
};

/**
 * @brief: Parse a string to a FooStruct
 *
 * @param [in] const std::string&: input string
 * @param [in/out] FooStruct*: parsed result
 * @return ERROR_CODE
 */
ERROR_CODE parse(const std::string& str, FooStruct* result);

}  // namespace dictparser

#endif // GOODCODER_GUIYILIN_DICT_PARSER_USER_TYPE_H
