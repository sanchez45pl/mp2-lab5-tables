#pragma once

#include "tables/hash_table.h"
#include "tables/sorted_table.h"
#include "tables/unsorted_table.h"

class Union_of_tables {
public:
    Hash_table hash_table;
    Sorted_table sorted_table;
    Unsorted_table unsorted_table;

    Union_of_tables() : hash_table(Hash_table(64)),
                        sorted_table(Sorted_table()),
                        unsorted_table(Unsorted_table()) {};

    void insert(unsigned int key, Polinom *polinom) {
        hash_table.insert(key, polinom);
        sorted_table.insert(key, polinom);
        unsorted_table.insert(key, polinom);
    }

    void remove(unsigned int key) {
        hash_table.remove(key);
        sorted_table.remove(key);
        unsorted_table.remove(key);
    }

    Polinom *find(unsigned long key) {
        Polinom *h_polinom = hash_table.find(key);
        Polinom *s_polinom = sorted_table.find(key);
        Polinom *u_polinom = unsorted_table.find(key);
        return h_polinom;
    }

    void print() {
        cout << "Hash table" << endl;
        hash_table.print();
        cout << "Sorted table" << endl;
        sorted_table.print();
        cout << "Unsorted table" << endl;
        unsorted_table.print();
        cout << endl;
    }
};
