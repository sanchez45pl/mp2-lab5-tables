#pragma once

#include "table.h"

class Unsorted_table : public Table {
public:
    Unsorted_table() = default;

    void push_back(Row row) {
        table.push_back(row);
    }

    void remove(unsigned int key) {
        for (Row &row: table) {
            if (row.key == key) {
                row.is_deleted = true;
                removed_rows_counter++;
            }
        }
        if (removed_rows_counter > table.size() / 2) {
            for (int i = 0; i < table.size(); i++) {
                if (table[i].is_deleted) {
                    table.erase(table.begin() + i);
                };
            }
            removed_rows_counter = 0;
        }
    }

    Polinom *find(int key) {
        for (Row &row: table) {
            if (row.key == key) return row.polinom;
        }
        return nullptr;
    }
};
