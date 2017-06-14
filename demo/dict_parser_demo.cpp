// Copyright 2017 Baidu Inc. All Rights Reserved.
// @author: Yilin Gui (guiyilin@baidu.com)
// @file: dict_parser_demo.cpp
// @brief: A demo showing how to use DictParser class to parse a dict. of multiple lines.

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "user_type.h"
#include "dict_parser.h"

bool load_columns_types_config(const std::string& config_file, 
        std::vector<std::string>* columns_types) {
    std::ifstream ifs(config_file.c_str());
    if (!ifs) {
        std::cerr << "Failed to open " << config_file << std::endl;
        return false;
    }

    columns_types->clear();
    while (!ifs.eof()) {
        std::string type;
        std::getline(ifs, type);
        columns_types->push_back(type);
    }

    return true;
}

bool parse_dict_from_file(const std::string &filename, 
        dictparser::DictParser& dict_parser) {
    std::ifstream ifs(filename.c_str());
    if (!ifs) {
        std::cerr << "Failed to open dict filename " << filename << std::endl;
        return false;
    }

    int num_lines = 0;
    while (!ifs.eof()) {
        std::string line;
        std::getline(ifs, line);
        if (line == "\n") {
            continue;
        }
        dict_parser.parse_one_line(line);
        size_t num_cols = dict_parser.get_num_columns();
        std::cout << "Row " << num_lines << std::endl;
        for (size_t i = 0; i < num_cols; ++i) {
            if (!dict_parser.print_column_data(i)) {
                std::cerr << "Failed to print column data at index " << i << std::endl;
                return false;
            }
        }
        std::cout << std::endl;
        ++num_lines;
    }

    return true;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " config_file_path dict_file_path" << std::endl;
        return -1;
    }

    // Load columns types config from file
    std::string config_file = argv[1];
    std::vector<std::string> columns_types;
    if (!load_columns_types_config(config_file, &columns_types)) {
        std::cerr << "Failed to load columns types config file!" << std::endl;
        return -1;
    }

    // Set parser's columns types
    dictparser::DictParser parser;
    parser.set_columns_types(columns_types);

    // Set printer for user defined type
    dictparser::ColumnPrinter* foo_printer = new dictparser::FooStructPrinter(&parser);
    parser.set_user_type_printer(dictparser::FOO_STRUCT_TYPE_NAME, foo_printer);

    // Parse from data file
    std::string dict_file = argv[2];
    if (!parse_dict_from_file(dict_file, parser)) {
        std::cerr << "Failed to parse dict from file " << dict_file << std::endl;
        return -1;
    }

    return 0;
}
