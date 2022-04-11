#pragma once

#include "table.h"

class Unsorted_table : public Table {
public:
    Unsorted_table() = default;

    void push_back(Row row) {
        table.push_back(row);
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
