#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int help() {
    cout << "Usage: ./main <filename>" << endl;

    return -1;
}

void calculateDepth(int num, int &prev, int &counter, bool &first) {
    if (first) {
        cout << num << " (N/A - no previous measurement)" << endl;
        first = false;
    } else {
        if (num > prev) {
            cout << num << " (increased)" << endl;
            counter++;
        } else {
            cout << num << " (decreased)" << endl;
        }
    }

    prev = num;
}

int basic(ifstream &file) {
    int num, prev = 0, counter = 0;
    bool first = true;

    while (file >> num) {
        calculateDepth(num, prev, counter, first);
    }

    return counter;
}

void calculateSum(int num, int &sum, int &window, vector<int> &sums) {
    if (window > 0) {
        sum += num;
    }

    window--;

    if (window == 0) {
        sums.push_back(sum);
        sum = 0;
        window = 3;
    }
}

int threeMeasurementSlidingWindow(ifstream &file) {
    bool first = true;
    int prev, counter = 0, sums[3] = {0, 0, 0}, windows[3] = {3, 3, 3};
    vector<int> numbers, sumVector;

    std::copy(std::istream_iterator<int>(file), std::istream_iterator<int>(),
              std::back_inserter(numbers));

    for (int i = 0; i < numbers.size(); i++) {
        calculateSum(numbers[i], sums[0], windows[0], sumVector);
        if (i > 0) calculateSum(numbers[i], sums[1], windows[1], sumVector);
        if (i > 1) calculateSum(numbers[i], sums[2], windows[2], sumVector);
    }

    for (int i = 0; i < sumVector.size(); i++) {
        calculateDepth(sumVector[i], prev, counter, first);
    }

    return counter;
}

int sonarSweep(const string &filename, bool type) {
    ifstream file(filename);

    if (!file.is_open()) {
        return help();
    }

    if (type) {
        cout << basic(file) << endl;
    } else {
        cout << threeMeasurementSlidingWindow(file) << endl;
    }

    file.close();

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return help();

    return sonarSweep(argv[1], false);
}