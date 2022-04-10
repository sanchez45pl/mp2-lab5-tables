#pragma once

#include <vector>
#include <cmath>
#include "row.h"

class Table {
public:
    std::vector<Row> table;
    unsigned int removed_rows_counter;

    Table() : removed_rows_counter(0) {};

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

    virtual void print() {
        unsigned int max_key = 0;
        for (Row &row: table) {
            if (row.key > max_key) max_key = row.key;
        }
        unsigned int max_key_length = (int) log10(max_key);

        for (Row &row: table) {
            if (!row.is_deleted) {
                unsigned int current_key_length = (int) log10(row.key);
                std::cout << row.key;
                for (int i = 0; i < max_key_length - current_key_length; i++) {
                    std::cout << " ";
                }
                std::cout << " | ";
                row.polinom->print();
            }
        }
    }
};