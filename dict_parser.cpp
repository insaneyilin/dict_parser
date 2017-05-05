// Copyright 2017 Baidu Inc. All Rights Reserved.
// @author: Yilin Gui (guiyilin@baidu.com)
// @file: dict_parser.cpp
// @brief:

#include "dict_parser.h"

#include <cstdlib>
#include <cstring>

namespace dictparser {

using util::split;

bool DictParser::parse_one_line(const std::string& line) {
    _columns.clear();

    if (!split(line, '\t', &_columns)) {
        return false;
    }

    return true;
}

bool DictParser::get_column_char_array(const int index, const int max_length, char* result) {
    if (index < 0 || index >= _columns.size()) {
        return false;
    }

    if (!parse(_columns[index], max_length, result)) {
        return false;
    }

    return true;
}

}  // namespace dictparser
