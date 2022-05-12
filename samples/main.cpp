#include "include/union_of_tables.h"
#include "logger.h"

using namespace std;

void save(Union_of_tables *tables, Polinom *new_polinom){
    int save = false;
    unsigned long key = 0;
    cout << "Do you want to save this polinom in table?" << endl;
    cout << "\t " << "1 - Yes" << endl;
    cout << "\t " << "0 - No" << endl;
    cin >> save;

    if (save){
        while (key == 0) {
            cout << "Enter key of polinom: ";
            cin >> key;
            cout << "Done" << endl << endl;
        }
        tables->insert(key, new_polinom);
    } else {
        cout << endl;
    }
}


int main() {
    int last_id = 1;
    int main_menu_command = true;
    Union_of_tables created_polinoms = Union_of_tables();

    cout << "Polinom CLI\n" << endl;
    while (main_menu_command) {
        cout << "Choose command:" << endl;
        cout << "\t" << "1 - create polinom" << endl;
        cout << "\t" << "2 - find polinom" << endl;
        cout << "\t" << "3 - show created polinoms" << endl;
        cout << "\t" << "4 - operate with created polinoms" << endl;
        cout << "\t" << "0 - exit" << endl;
        cin >> main_menu_command;
        cout << endl;
        if (main_menu_command == 1) {
            auto *new_polinom = new Polinom();
            float coefficient;
            int powers;
            int should_continue = true;
            unsigned long key = 0;
            cout << "Creating polinom" << endl;
            while (should_continue) {
                cout << "\t" << "Adding monom:" << endl;
                cout << "\t " << "Enter coefficient of monom: ";
                cin >> coefficient;
                cout << "\t " << "Enter xyz - powers of monom: ";
                cin >> powers;
                new_polinom->add_monom(coefficient, powers);
                cout << "Add another one?" << endl;
                cout << "\t " << "1 - Yes" << endl;
                cout << "\t " << "0 - No" << endl;
                cin >> should_continue;
            }
            while (key == 0) {
                cout << "Enter key of polinom: ";
                cin >> key;
                cout << "Done" << endl << endl;
            }
            created_polinoms.insert(key, new_polinom);
        }else if (main_menu_command == 2) {
            unsigned long key = 0;
            while (key == 0) {
                cout << "Enter key of polinom: ";
                cin >> key;
            }
            Polinom *polinom = created_polinoms.find(key);
            if (polinom) {
                polinom->print();
                cout << endl;
            } else {
                cout << "Not found" << endl << endl;
            }
        } else if (main_menu_command == 3) {
            created_polinoms.print();
        } else if (main_menu_command == 4) {
            int operation_menu_command = true;
            while (operation_menu_command) {
                cout << "Select operation:" << endl;
                cout << "\t" << "1 - addition" << endl;
                cout << "\t" << "2 - subtraction" << endl;
                cout << "\t" << "3 - multiplication by constant" << endl;
                cout << "\t" << "4 - multiplication by polinom" << endl;
                cout << "\t" << "0 - back" << endl;
                cin >> operation_menu_command;
                cout << endl;
                if (operation_menu_command == 1) {
                    unsigned long key1, key2;


                    Polinom *new_polinom;
                    cout << "Select two polinoms:" << endl;
                    cout << "First: ";
                    cin >> key1;
                    cout << "Second: ";
                    cin >> key2;
                    new_polinom = *created_polinoms.find(key1) + *created_polinoms.find(key2);
                    cout << "Result: ";
                    new_polinom->print();

                    save(&created_polinoms, new_polinom);

                } else if (operation_menu_command == 2) {
                    int first_polinom, second_polinom;
                    Polinom *new_polinom;
                    cout << "Select two polinoms:" << endl;
                    cout << "First: ";
                    cin >> first_polinom;
                    cout << "Second: ";
                    cin >> second_polinom;
                    new_polinom = *created_polinoms.find(first_polinom) - *created_polinoms.find(second_polinom);
                    cout << "Result: ";
                    new_polinom->print();

                    save(&created_polinoms, new_polinom);


                } else if (operation_menu_command == 3) {
                    int polinom, constant;
                    Polinom *new_polinom;
                    cout << "Select polinom: ";
                    cin >> polinom;
                    cout << "Enter constant: ";
                    cin >> constant;
                    new_polinom = constant * *created_polinoms.find(polinom);
                    cout << "Result: ";
                    new_polinom->print();

                    save(&created_polinoms, new_polinom);


                } else if (operation_menu_command == 4) {
                    int first_polinom, second_polinom;
                    Polinom *new_polinom;
                    cout << "Select two polinoms:" << endl;
                    cout << "First: ";
                    cin >> first_polinom;
                    cout << "Second: ";
                    cin >> second_polinom;
                    new_polinom = *created_polinoms.find(first_polinom) * *created_polinoms.find(second_polinom);
                    cout << "Result: ";
                    new_polinom->print();

                    save(&created_polinoms, new_polinom);
                }
            }
        }
    }
    return 0;
}