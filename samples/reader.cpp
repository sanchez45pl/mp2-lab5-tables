#include <fstream>
#include "iostream"
#include <thread>

using namespace std;

int main() {
    while(true){
        ifstream in;

        string unsorted_table;
        string sorted_table;
        string hash_table;
        string result;

        in.open("./unsorted_table");
        getline(in, unsorted_table);
        in.close();

        in.open("./sorted_table");
        getline(in, sorted_table);
        in.close();

        in.open("./hash_table");
        getline(in, hash_table);
        in.close();

        cout << "Unsorted_table: " << unsorted_table;
        cout << " Sorted_table: " << sorted_table;
        cout << " Hash_table: " << hash_table;
        cout << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
};