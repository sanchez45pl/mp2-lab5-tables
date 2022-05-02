#pragma once

#include "polinom.h"

struct Row {
    unsigned long key;
    Polinom *polinom;
    bool is_deleted;

    Row(unsigned long key, Polinom *polinom) : key(key), polinom(polinom), is_deleted(false) {};
};


struct Hash_row {
    unsigned long key;
    Polinom *polinom;
    Hash_row *next_row;


    Hash_row() :
            key(0),
            polinom(nullptr),
            next_row(nullptr) {};

    Hash_row(unsigned long key, Polinom *polinom) :
            key(key),
            polinom(polinom),
            next_row(nullptr){};
};

