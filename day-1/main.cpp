#include <iostream>
#include <fstream>

using namespace std;

int help() {
    cout << "Usage: ./main <filename>" << endl;

    return -1;
}

int sonarSweep(const string &filename) {
    ifstream file(filename);
    bool first = true;
    int num, counter = 0, prev = 0;

    if (!file.is_open()) {
        return help();
    }

    while (file >> num) {
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

    cout << endl << counter << endl;

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return help();

    return sonarSweep(argv[1]);
}