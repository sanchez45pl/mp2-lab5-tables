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

    void remove(unsigned int key) {
        unsigned long index = binary_search(key);
        if (index != -1){
            table[index].is_deleted = true;
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

    Polinom *find(unsigned long key) {
        unsigned long index = binary_search(key);
        if (index != -1){
            return  table[index].polinom;
        } else {
            return nullptr;
        }
    }

private:
    unsigned long binary_search(unsigned long key) {
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
                return middle;
            }
            if (left > right) {
                return -1;
            }
        }
    }
};
