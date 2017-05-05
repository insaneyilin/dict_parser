#include "user_type.h"
#include "built_in_parser.h"
#include "dict_parser.h"

using namespace dictparser;

#if 0
int main(int argc, char **argv)
{
    DictParser dict_parser;
    std::string line = "haha\t19 8.23 Peter\t4:4,2,5,-1\t42\n";
    dict_parser.parse_one_line(line);

    FooStruct col_1;
    dict_parser.get_column_data(1, &col_1);

    return 0;
}
#endif
