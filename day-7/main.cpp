#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int help() {
    cout << "Usage: ./main <filename>" << endl;

    return -1;
}

int calculateStep(int j, int i) {
    int step = 0, counter = 1;
    while (j != i) {
        step += counter++;

        j > i ? j-- : j++;
    }
    return step;
}

void calculateSum(int start, int end, int i, int &sum, vector<int> numbers, bool type, vector<int> &steps) {
    int index;

    for (int j = start; j < end; j++) {
        if (!type)
            i > j ? sum += (i - j) * numbers[j] : sum += (j - i) * numbers[j];
        else {
            index = i > j ? i - j : j - i;
            if (steps[index] == 0) steps[index] = calculateStep(j, i);
            sum += numbers[j] * steps[index];
        }
    }
}

int crabs(const string &filename, bool type) {
    ifstream file(filename);
    vector<int> numbers;
    vector<int> steps;
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

    if (type)
        steps = vector<int>(numbers.size());

    for (int i = 0; i < numbers.size(); i++) {
        sum = 0;
        calculateSum(0, i, i, sum, numbers, type, steps);
        calculateSum(i + 1, numbers.size(), i, sum, numbers, type, steps);
        if (sum < min) min = sum;
    }

    cout << min << endl;

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return help();

    return crabs(argv[1], true);
}