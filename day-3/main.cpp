#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int help() {
    cout << "Usage: ./main <filename>" << endl;

    return -1;
}

int binaryDiagnostic(const string &filename) {
    ifstream file(filename);
    string binaryNumber;
    vector<int> ones;
    int counter = 0;
    uint gamma = 0, epsilon = 0;
    bool first = true;

    if (!file.is_open()) {
        return help();
    }

    while (file >> binaryNumber) {
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
            cout << "1";
            gamma ^= (-1UL ^ gamma) & (1UL << (ones.size() - 1 - i));
        } else {
            epsilon ^= (-1UL ^ epsilon) & (1UL << (ones.size() - 1 - i));
        }
    }
    cout << gamma << " " << epsilon << " " << gamma * epsilon << endl;

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return help();

    return binaryDiagnostic(argv[1]);
}