#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int help() {
    cout << "Usage: ./main <filename>" << endl;

    return -1;
}

int crabs(const string &filename) {
    ifstream file(filename);
    vector<int> numbers;
    int num, sum = 0, min = INT_MAX;

    if (!file.is_open()) {
        return help();
    }

    while (file >> num) {
        while (numbers.size() < num + 1) {
            numbers.push_back(0);
        }
        ++numbers[num];

        if (file.peek() == ',') file.ignore();
    }

    for (int i = 0; i < numbers.size(); i++) {
        sum = 0;
        for (int j = 0; j < i; j++) {
            sum += (i - j) * numbers[j];
        }
        for (int j = i + 1; j < numbers.size(); j++) {
            sum += (j - i) * numbers[j];
        }
        if (sum < min) min = sum;
    }

    cout << min << endl;

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return help();

    return crabs(argv[1]);
}