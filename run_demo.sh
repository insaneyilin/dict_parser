#!/bin/sh
demo_bin_file="./build/demo/dict_parser_demo"

if [ ! -f "$demo_bin_file" ]; then
    echo "$demo_bin_file not exists!"
    echo "Please run build.sh first."
    exit 0
fi

$demo_bin_file "./conf/demo_columns_types.config" "./data/demo_dict_file.txt"

