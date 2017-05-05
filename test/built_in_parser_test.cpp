#include <climits>
#include <cmath>
#include <string>

#include <gtest/gtest.h>

#include "built_in_parser.h"

namespace dictparser {

///////////////////////////////////////////////////////////////////////////////
// Test parse int values

#if 1
TEST(ParseIntTest, Positive) {
    int result_20 = 0;
    std::string str_20 = "20";
    ASSERT_TRUE(parse(str_20, &result_20));
    EXPECT_EQ(20, result_20);

    int result_728349352 = 0;
    std::string str_728349352 = "728349352";
    ASSERT_TRUE(parse(str_728349352, &result_728349352));
    EXPECT_EQ(728349352, result_728349352);    

    int result_INT_MAX = 0;
    std::string str_INT_MAX = std::to_string(INT_MAX);
    ASSERT_TRUE(parse(str_INT_MAX, &result_INT_MAX));
    EXPECT_EQ(INT_MAX, result_INT_MAX);    
}

TEST(ParseIntTest, Negative) {
    int result_negative1 = 0;
    std::string str_negative1 = "-99281";
    ASSERT_TRUE(parse(str_negative1, &result_negative1));
    EXPECT_EQ(-99281, result_negative1);

    int result_negative2 = 0;
    std::string str_negative2 = "-3";
    ASSERT_TRUE(parse(str_negative2, &result_negative2));
    EXPECT_EQ(-3, result_negative2);
}

TEST(ParseIntTest, Zero) {
    int result_zero = -1;
    std::string str_zero = "0";
    ASSERT_TRUE(parse(str_zero, &result_zero));
    EXPECT_EQ(0, result_zero);
}

TEST(ParseIntTest, Invalid) {
    int result_invalid = -1;
    std::string str_invalid = "asdf*1";
    ASSERT_FALSE(parse(str_invalid, &result_invalid));
    EXPECT_EQ(0, result_invalid);
}

///////////////////////////////////////////////////////////////////////////////
// Test parse float(built-in double) values

TEST(ParseFloatTest, Positive) {
    const double EPS = 1e-10;

    double result_1 = 0.0f;
    std::string str_1 = "4.19234878";
    ASSERT_TRUE(parse(str_1, &result_1));
    ASSERT_TRUE(fabs(result_1 - 4.19234878) < EPS);

    double result_2 = 0.0f;
    std::string str_2 = "1321541234.1";
    ASSERT_TRUE(parse(str_2, &result_2));
    ASSERT_TRUE(fabs(result_2 - 1321541234.1) < EPS);

    double result_3 = -1.0f;
    std::string str_3 = "0.00001";
    ASSERT_TRUE(parse(str_3, &result_3));
    ASSERT_TRUE(fabs(result_3 - 0.00001) < EPS);
}

TEST(ParseFloatTest, Negative) {
    const double EPS = 1e-10;

    double result_1 = 0.0f;
    std::string str_1 = "-21.363859173";
    ASSERT_TRUE(parse(str_1, &result_1));
    ASSERT_TRUE(fabs(-21.363859173 - result_1) < EPS);

    double result_2 = 0.0f;
    std::string str_2 = "-827192437.234";
    ASSERT_TRUE(parse(str_2, &result_2));
    ASSERT_TRUE(fabs(-827192437.234 - result_2) < EPS);

    double result_3 = 1.0f;
    std::string str_3 = "-0.00001";
    ASSERT_TRUE(parse(str_3, &result_3));
    ASSERT_TRUE(fabs(-0.00001 - result_3) < EPS);
}

TEST(ParseFloatTest, Zero) {
    const double EPS = 1e-10;

    double result_1 = 1.0;
    std::string str_1 = "0.0";
    ASSERT_TRUE(parse(str_1, &result_1));
    ASSERT_TRUE(fabs(result_1) < EPS);

    double result_2 = 1.0;
    std::string str_2 = "0.00000";
    ASSERT_TRUE(parse(str_2, &result_2));
    ASSERT_TRUE(fabs(result_2) < EPS);

    double result_3 = 1.0;
    std::string str_3 = "-0.0000000";
    ASSERT_TRUE(parse(str_3, &result_3));
    ASSERT_TRUE(fabs(result_3) < EPS);
}

TEST(ParseFloatTest, Invalid) {
    double result_1 = 1.0;
    std::string str_1 = "0.0.0";
    ASSERT_FALSE(parse(str_1, &result_1));

    double result_2 = 0.0;
    std::string str_2 = "asdfgaq**0.0.0";
    ASSERT_FALSE(parse(str_2, &result_2));

    double result_3 = 0.0;
    std::string str_3 = "-hfgaq$^&!";
    ASSERT_FALSE(parse(str_3, &result_3));
}

///////////////////////////////////////////////////////////////////////////////
// Test parse strings

TEST(ParseStringTest, CppStr) {
    std::string result_1;
    std::string str_1 = "";
    ASSERT_FALSE(parse(str_1, &result_1));

    std::string result_2;
    std::string str_2 = "u2834na*&1A.";
    ASSERT_TRUE(parse(str_2, &result_2));
    EXPECT_EQ(std::string("u2834na*&1A."), result_2);

    std::string result_3;
    std::string str_3 = "oo   asdf --- __ !!( a";
    ASSERT_TRUE(parse(str_3, &result_3));
    EXPECT_EQ("oo   asdf --- __ !!( a", result_3);
}

TEST(ParseStringTest, CStr) {
    char result_1[MAX_CSTR_LENGTH];
    std::string str_1 = "";
    ASSERT_FALSE(parse(str_1, MAX_CSTR_LENGTH, result_1));

    char result_2[MAX_CSTR_LENGTH];
    std::string str_2 = "** _ 1adf 23 --$@ ad ";
    ASSERT_TRUE(parse(str_2, MAX_CSTR_LENGTH, result_2));
    EXPECT_STREQ("** _ 1adf 23 --$@ ad ", result_2);    
}

///////////////////////////////////////////////////////////////////////////////
// Test parse arrays

TEST(ParseArrayTest, IntArray) {
    std::vector<int> result_1;
    std::string str_1 = "3:4,2,5";
    std::vector<int> gt_1 = {4, 2, 5};
    ASSERT_TRUE(parse(str_1, &result_1));
    EXPECT_EQ(gt_1.size(), result_1.size());
    for (size_t i = 0; i < gt_1.size(); ++i) {
        EXPECT_EQ(gt_1[i], result_1[i]);
    }

    std::vector<int> result_2;
    std::string str_2 = "4:4,2,5";
    ASSERT_FALSE(parse(str_2, &result_2));

    std::vector<int> result_3;
    std::string str_3 = "1:4,2,5";
    ASSERT_FALSE(parse(str_3, &result_3));

    std::vector<int> result_4;
    std::string str_4 = "1:123";
    std::vector<int> gt_4 = {123};
    ASSERT_TRUE(parse(str_4, &result_4));
    EXPECT_EQ(gt_4.size(), result_4.size());
    for (size_t i = 0; i < gt_4.size(); ++i) {
        EXPECT_EQ(gt_4[i], result_4[i]);
    }

    std::vector<int> result_5;
    std::string str_5 = "100:691,155,-318,-1000,-978,641,-357,731,848,961,978,-609,767,77,"
            "766,-157,-114,-346,394,800,-399,115,105,-126,891,-103,146,675,188,479,434,-103,"
            "687,339,865,977,886,-902,-565,145,389,-461,-371,-993,316,-502,305,423,-486,312,"
            "431,-836,313,380,-381,758,756,669,-677,-106,429,136,-361,-219,-407,-97,-863,461,"
            "-72,-778,867,182,-569,7,-327,275,-793,-799,-894,-514,739,351,-558,-140,932,414,"
            "-55,150,-555,117,199,-298,-221,378,-976,-834,-218,708,-153,-6";
    std::vector<int> gt_5 = {691, 155, -318, -1000, -978, 641, -357, 731, 848, 961, 978, -609, 
            767, 77, 766, -157, -114, -346, 394, 800, -399, 115, 105, -126, 891, -103, 146, 675, 
            188, 479, 434, -103, 687, 339, 865, 977, 886, -902, -565, 145, 389, -461, -371, 
            -993, 316, -502, 305, 423, -486, 312, 431, -836, 313, 380, -381, 758, 756, 669, 
            -677, -106, 429, 136, -361, -219, -407, -97, -863, 461, -72, -778, 867, 182, -569, 
            7, -327, 275, -793, -799, -894, -514, 739, 351, -558, -140, 932, 414, -55, 150, 
            -555, 117, 199, -298, -221, 378, -976, -834, -218, 708, -153, -6};
    ASSERT_TRUE(parse(str_5, &result_5));
    EXPECT_EQ(gt_5.size(), result_5.size());
    for (size_t i = 0; i < gt_5.size(); ++i) {
        EXPECT_EQ(gt_5[i], result_5[i]);
    }
}

TEST(ParseArrayTest, FloatArray) {
    const double EPS = 1e-10;

    std::vector<double> result_1;
    std::string str_1 = "1:0.01";
    std::vector<double> gt_1 = {0.01};
    ASSERT_TRUE(parse(str_1, &result_1));
    EXPECT_EQ(gt_1.size(), result_1.size());
    for (size_t i = 0; i < gt_1.size(); ++i) {
        ASSERT_TRUE(fabs(gt_1[i] - result_1[i]) < EPS);
    }

    std::vector<double> result_2;
    std::string str_2 = "-2:0.01";
    ASSERT_FALSE(parse(str_2, &result_2));

    std::vector<double> result_3;
    std::string str_3 = "100:0.01";
    ASSERT_FALSE(parse(str_3, &result_3));

    std::vector<double> result_4;
    std::string str_4 = "5:0.01,1,2.13,3.14,-20";
    std::vector<double> gt_4 = {0.01, 1, 2.13, 3.14, -20};
    ASSERT_TRUE(parse(str_4, &result_4));
    EXPECT_EQ(gt_4.size(), result_4.size());
    for (size_t i = 0; i < gt_4.size(); ++i) {
        ASSERT_TRUE(fabs(gt_4[i] - result_4[i]) < EPS);
    }

    std::vector<double> result_5;
    std::string str_5 = "100:46.9099785272,-58.2913738385,-52.5710979983,-27.0809999501,"
            "-77.2640265239,-35.6410330209,-62.907663427,-48.7332592494,95.5716974826,"
            "52.6491159437,60.8967761175,69.355093274,-25.0175834249,-50.1815139153,"
            "78.3912355809,-8.29265352869,64.1757150057,-32.953480861,35.4525006775,"
            "-12.094833385,-24.9898195958,32.5411098343,-55.8372964589,-70.2192331615,"
            "-62.96920082,63.7853017479,-55.5445305892,-86.2485580191,-47.3909928181,"
            "-73.6696989297,-19.7134107976,33.9102862479,-16.5225188274,-70.818483918,"
            "-22.5134225703,78.1364878778,62.3458581126,-59.6287267591,51.3018856736,"
            "67.2984960551,-53.4852151764,97.7375034363,-33.137367966,-51.3232671008,"
            "11.1892007222,-35.0122859954,-84.1594047693,30.6349051465,17.4452004633,"
            "4.74352411365,-45.9827158184,98.2232665379,66.1281088544,60.7267345245,"
            "-57.9973816556,32.5336567986,-9.72337581714,-18.0534639021,-85.8769403683,"
            "-1.49959573311,54.7288186142,-27.0839267398,66.0280501106,81.6086169809,"
            "67.8730635228,49.5252084751,-62.4264557088,-8.60493555519,-81.3543788119,"
            "68.4205140143,94.5586003215,36.3086112037,-76.1712995129,-11.1806851359,"
            "54.8383706983,-68.8451795284,42.9064730883,-19.6327891548,-21.2154731785,"
            "-22.7708111227,-0.871618559285,-16.2299926784,-68.911711259,63.1498876188,"
            "28.0903888348,14.5415837382,97.546223714,37.6736075111,-72.9833738732,"
            "39.3897589887,50.1795255415,94.250786672,34.687694972,-2.82471437001,"
            "77.2342356368,-92.9804482073,-86.4105085865,83.3527526937,94.1207450396,"
            "94.8065460953";
    std::vector<double> gt_5 = {46.9099785272, -58.2913738385, -52.5710979983, -27.0809999501, 
            -77.2640265239, -35.6410330209, -62.907663427, -48.7332592494, 95.5716974826, 
            52.6491159437, 60.8967761175, 69.355093274, -25.0175834249, -50.1815139153, 
            78.3912355809, -8.29265352869, 64.1757150057, -32.953480861, 35.4525006775, 
            -12.094833385, -24.9898195958, 32.5411098343, -55.8372964589, -70.2192331615, 
            -62.96920082, 63.7853017479, -55.5445305892, -86.2485580191, -47.3909928181, 
            -73.6696989297, -19.7134107976, 33.9102862479, -16.5225188274, -70.818483918, 
            -22.5134225703, 78.1364878778, 62.3458581126, -59.6287267591, 51.3018856736, 
            67.2984960551, -53.4852151764, 97.7375034363, -33.137367966, -51.3232671008, 
            11.1892007222, -35.0122859954, -84.1594047693, 30.6349051465, 17.4452004633, 
            4.74352411365, -45.9827158184, 98.2232665379, 66.1281088544, 60.7267345245, 
            -57.9973816556, 32.5336567986, -9.72337581714, -18.0534639021, -85.8769403683, 
            -1.49959573311, 54.7288186142, -27.0839267398, 66.0280501106, 81.6086169809, 
            67.8730635228, 49.5252084751, -62.4264557088, -8.60493555519, -81.3543788119, 
            68.4205140143, 94.5586003215, 36.3086112037, -76.1712995129, -11.1806851359, 
            54.8383706983, -68.8451795284, 42.9064730883, -19.6327891548, -21.2154731785, 
            -22.7708111227, -0.871618559285, -16.2299926784, -68.911711259, 63.1498876188, 
            28.0903888348, 14.5415837382, 97.546223714, 37.6736075111, -72.9833738732, 
            39.3897589887, 50.1795255415, 94.250786672, 34.687694972, -2.82471437001, 
            77.2342356368, -92.9804482073, -86.4105085865, 83.3527526937, 94.1207450396, 
            94.8065460953};
    ASSERT_TRUE(parse(str_5, &result_5));
    EXPECT_EQ(gt_5.size(), result_5.size());
    for (size_t i = 0; i < gt_5.size(); ++i) {
        ASSERT_TRUE(fabs(gt_5[i] - result_5[i]) < EPS);
    }
}

TEST(ParseArrayTest, CppStrArray) {
    std::vector<std::string> result_1;
    std::string str_1 = "30:Four,score,and,seven,years,ago,our,fathers,brought,forth,on,"
            "this,continent,a,new,nation,conceived,in,Liberty,and,dedicated,to,the,"
            "proposition,that,all,men,are,created,equal";
    std::vector<std::string> gt_1 = {"Four", "score", "and", "seven", "years", "ago", 
            "our", "fathers", "brought", "forth", "on", "this", "continent", "a", "new", 
            "nation", "conceived", "in", "Liberty", "and", "dedicated", "to", "the", 
            "proposition", "that", "all", "men", "are", "created", "equal"};
    ASSERT_TRUE(parse(str_1, &result_1));
    EXPECT_EQ(gt_1.size(), result_1.size());
    for (size_t i = 0; i < gt_1.size(); ++i) {
        EXPECT_EQ(gt_1[i], result_1[i]);
    }

    std::vector<std::string> result_2;
    std::string str_2 = "3:hello,world";
    ASSERT_FALSE(parse(str_2, &result_2));

    std::vector<std::string> result_3;
    std::string str_3 = "0:hello,world";
    ASSERT_FALSE(parse(str_3, &result_3));
}

// There is no way to store C-style arrays in vectors (or in any other standard library container).
// std::vector<char*> cannot be used to "store" C-style arrays.
/*
TEST(ParseArrayTest, CStrArray) {
    
}
*/

#endif
}  // namespace dictparser
