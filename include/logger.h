#pragma once

#include <fstream>

class Logger {
    string name;
    unsigned long n;
    std::ofstream out;
public:
    explicit Logger(string name) :
            name(std::move(name)),
            n(0) {
        log();
    };

    void log() {
        out.open("./" + name, ios::out);
        out << n;
        out.close();
    }

    void count() {
        n++;
    }

    void count_and_log() {
        count();
        log();
    }
};