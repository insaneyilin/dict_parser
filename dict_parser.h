// Copyright 2017 Baidu Inc. All Rights Reserved.
// @author: Yilin Gui (guiyilin@baidu.com)
// @file: dict_parser.h
// @brief:

#ifndef _GOODCODER_GUIYILIN_DICT_PARSER_H_
#define _GOODCODER_GUIYILIN_DICT_PARSER_H_

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

#include "util.h"
#include "built_in_parser.h"

namespace dictparser {

class DictParser {
public:
    DictParser() = default;
    ~DictParser() = default;

    bool parse_one_line(const std::string& line);

    size_t get_num_columns() const {
        return _columns.size();
    }

    template<typename T>
    bool get_column_data(const int index, T* result);

    bool get_column_char_array(const int index, const int max_length, char* result);

private:
    std::vector<std::string> _columns;

    DISALLOW_COPY_AND_ASSIGN(DictParser);
};

template<typename T>
bool DictParser::get_column_data(const int index, T* result) {
    if (index < 0 || index >= _columns.size()) {
        return false;
    }

    if (!parse(_columns[index], result)) {
        return false;
    }

    return true;
}

}  // namespace dictparser

#endif  // _GOODCODER_GUIYILIN_DICT_PARSER_H_
