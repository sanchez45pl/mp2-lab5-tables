#pragma once

#include "polinom.h"

struct Row {
    unsigned long key;
    Polinom *polinom;
    bool is_deleted;

    Row(unsigned long key, Polinom *polinom) :
            key(key),
            polinom(polinom),
            is_deleted(false) {};
};