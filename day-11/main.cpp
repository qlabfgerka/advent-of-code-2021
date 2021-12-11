#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int help() {
    cout << "Usage: ./main <filename>" << endl;

    return -1;
}

int flash(vector<vector<int>> &octopuses, vector<vector<bool>> &flashed, int i, int j) {
    if (i < 0 || j < 0 || i >= 10 || j >= 10) return 0;

    int flashes = 0;

    if (!flashed[i][j])
        ++octopuses[i][j];

    if (octopuses[i][j] > 9) {
        octopuses[i][j] = 0;
        flashed[i][j] = true;
        ++flashes;
        flashes += flash(octopuses, flashed, i - 1, j - 1);
        flashes += flash(octopuses, flashed, i - 1, j);
        flashes += flash(octopuses, flashed, i - 1, j + 1);

        flashes += flash(octopuses, flashed, i, j - 1);
        flashes += flash(octopuses, flashed, i, j + 1);

        flashes += flash(octopuses, flashed, i + 1, j - 1);
        flashes += flash(octopuses, flashed, i + 1, j);
        flashes += flash(octopuses, flashed, i + 1, j + 1);
    }

    return flashes;
}

void setFlashed(vector<vector<bool>> &flashed) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) flashed[i][j] = false;
    }
}

int dumboOctopus(const string &filename) {
    fstream file(filename);
    string line;
    int flashes = 0;
    vector<vector<int>> octopuses(10, vector<int>(10, 0));
    vector<vector<bool>> flashed(10, vector<bool>(10, false));

    if (!file.is_open()) {
        return help();
    }

    for (int i = 0; i < 10; i++) {
        file >> line;
        for (int j = 0; j < 10; j++) {
            octopuses[i][j] = line[j] - 48;
        }
    }

    for (int iterations = 0; iterations < 100; iterations++) {
        setFlashed(flashed);
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                flashes += flash(octopuses, flashed, i, j);
            }
        }
    }
    
    cout << flashes << endl;

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return help();

    return dumboOctopus(argv[1]);
}