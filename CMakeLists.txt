cmake_minimum_required(VERSION 3.21)
project(mp2-lab5-tables)

set(CMAKE_CXX_STANDARD 23)

include_directories(.)
include_directories(include)



add_executable(mp2-lab5-tables samples/main.cpp include/tables/unsorted_table.h include/tables/sorted_table.h include/tables/hash_table.h include/polinom.h include/row.h include/table.h)
add_subdirectory(google_tests)