#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int help() {
    cout << "Usage: ./main <filename>" << endl;

    return -1;
}

long sum(vector<long> numbers) {
    long sum = 0;
    for (int i = 0; i < numbers.size(); i++) {
        sum += numbers[i];
    }
    return sum;
}

int lanternfish(const string &filename) {
    ifstream file(filename);
    vector<long> numbers(10);
    int num;

    if (!file.is_open()) {
        return help();
    }

    while (file >> num) {
        ++numbers[num];

        if (file.peek() == ',') file.ignore();
    }

    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < numbers.size(); j++) {
            if (numbers[j] > 0) {
                if (j - 1 == -1) {
                    numbers[7] += numbers[j];
                    numbers[9] += numbers[j];
                } else {
                    numbers[j - 1] += numbers[j];
                }
                numbers[j] -= numbers[j];
            }
        }
    }

    cout << "SUM: " << sum(numbers) << endl;

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return help();

    return lanternfish(argv[1]);
}