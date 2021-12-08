#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int help() {
    cout << "Usage: ./main <filename>" << endl;

    return -1;
}

int segments(const string &filename) {
    fstream file(filename);
    string line, symbol;
    stringstream ss;
    int counter = 0;
    bool delimiter;

    if (!file.is_open()) {
        return help();
    }

    while (getline(file, line)) {
        ss = stringstream(line);

        delimiter = false;
        while (ss >> symbol) {
            if (delimiter && (symbol.size() == 2 || symbol.size() == 4 || symbol.size() == 3 || symbol.size() == 7))
                ++counter;

            if (symbol == "|") delimiter = true;
        }
    }

    cout<<counter<<endl;

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return help();

    return segments(argv[1]);
}