#pragma once

#include "table.h"

class Unsorted_table : public Table {
public:
    Unsorted_table() = default;

    void push_back(Row row) {
        table.push_back(row);
    }
};
