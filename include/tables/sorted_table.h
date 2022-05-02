#pragma once

#include "include/common/table.h"

class Sorted_table : public Table {
public:
    Sorted_table() = default;

    void insert(unsigned int key, Polinom *polinom) {
        Row new_row = Row(key, polinom);
        auto iterator = table.begin();
        while (iterator != table.end() && iterator->key < key) {
            iterator++;
        }
        table.insert(iterator, new_row);
    }

    void remove(unsigned int key) {
        Row *row = binary_search(key);
        if (row) {
            row->is_deleted = true;
        }
        clear();
    }

    Polinom *find(unsigned long key) {
        Row *row = binary_search(key);
        if (row) {
            return row->polinom;
        }
        return nullptr;
    }

private:
    Row *binary_search(unsigned long key) {
        unsigned long middle;
        unsigned long left = 0;
        unsigned long right = table.size() - 1;
        while (true) {
            middle = (left + right) / 2;

            if (key < table[middle].key) {
                right = middle - 1;
            } else if (key > table[middle].key) {
                left = middle + 1;
            } else {
                return &table[middle];
            }
            if (left > right) {
                return nullptr;
            }
        }
    }
};
