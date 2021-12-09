#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int help() {
    cout << "Usage: ./main <filename>" << endl;

    return -1;
}

int getValue(vector<vector<int>> smoke, int i, int j) {
    if (i < 0 || i >= smoke.size() || j < 0 || j >= smoke[i].size()) return 10;
    return smoke[i][j];
}

bool lowPoint(vector<vector<int>> smoke, int i, int j) {
    return (smoke[i][j] < getValue(smoke, i - 1, j) && smoke[i][j] < getValue(smoke, i, j - 1) &&
            smoke[i][j] < getValue(smoke, i, j + 1) && smoke[i][j] < getValue(smoke, i + 1, j) != 0);
}

int lavaTubes(const string &filename) {
    ifstream file(filename);
    int counter = 0;
    string line;
    vector<vector<int>> smoke;

    if (!file.is_open()) {
        return help();
    }

    while (getline(file, line)) {
        smoke.emplace_back();

        for (int i = 0; i < line.size(); i++) {
            smoke[counter].push_back(line[i] - 48);
        }

        ++counter;
    }

    counter = 0;
    for (int i = 0; i < smoke.size(); i++) {
        for (int j = 0; j < smoke[i].size(); j++) {
            if (lowPoint(smoke, i, j)) counter += smoke[i][j] + 1;

        }
    }

    cout << counter << endl;
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return help();

    return lavaTubes(argv[1]);
}