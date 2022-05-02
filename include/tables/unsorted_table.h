#pragma once

#include "include/common/table.h"

class Unsorted_table : public Table {
public:
    Unsorted_table() = default;

    void insert(unsigned int key, Polinom *polinom) {
        Row new_row = Row(key, polinom);
        table.push_back(new_row);
    }

    void remove(unsigned int key) {
        Row *row = linear_search(key);
        if (row) {
            row->is_deleted = true;
        }
        clear();
    }

    Polinom *find(unsigned long key) {
        Row *row = linear_search(key);
        if (row) {
            return row->polinom;
        }
        return nullptr;
    }

private:
     Row* linear_search(unsigned long key){
        for (auto & row : table) {
            if (row.key == key) return &row;
        }
        return nullptr;
    }
};
