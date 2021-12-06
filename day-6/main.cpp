#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int help() {
    cout << "Usage: ./main <filename>" << endl;

    return -1;
}

int lanternfish(const string &filename) {
    ifstream file(filename);
    vector<int> numbers;
    int num;

    if (!file.is_open()) {
        return help();
    }

    while (file >> num) {
        numbers.push_back(num);

        if (file.peek() == ',') file.ignore();
    }

    for (int i = 0; i < 80; i++) {
        for (int j = 0; j < numbers.size(); j++) {
            --numbers[j];

            if (numbers[j] == -1) {
                numbers[j] = 6;
                numbers.push_back(9);
            }
        }
    }
    cout << "SUM: " << numbers.size() << endl;

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return help();

    return lanternfish(argv[1]);
}