#pragma once

#include "polinom.h"

struct Row {
    unsigned int key;
    Polinom *polinom;
    bool is_deleted;

    Row(unsigned int key, Polinom *polinom) :
            key(key),
            polinom(polinom),
            is_deleted(false) {};
};