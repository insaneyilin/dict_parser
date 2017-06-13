// Copyright 2017 Baidu Inc. All Rights Reserved.
// @author: Yilin Gui (guiyilin@baidu.com)
// @file: dict_parser.h
// @brief: DictParser class declaration, this class can parse one line of the dict
//         and get data at a specific column.

#ifndef GOODCODER_GUIYILIN_DICT_PARSER_DICT_PARSER_H
#define GOODCODER_GUIYILIN_DICT_PARSER_DICT_PARSER_H

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>

#include "util.h"
#include "built_in_parser.h"

namespace dictparser {

class DictParser {
public:
    DictParser() = default;
    ~DictParser();

    /**
     * @brief: Parse one line of the dictionary and save original columns string.
     *
     * @param [in] const std::string&: input line string
     * @return ERROR_CODE
     */
    ERROR_CODE parse_one_line(const std::string& line);

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
     * @return ERROR_CODE
     */
    template<typename T>
    ERROR_CODE get_column_data(const int index, T* result);

    /**
     * @brief: Get a c-style array at a specific column.
     *
     * @param [in] const int: column index
     * @param [in] const int: maximum length of the input array
     * @param [in/out] T*: parsed result
     * 
     * @return ERROR_CODE
     */
    ERROR_CODE get_column_char_array(const int index, const int max_length, char* result);

    /**
     * @brief: Set types of columns.
     *
     * @param [in] const std::vector<std::string>&: types of columns
     * 
     * @return ERROR_CODE
     */
    void set_columns_types(const std::vector<std::string>& columns_types);

    /**
     * @brief: Print columns values of current line.
     * 
     * @param [in] const int: column index
     * 
     * @return ERROR_CODE
     */
    bool print_column_data(const int index);

    void set_user_type_printer(const std::string& type, ColumnPrinter* printer);

private:
    std::vector<std::string> _columns;  // to save original columns strings
    std::vector<std::string> _columns_types;  // to save types of columns
    std::map<std::string, ColumnPrinter*> _user_type_printers;

    DISALLOW_COPY_AND_ASSIGN(DictParser);
};

template<typename T>
ERROR_CODE DictParser::get_column_data(const int index, T* result) {
    if (index < 0 || index >= _columns.size()) {
        std::cerr << "Out of range! The columns size is: " << _columns.size() << std::endl;
        return OUT_OF_RANGE;
    }

    if (parse(_columns[index], result) != RET_SUCCESS) {
        std::cerr << "Failed to parse column at index: " << index << std::endl;
        return RET_FAILURE;
    }

    return RET_SUCCESS;
}

}  // namespace dictparser

#endif  // GOODCODER_GUIYILIN_DICT_PARSER_DICT_PARSER_H
