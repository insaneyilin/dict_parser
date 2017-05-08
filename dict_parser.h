// Copyright 2017 Baidu Inc. All Rights Reserved.
// @author: Yilin Gui (guiyilin@baidu.com)
// @file: dict_parser.h
// @brief: DictParser class declaration, this class can parse one line of the dict
//         and get data at a specific column.

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

    /**
     * @brief: Parse one line of the dictionary and save original columns string.
     *
     * @param [in] const std::string&: input line string
     * @return bool
     */
    bool parse_one_line(const std::string& line);


    /**
     * @brief: Get number of columns. Should be called after parse_one_line()
     *
     * @return size_t: number of columns
     */
    size_t get_num_columns() const {
        return _columns.size();
    }

    /**
     * @brief: Get data at a specific column.
     *
     * @param [in] const int: column index
     * @param [in/out] T*: parsed result
     * 
     * @return bool
     */
    template<typename T>
    bool get_column_data(const int index, T* result);

    /**
     * @brief: Get a c-style array at a specific column.
     *
     * @param [in] const int: column index
     * @param [in] const int: maximum length of the input array
     * @param [in/out] T*: parsed result
     * 
     * @return bool
     */
    bool get_column_char_array(const int index, const int max_length, char* result);

private:
    std::vector<std::string> _columns;  // to save original columns strings

    DISALLOW_COPY_AND_ASSIGN(DictParser);
};

template<typename T>
bool DictParser::get_column_data(const int index, T* result) {
    if (index < 0 || index >= _columns.size()) {
        std::cerr << "Out of range! The columns size is: " << _columns.size() << std::endl;
        return false;
    }

    if (!parse(_columns[index], result)) {
        std::cerr << "Failed to parse column at index: " << index << std::endl;
        return false;
    }

    return true;
}

}  // namespace dictparser

#endif  // _GOODCODER_GUIYILIN_DICT_PARSER_H_
