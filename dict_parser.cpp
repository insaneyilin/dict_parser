// Copyright 2017 Baidu Inc. All Rights Reserved.
// @author: Yilin Gui (guiyilin@baidu.com)
// @file: dict_parser.cpp
// @brief: DictParser class implementation. 

#include "dict_parser.h"

#include <cstdlib>
#include <cstring>

namespace dictparser {

using util::split;

DictParser::~DictParser() {
    for (auto itr = _user_type_printers.begin(); 
        itr != _user_type_printers.end(); ++itr) {
        delete itr->second;
    }
}

ERROR_CODE DictParser::parse_one_line(const std::string& line) {
    _columns.clear();

    if (!split(line, '\t', &_columns)) {
        std::cerr << "Failed to split: " << line << std::endl;
        return RET_FAILURE;
    }

    return RET_SUCCESS;
}

ERROR_CODE DictParser::get_column_char_array(
        const int index, const int max_length, char* result) {
    if (index < 0 || index >= _columns.size()) {
        std::cerr << "Out of range! The columns size is: " << _columns.size() << std::endl;
        return OUT_OF_RANGE;
    }

    if (parse(_columns[index], max_length, result) != RET_SUCCESS) {
        std::cerr << "Failed to parse column to C-style string at index: " << index << std::endl;
        return RET_FAILURE;
    }

    return RET_SUCCESS;
}

void DictParser::set_columns_types(const std::vector<std::string>& columns_types) {
    _columns_types = columns_types;
}

bool DictParser::print_column_data(const int index) {
    if (index < 0 || index >= _columns_types.size()) {
        std::cerr << "Out of range! The columns types' size is: " 
                << _columns_types.size() << std::endl;
        return false;
    }
    const auto& type = _columns_types[index];
    bool ret = true;
    if (type == "int") {
        int column_data = 0;
        if (get_column_data(index, &column_data) == dictparser::RET_SUCCESS) {
            std::cout << "Column " << index << ": ";
            std::cout << column_data << std::endl;
        } else {
            ret = false;
        }
    } else if (type == "float") {
        double column_data = 0.0;
        if (get_column_data(index, &column_data) == dictparser::RET_SUCCESS) {
            std::cout << "Column " << index << ": ";
            std::cout << column_data << std::endl;
        } else {
            ret = false;
        }
    } else if (type == "string") {
        std::string column_data = "";
        if (get_column_data(index, &column_data) == dictparser::RET_SUCCESS) {
            std::cout << "Column " << index << ": ";
            std::cout << column_data << std::endl;
        } else {
            ret = false;
        }
    } else if (type == "int_array") {
        std::vector<int> column_data;
        if (get_column_data(index, &column_data) == dictparser::RET_SUCCESS) {
            std::cout << "Column " << index << ": ";
                    std::cout << "[";
            for (size_t i = 0; i < column_data.size(); ++i) {
                std::cout << (i == 0 ? "" : ", ") << column_data[i];
            }
            std::cout << "]" << std::endl;
        } else {
            ret = false;
        }
    } else if (type == "float_array") {
        std::vector<double> column_data;
        if (get_column_data(index, &column_data) == dictparser::RET_SUCCESS) {
            std::cout << "Column " << index << ": ";
                    std::cout << "[";
            for (size_t i = 0; i < column_data.size(); ++i) {
                std::cout << (i == 0 ? "" : ", ") << column_data[i];
            }
            std::cout << "]" << std::endl;
        } else {
            ret = false;
        }
    } else if (type == "string_array") {
        std::vector<std::string> column_data;
        if (get_column_data(index, &column_data) == dictparser::RET_SUCCESS) {
            std::cout << "Column " << index << ": ";
                    std::cout << "[";
            for (size_t i = 0; i < column_data.size(); ++i) {
                std::cout << (i == 0 ? "" : ", ") << column_data[i];
            }
            std::cout << "]" << std::endl;
        } else {
            ret = false;
        }
    } else {
        // User defined type
        if (_user_type_printers.find(type) == _user_type_printers.end()) {
            ret = false;
        } else {
            _user_type_printers[type]->print_column_data(index);
        }
    }

    if (!ret) {
        std::cerr << "Failed to get column data at index: " << index << std::endl;
        return false;
    }

    return true;
}

void DictParser::set_user_type_printer(const std::string& type, ColumnPrinter* printer) {
    _user_type_printers[type] = printer;
}


}  // namespace dictparser
