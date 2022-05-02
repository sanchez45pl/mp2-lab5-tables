#pragma once
#include <vector>
#include <list>
#include <cmath>
#include "row.h"


class Hash_table {
public:
    unsigned long size;
    Hash_row *table;

    explicit Hash_table(unsigned long size) : size(size), table(new Hash_row[size]) {};

    void insert(unsigned int key, Polinom *polinom) const {
        unsigned long hash = hash_func(key);
        Hash_row *new_row = new Hash_row(key, polinom);
        Hash_row *current_row = table + hash;
        while (current_row->next_row != nullptr) {
            current_row = current_row->next_row;
        }
        if (table[hash].key == 0) {
            table[hash] = *new_row;
            delete new_row;
        } else {
            current_row->next_row = new_row;
        }
    }

    void remove(unsigned int key) const {
        unsigned long hash = hash_func(key);
        Hash_row *current_row = table + hash;
        if (current_row->next_row == nullptr && current_row->key == key) {
            table[hash].key = 0;
            table[hash].polinom = nullptr;
        } else if (current_row->next_row != nullptr && current_row->key == key) {
            table[hash] = *current_row->next_row;
        } else {
            while (current_row->next_row != nullptr && current_row->next_row->key != key) {
                current_row = current_row->next_row;

            }
            if (current_row->next_row != nullptr && current_row->next_row->key == key) {
                Hash_row *row_to_delete = current_row->next_row;
                current_row->next_row = current_row->next_row->next_row;
                delete row_to_delete;
            }
        }
    }

    Polinom *find(unsigned long key) const {
        unsigned long hash = hash_func(key);
        Hash_row *current_row = &table[hash];
        while (current_row != nullptr || current_row->key != key) {
            current_row = current_row->next_row;
        }
        return current_row->polinom ? current_row->polinom : nullptr;
    }

    unsigned long hash_func(unsigned long key) const {
        return key % size;
    }

    void print() const {
        unsigned int max_key = 0;
        for (int i = 0; i < size; i++) {
            if (table[i].key != 0) {
                Hash_row *current_row = table + i;
                while (current_row) {
                    if (current_row->key > max_key) {
                        max_key = current_row->key;
                    }
                    current_row = current_row->next_row;
                }
            }
        }
        unsigned int max_key_length = (int) log10(max_key);

        for (int j = 0; j < size; j++) {
            if (table[j].key != 0) {
                Hash_row *current_row = table + j;
                while (current_row) {
                    unsigned int current_key_length = (int) log10(current_row->key);
                    cout << current_row->key;
                    for (int k = 0; k < max_key_length - current_key_length; k++) {
                        cout << " ";
                    }
                    cout << " | ";
                    current_row->polinom->print();
                    current_row = current_row->next_row;
                }
            }
        }
        cout << endl;
    }

};

