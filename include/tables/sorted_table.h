#pragma once

#include "table.h"

class Sorted_table : public Table {
public:
    Sorted_table() = default;

    void insert(Row row) {
        auto iterator = table.begin();
        while (iterator != table.end() && iterator->key < row.key) {
            iterator++;
        }
        table.insert(iterator, row);
    }
};
