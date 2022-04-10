#include <vector>
#include <cmath>
#include "row.h"

class Table {
public:
    std::vector<Row> table;
    unsigned int removed_rows_counter;

    Table(): removed_rows_counter(0){};

    virtual void print() {
        unsigned int max_key = 0;
        for (Row &row: table) {
            if (row.key > max_key) max_key = row.key;
        }
        unsigned int max_key_length = (int)log10(max_key);

        for (Row &row: table) {
            unsigned int current_key_length = (int)log10(row.key);
            std::cout << row.key;
            for (int i = 0; i < max_key_length - current_key_length; i++) {
                std::cout << " ";
            }
            std::cout << " | ";
            row.polinom->print();
        }
    }
};