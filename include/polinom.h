#include <iostream>

using namespace std;

struct Monom {
    float coefficient;
    int powers;
    Monom *next_monom;
    Monom *previous_monom;

    Monom(float coefficient, int powers) {
        if (powers > 999 || powers < 0) {
            throw runtime_error("Cannot create monom: power out of range");
        } else {
            this->coefficient = coefficient;
            this->powers = powers;
            this->next_monom = nullptr;
            this->previous_monom = nullptr;
        }
    }

    int x_power() const { return this->powers / 100; }

    int y_power() const { return this->powers / 10 % 10; }

    int z_power() const { return this->powers % 10; }


};

class Polinom {
public:
    Monom *first_monom;
    Monom *last_monom;

    Polinom() : first_monom(nullptr), last_monom(nullptr) {};

    void add_monom(float coefficient, int powers) {
        Monom *new_monom = new Monom(coefficient, powers);
        Monom *current_monom = find_where_to_insert(new_monom);
        insert(current_monom, new_monom);
        bring_similar();
    }

    void print() {
        if (is_empty()) return;
        Monom *current_monom = this->first_monom;
        while (current_monom) {
            if (current_monom->coefficient > 0 && current_monom != this->first_monom) cout << " + ";
            if (current_monom->coefficient < 0 && current_monom == this->first_monom) cout << " -";
            if (current_monom->coefficient < 0 && current_monom != this->first_monom) cout << " - ";
            cout << abs(current_monom->coefficient);
            if (current_monom->powers != 0) cout << "*";
            if (current_monom->x_power()) {
                cout << "(x^" << current_monom->x_power() << ")";
            }
            if (current_monom->y_power()) {
                cout << "(y^" << current_monom->y_power() << ")";
            }
            if (current_monom->z_power()) {
                cout << "(z^" << current_monom->z_power() << ")";
            }
            current_monom = current_monom->next_monom;
        }
        cout << endl;
    }

private:
    bool is_empty() const {
        return this->first_monom == nullptr;
    }

    void push_back(Monom *new_monom) {
        new_monom->previous_monom = this->last_monom;
        this->last_monom->next_monom = new_monom;
        this->last_monom = new_monom;
    }

    void push_front(Monom *new_monom) {
        new_monom->next_monom = this->first_monom;
        this->first_monom->previous_monom = new_monom;
        this->first_monom = new_monom;
    }

    Monom *find_where_to_insert(Monom *new_monom) const {
        Monom *current_monom = this->first_monom;
        while (current_monom && current_monom->powers >= new_monom->powers) {
            current_monom = current_monom->next_monom;
        }
        return current_monom;
    }

    void insert(Monom *current_monom, Monom *new_monom) {
        if (is_empty()) {
            this->first_monom = new_monom;
            this->last_monom = new_monom;
        } else if (current_monom == this->first_monom) {
            push_front(new_monom);
        } else if (current_monom == nullptr) {
            push_back(new_monom);
        } else {
            new_monom->previous_monom = current_monom->previous_monom;
            current_monom->previous_monom->next_monom = new_monom;
            new_monom->next_monom = current_monom;
            current_monom->previous_monom = new_monom;
        }
    }

    void bring_similar() {
        Monom *current_monom = this->first_monom->next_monom;
        while (current_monom) {
            if (current_monom->previous_monom->powers == current_monom->powers) {
                if (current_monom->previous_monom->coefficient + current_monom->coefficient == 0) {
                    remove(current_monom->previous_monom);
                    remove(current_monom);
                    return;
                } else {
                    current_monom->previous_monom->coefficient += current_monom->coefficient;
                    remove(current_monom);
                    return;
                }
            }
            current_monom = current_monom->next_monom;
        }
    }

    void remove(Monom *monom_to_remove) {
        if (monom_to_remove == this->last_monom) {
            this->last_monom = this->last_monom->previous_monom;
            this->last_monom->next_monom = nullptr;
            delete monom_to_remove;
        } else {
            monom_to_remove->previous_monom->next_monom = monom_to_remove->next_monom;
            monom_to_remove->next_monom->previous_monom = monom_to_remove->previous_monom;
            delete monom_to_remove;
        }
    }
};

Polinom *operator+(Polinom first_polinom, Polinom second_polinom) {
    Polinom *new_polinom = new Polinom;
    Monom *current_monom = first_polinom.first_monom;
    while (current_monom) {
        new_polinom->add_monom(current_monom->coefficient, current_monom->powers);
        current_monom = current_monom->next_monom;
    }
    current_monom = second_polinom.first_monom;
    while (current_monom) {
        new_polinom->add_monom(current_monom->coefficient, current_monom->powers);
        current_monom = current_monom->next_monom;
    }
    return new_polinom;
}

Polinom *operator-(Polinom first_polinom, Polinom second_polinom) {
    Polinom *new_polinom = new Polinom;
    Monom *current_monom = first_polinom.first_monom;
    while (current_monom) {
        new_polinom->add_monom(current_monom->coefficient, current_monom->powers);
        current_monom = current_monom->next_monom;
    }
    current_monom = second_polinom.first_monom;
    while (current_monom) {
        new_polinom->add_monom((-1) * current_monom->coefficient, current_monom->powers);
        current_monom = current_monom->next_monom;
    }
    return new_polinom;
}

Polinom *operator*(float number, Polinom polinom) {
    Polinom *new_polinom = new Polinom;
    Monom *current_monom = polinom.first_monom;
    while (current_monom) {
        new_polinom->add_monom(number * current_monom->coefficient, current_monom->powers);
        current_monom = current_monom->next_monom;
    }
    return new_polinom;
}

Polinom *operator*(Polinom first_polinom, Polinom second_polinom) {
    Polinom *new_polinom = new Polinom;
    Monom *current_monom_from_first = first_polinom.first_monom;
    Monom *current_monom_from_second = second_polinom.first_monom;
    while (current_monom_from_first) {
        while (current_monom_from_second) {
            float coefficient = current_monom_from_first->coefficient * current_monom_from_second->coefficient;
            int powers = current_monom_from_first->powers + current_monom_from_second->powers;
            if (powers / 100 < current_monom_from_first->x_power() ||
                powers / 10 % 10 < current_monom_from_first->y_power() ||
                powers % 10 < current_monom_from_first->z_power()) {
                throw runtime_error("Get power out of range while multiplying");
            } else {
                new_polinom->add_monom(coefficient, powers);
                current_monom_from_second = current_monom_from_second->next_monom;
            }

        }
        current_monom_from_first = current_monom_from_first->next_monom;
        current_monom_from_second = second_polinom.first_monom;
    }
    return new_polinom;
}
