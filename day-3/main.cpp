#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int help() {
    cout << "Usage: ./main <filename>" << endl;

    return -1;
}

void erase(vector<string> &binaryNumbers, int index, char value) {
    binaryNumbers.erase(std::remove_if(
            binaryNumbers.begin(), binaryNumbers.end(), [index, value](const string &x) {
                return x[index] != value;
            }), binaryNumbers.end());
}

int toDecimal(const string &binary) {
    uint num = 0;
    for (int i = 0; i < binary.size(); i++) {
        num ^= (-(binary[i] == '1' ? 1UL : 0UL) ^ num) & (1UL << (binary.size() - 1 - i));
    }

    return num;
}

string criteria(vector<string> array, vector<int> ones, char value) {
    int counter = 0;
    while (true) {
        ones[counter] = 0;
        for (int i = 0; i < array.size(); i++) {
            if (array[i][counter] == '1') {
                ones[counter] = ones[counter] + 1;
            }
        }

        if (ones[counter] >= array.size() - ones[counter]) erase(array, counter, value);
        else erase(array, counter, value == '1' ? '0' : '1');

        if (array.size() == 1) break;

        counter++;
    }

    return array[0];
}

int binaryDiagnostic(const string &filename) {
    ifstream file(filename);
    string binaryNumber;
    vector<int> ones;
    vector<string> binaryNumbers;
    int counter = 0;
    uint gamma = 0, epsilon = 0;
    bool first = true;

    if (!file.is_open()) {
        return help();
    }

    while (file >> binaryNumber) {
        binaryNumbers.push_back(binaryNumber);

        if (first) {
            ones = vector<int>(binaryNumber.size(), 0);
            first = false;
        }

        counter++;
        for (int i = 0; i < binaryNumber.size(); i++) {
            if (binaryNumber[i] == '1') {
                ones[i] = ones[i] + 1;
            }
        }
    }

    for (int i = 0; i < ones.size(); i++) {
        if (ones[i] > counter - ones[i]) {
            gamma ^= (-1UL ^ gamma) & (1UL << (ones.size() - 1 - i));
        } else {
            epsilon ^= (-1UL ^ epsilon) & (1UL << (ones.size() - 1 - i));
        }
    }

    cout << gamma * epsilon << " " <<
         toDecimal(criteria(binaryNumbers, ones, '1')) *
         toDecimal(criteria(binaryNumbers, ones, '0')) << endl;

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return help();

    return binaryDiagnostic(argv[1]);
}