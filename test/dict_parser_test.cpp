// Copyright 2017 Baidu Inc. All Rights Reserved.
// @author: Yilin Gui (guiyilin@baidu.com)
// @file: dict_parser_test.cpp
// @brief: Unittest for DictParser class.

#include <climits>
#include <cmath>
#include <string>

#include <gtest/gtest.h>

#include "user_type.h"
#include "dict_parser.h"

namespace dictparser {

class DictParserTest : public testing::Test {
protected:
    DictParserTest() = default;
    virtual ~DictParserTest() {}

    virtual void SetUp() {
        _dict_parser = new DictParser();
    }

    virtual void TearDown() {
        delete _dict_parser;
    }

protected:
    DictParser* _dict_parser;
};

TEST_F(DictParserTest, case_empty_line) {
    EXPECT_EQ(RET_FAILURE, _dict_parser->parse_one_line(std::string("")));
    int result = 0;
    EXPECT_EQ(OUT_OF_RANGE, _dict_parser->get_column_data(0, &result));
}

TEST_F(DictParserTest, case_invalid) {
    std::string line_1 = "-3.412\t2:1,2,3\tasdf\n";
    EXPECT_EQ(RET_SUCCESS, _dict_parser->parse_one_line(line_1));

    std::vector<int> col_1;
    EXPECT_EQ(RET_FAILURE, _dict_parser->get_column_data(1, &col_1));
}

TEST_F(DictParserTest, case_int_columns) {
    std::string line = "24\t-23\t123\t5\t-20\t66666666\n";
    EXPECT_EQ(RET_SUCCESS, _dict_parser->parse_one_line(line));

    std::vector<int> gt_values = {24, -23, 123, 5, -20, 66666666};
    EXPECT_EQ(gt_values.size(), _dict_parser->get_num_columns());
    for (size_t i = 0; i < gt_values.size(); ++i) {
        int val = 0;
        EXPECT_EQ(RET_SUCCESS, _dict_parser->get_column_data(i, &val));
        EXPECT_EQ(gt_values[i], val);
    }
}

TEST_F(DictParserTest, case_double_columns) {
    std::string line = "2.33333\t-9811111.1123\t0.000001\t928347\t.6372\n";
    EXPECT_EQ(RET_SUCCESS, _dict_parser->parse_one_line(line));

    std::vector<double> gt_values = {2.33333, -9811111.1123, 0.000001, 928347, .6372};
    EXPECT_EQ(gt_values.size(), _dict_parser->get_num_columns());
    for (size_t i = 0; i < gt_values.size(); ++i) {
        double val = 0;
        EXPECT_EQ(RET_SUCCESS, _dict_parser->get_column_data(i, &val));
        EXPECT_DOUBLE_EQ(gt_values[i], val);
    }
}

TEST_F(DictParserTest, case_string_columns) {
    std::string line = "hello\t^-^\tworld\t>_<\t**^. ^**\n";
    EXPECT_EQ(RET_SUCCESS, _dict_parser->parse_one_line(line));
    EXPECT_EQ(5, _dict_parser->get_num_columns());

    std::string col_0 = "";
    EXPECT_EQ(RET_SUCCESS, _dict_parser->get_column_data(0, &col_0));
    EXPECT_EQ("hello", col_0);

    char col_0_cstr[MAX_CSTR_LENGTH];  // test C-style string
    EXPECT_EQ(RET_SUCCESS, _dict_parser->get_column_char_array(0, MAX_CSTR_LENGTH, col_0_cstr));
    EXPECT_STREQ("hello", col_0_cstr);

    std::string col_1 = "";
    EXPECT_EQ(RET_SUCCESS, _dict_parser->get_column_data(1, &col_1));
    EXPECT_EQ("^-^", col_1);

    char col_1_cstr[MAX_CSTR_LENGTH];  // test C-style string
    EXPECT_EQ(RET_SUCCESS, _dict_parser->get_column_char_array(1, MAX_CSTR_LENGTH, col_1_cstr));
    EXPECT_STREQ("^-^", col_1_cstr);

    std::string col_2 = "";
    EXPECT_EQ(RET_SUCCESS, _dict_parser->get_column_data(2, &col_2));
    EXPECT_EQ("world", col_2);

    char col_2_cstr[MAX_CSTR_LENGTH];  // test C-style string
    EXPECT_EQ(RET_SUCCESS, _dict_parser->get_column_char_array(2, MAX_CSTR_LENGTH, col_2_cstr));
    EXPECT_STREQ("world", col_2_cstr);

    char col_4_cstr[MAX_CSTR_LENGTH];  // test C-style string
    EXPECT_EQ(RET_SUCCESS, _dict_parser->get_column_char_array(4, MAX_CSTR_LENGTH, col_4_cstr));
    EXPECT_STREQ("**^. ^**", col_4_cstr);
}

TEST_F(DictParserTest, case_array_columns) {
    std::string line = "3:1,3,2\t1:-0.123\t4:nice,to,meet,you!\n";

    EXPECT_EQ(RET_SUCCESS, _dict_parser->parse_one_line(line));

    EXPECT_EQ(3, _dict_parser->get_num_columns());

    std::vector<int> col_0;
    std::vector<int> col_0_gt = {1, 3, 2};
    EXPECT_EQ(RET_SUCCESS, _dict_parser->get_column_data(0, &col_0));
    EXPECT_EQ(col_0_gt.size(), col_0.size());
    for (size_t i = 0; i < col_0.size(); ++i) {
        EXPECT_EQ(col_0_gt[i], col_0[i]);
    }

    std::vector<double> col_1;
    std::vector<double> col_1_gt = {-0.123};
    EXPECT_EQ(RET_SUCCESS, _dict_parser->get_column_data(1, &col_1));
    EXPECT_EQ(col_1_gt.size(), col_1.size());
    for (size_t i = 0; i < col_1.size(); ++i) {
        EXPECT_DOUBLE_EQ(col_1_gt[i], col_1[i]);
    }

    std::vector<std::string> col_2;
    std::vector<std::string> col_2_gt = {"nice", "to", "meet", "you!"};
    EXPECT_EQ(RET_SUCCESS, _dict_parser->get_column_data(2, &col_2));
    EXPECT_EQ(col_2_gt.size(), col_2.size());
    for (size_t i = 0; i < col_2.size(); ++i) {
        EXPECT_EQ(col_2_gt[i], col_2[i]);
    }
}

TEST_F(DictParserTest, case_mix_columns) {
    std::string line = "Baidu\t8864\t11.823\t*&*^@*((&asdf\t5:4,6,7,-2,0\t-1213.023\n";
    EXPECT_EQ(RET_SUCCESS, _dict_parser->parse_one_line(line));

    std::string col_0 = "";
    EXPECT_EQ(RET_SUCCESS, _dict_parser->get_column_data(0, &col_0));
    EXPECT_EQ("Baidu", col_0);

    int col_1 = 0;
    EXPECT_EQ(RET_SUCCESS, _dict_parser->get_column_data(1, &col_1));
    EXPECT_EQ(8864, col_1);

    double col_2 = 0.0;
    EXPECT_EQ(RET_SUCCESS, _dict_parser->get_column_data(2, &col_2));
    EXPECT_DOUBLE_EQ(11.823, col_2);

    std::string col_3 = "";
    EXPECT_EQ(RET_SUCCESS, _dict_parser->get_column_data(3, &col_3));
    EXPECT_EQ("*&*^@*((&asdf", col_3);

    std::vector<int> col_4;
    std::vector<int> col_4_gt = {4, 6, 7, -2, 0};
    EXPECT_EQ(RET_SUCCESS, _dict_parser->get_column_data(4, &col_4));
    EXPECT_EQ(col_4_gt.size(), col_4.size());
    for (size_t i = 0; i < col_4_gt.size(); ++i) {
        EXPECT_DOUBLE_EQ(col_4_gt[i], col_4[i]);
    }

    double col_5 = 0.0;
    EXPECT_EQ(RET_SUCCESS, _dict_parser->get_column_data(5, &col_5));
    EXPECT_DOUBLE_EQ(-1213.023, col_5);
}

TEST_F(DictParserTest, case_user_defined_type) {
    std::string line_1 = "haha\t19 8.23 Peter\t4:4,2,5,-1\t42\n";
    EXPECT_EQ(RET_SUCCESS, _dict_parser->parse_one_line(line_1));

    std::string col_0 = "";
    EXPECT_EQ(RET_SUCCESS, _dict_parser->get_column_data(0, &col_0));
    EXPECT_EQ("haha", col_0);

    FooStruct col_1;
    EXPECT_EQ(RET_SUCCESS, _dict_parser->get_column_data(1, &col_1));
    EXPECT_EQ(19, col_1.a);
    EXPECT_EQ(8.23, col_1.b);
    EXPECT_EQ("Peter", col_1.c);

    std::vector<int> col_2;
    std::vector<int> gt_col_2 = {4, 2, 5, -1};
    EXPECT_EQ(RET_SUCCESS, _dict_parser->get_column_data(2, &col_2));
    EXPECT_EQ(gt_col_2.size(), col_2.size());
    for (size_t i = 0; i < col_2.size(); ++i) {
        EXPECT_EQ(gt_col_2[i], col_2[i]);
    }

    int col_3 = 42;
    EXPECT_EQ(RET_SUCCESS, _dict_parser->get_column_data(3, &col_3));
    EXPECT_EQ(42, col_3);

    std::string line_2 = "235 -0.231 Alice\t5 12314.1231 Bob\t-214 0.000003 Casia\n";
    EXPECT_EQ(RET_SUCCESS, _dict_parser->parse_one_line(line_2));

    FooStruct col_alice;
    EXPECT_EQ(RET_SUCCESS, _dict_parser->get_column_data(0, &col_alice));
    EXPECT_EQ(235, col_alice.a);
    EXPECT_EQ(-0.231, col_alice.b);
    EXPECT_EQ("Alice", col_alice.c);

    FooStruct col_bob;
    EXPECT_EQ(RET_SUCCESS, _dict_parser->get_column_data(1, &col_bob));
    EXPECT_EQ(5, col_bob.a);
    EXPECT_EQ(12314.1231, col_bob.b);
    EXPECT_EQ("Bob", col_bob.c);

    FooStruct col_casia;
    EXPECT_EQ(RET_SUCCESS, _dict_parser->get_column_data(2, &col_casia));
    EXPECT_EQ(-214, col_casia.a);
    EXPECT_EQ(0.000003, col_casia.b);
    EXPECT_EQ("Casia", col_casia.c);
}

}  // namespace dictparser
