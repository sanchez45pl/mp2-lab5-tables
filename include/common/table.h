#pragma once

#include <vector>
#include <cmath>
#include "row.h"

class Table {
public:
    vector<Row> table;
    unsigned long removed_rows_counter;

    Table() : removed_rows_counter(0) {};

    void clear(){
        if (removed_rows_counter > table.size() / 2) {
            for (int i = 0; i < table.size(); i++) {
                if (table[i].is_deleted) {
                    table.erase(table.begin() + i);
                }
            }
            removed_rows_counter = 0;
        }
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
                cout << row.key;
                for (int i = 0; i < max_key_length - current_key_length; i++) {
                    cout << " ";
                }
                cout << " | ";
                row.polinom->print();
            }
        }
    }
};