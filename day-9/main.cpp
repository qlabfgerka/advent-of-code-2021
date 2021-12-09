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

void mark(vector<vector<bool>> &checked, int i, int j, int &size) {
    checked[i][j] = true;
    ++size;
}

int basins(vector<vector<int>> &smoke, vector<vector<bool>> &checked, int i, int j) {
    int size = 0;
    ++size;
    checked[i][j] = true;

    if (getValue(smoke, i - 1, j) < 9 && !checked[i - 1][j]) size += basins(smoke, checked, i - 1, j);
    if (getValue(smoke, i, j - 1) < 9 && !checked[i][j - 1]) size += basins(smoke, checked, i, j - 1);
    if (getValue(smoke, i, j + 1) < 9 && !checked[i][j + 1]) size += basins(smoke, checked, i, j + 1);
    if (getValue(smoke, i + 1, j) < 9 && !checked[i + 1][j]) size += basins(smoke, checked, i + 1, j);

    if (getValue(smoke, i - 1, j) < 9 && !checked[i - 1][j]) mark(checked, i - 1, j, size);
    if (getValue(smoke, i, j - 1) < 9 && !checked[i][j - 1]) mark(checked, i, j - 1, size);
    if (getValue(smoke, i, j + 1) < 9 && !checked[i][j + 1]) mark(checked, i, j + 1, size);
    if (getValue(smoke, i + 1, j) < 9 && !checked[i + 1][j]) mark(checked, i + 1, j, size);

    return size;
}

void initializeChecked(vector<vector<bool>> &checked, int n, int m) {
    for (int i = 0; i < n; i++) {
        checked.emplace_back();
        for (int j = 0; j < m; j++) {
            checked[i].push_back(false);
        }
    }
}

int lavaTubes(const string &filename, bool type) {
    ifstream file(filename);
    int counter = 0;
    string line;
    vector<vector<int>> smoke;
    vector<vector<bool>> checked;
    vector<int> basinsVector;

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
            if (lowPoint(smoke, i, j)) {
                if (!type) counter += smoke[i][j] + 1;
                else {
                    initializeChecked(checked, smoke.size(), smoke[0].size());
                    checked[i][j] = true;
                    basinsVector.push_back(basins(smoke, checked, i, j));
                }
            }
        }
    }

    if (!type) cout << counter << endl;
    else {
        sort(basinsVector.begin(), basinsVector.end(), greater<int>());
        cout << basinsVector[0] * basinsVector[1] * basinsVector[2] << endl;
    }


    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return help();

    return lavaTubes(argv[1], true);
}