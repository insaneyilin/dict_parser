// Copyright 2017 Baidu Inc. All Rights Reserved.
// @author: Yilin Gui (guiyilin@baidu.com)
// @file: dict_parser_demo.cpp
// @brief: A demo showing how to use DictParser class to parse a dict. of multiple lines.

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "user_type.h"
#include "dict_parser.h"

// A dictionary containing multiple lines
char* dict = "4:7,2,0,-20\taavvs13\t32\t-123.002\t80 123.34 Sam\n"
        "3:9,2,6\tbsdfg\t23\t0.23145\t-64 9.213 ysfg\n"
        "1:-10000\tldiej\t983\t648.284\t100000 890900099.123444 ieoejk\n"
        "4:7,2,0,-20\taavvs13\t32\t-123.002\t80 123.34 Sam\n"
        "3:9,2,6\tbsdfg\t23\t0.23145\t-64 9.213 ysfg\n"
        "1:-10000\tldiej\t983\t648.284\t100000 890900099.123444 ieoejk\n"
        "4:7,2,0,-20\taavvs13\t32\t-123.002\t80 123.34 Sam\n"
        "3:9,2,6\tbsdfg\t23\t0.23145\t-64 9.213 ysfg\n"
        "1:-10000\tldiej\t983\t648.284\t100000 890900099.123444 ieoejk\n"
        "4:7,2,0,-20\taavvs13\t32\t-123.002\t80 123.34 Sam\n"
        "3:9,2,6\tbsdfg\t23\t0.23145\t-64 9.213 ysfg\n"
        "1:-10000\tldiej\t983\t648.284\t100000 890900099.123444 ieoejk\n"
        "4:7,2,0,-20\taavvs13\t32\t-123.002\t80 123.34 Sam\n"
        "3:9,2,6\tbsdfg\t23\t0.23145\t-64 9.213 ysfg\n"
        "1:-10000\tldiej\t983\t648.284\t100000 890900099.123444 ieoejk\n"
        "4:7,2,0,-20\taavvs13\t32\t-123.002\t80 123.34 Sam\n"
        "3:9,2,6\tbsdfg\t23\t0.23145\t-64 9.213 ysfg\n"
        "1:-10000\tldiej\t983\t648.284\t100000 890900099.123444 ieoejk\n"
        "4:7,2,0,-20\taavvs13\t32\t-123.002\t80 123.34 Sam\n"
        "3:9,2,6\tbsdfg\t23\t0.23145\t-64 9.213 ysfg\n"
        "1:-10000\tldiej\t983\t648.284\t100000 890900099.123444 ieoejk\n"
        "4:7,2,0,-20\taavvs13\t32\t-123.002\t80 123.34 Sam\n"
        "3:9,2,6\tbsdfg\t23\t0.23145\t-64 9.213 ysfg\n"
        "1:-10000\tldiej\t983\t648.284\t100000 890900099.123444 ieoejk\n";


int main(int argc, char **argv)
{
    std::istringstream iss;
    iss.str(dict);

    // Parse dict. line by line
    for (std::string line; std::getline(iss, line); ) {
        dictparser::DictParser parser;
        if (!parser.parse_one_line(line)) {
            std::cerr << "Failed to parse one line!" << std::endl;
            return 1;
        }

        // Column 0
        std::vector<int> column_0;
        if (!parser.get_column_data(0, &column_0)) {
            std::cerr << "Failed to get column data at index: " << 0 << std::endl;
            return 1;
        }
        std::cout << "Column 0: ";
        std::cout << "[";
        for (size_t i = 0; i < column_0.size(); ++i) {
            std::cout << (i == 0 ? "" : ", ") << column_0[i];
        }
        std::cout << "]" << std::endl;

        // Column 1
        std::string column_1;
        if (!parser.get_column_data(1, &column_1)) {
            std::cerr << "Failed to get column data at index: " << 1 << std::endl;
            return 1;
        }
        std::cout << "Column 1: ";
        std::cout << column_1 << std::endl;

        // Column 2
        int column_2;
        if (!parser.get_column_data(2, &column_2)) {
            std::cerr << "Failed to get column data at index: " << 2 << std::endl;
            return 1;
        }
        std::cout << "Column 2: ";
        std::cout << column_2 << std::endl;

        // Column 3
        double column_3;
        if (!parser.get_column_data(3, &column_3)) {
            std::cerr << "Failed to get column data at index: " << 3 << std::endl;
            return 1;
        }
        std::cout << "Column 3: ";
        std::cout << column_3 << std::endl;

        // Column 4
        dictparser::FooStruct column_4;
        if (!parser.get_column_data(4, &column_4)) {
            std::cerr << "Failed to get column data at index: " << 4 << std::endl;
            return 1;
        }
        std::cout << "Column 4: ";
        std::cout << column_4.a << " " << column_4.b << " " << column_4.c << std::endl;

        std::cout << std::endl << std::endl;
    }

    return 0;
}
