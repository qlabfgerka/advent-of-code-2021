#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int help() {
    cout << "Usage: ./main <filename>" << endl;

    return -1;
}

int polymerization(const string &filename) {
    ifstream file(filename);
    string line;
    map<string, int> frequencies;
    map<string, int> tempFrequencies;
    map<string, int> symbolFrequencies;
    map<string, string> instructions;
    int max = -INT_MAX, min = INT_MAX;

    if (!file.is_open()) {
        return help();
    }

    getline(file, line);

    for (int i = 0; i < line.size() - 1; i++) {
        ++frequencies[string(1, line[i]) + line[i + 1]];
        ++symbolFrequencies[string(1, line[i])];
    }
    ++symbolFrequencies[string(1, line[line.size() - 1])];

    getline(file, line);

    while (getline(file, line)) {
        instructions[string(1, line[0]) + line[1]] = line[6];
    }

    for (int i = 0; i < 10; i++) {
        for (auto &kv: frequencies) {
            while (frequencies[kv.first] > 0) {
                --frequencies[kv.first];
                ++tempFrequencies[string(1, kv.first[0]) + instructions[kv.first]];
                ++tempFrequencies[instructions[kv.first] + kv.first[1]];
                ++symbolFrequencies[instructions[kv.first]];
            }
        }

        frequencies = tempFrequencies;
        tempFrequencies = map<string, int>();
    }

    for (auto &kv: symbolFrequencies) {
        if (kv.second > max) max = kv.second;
        if (kv.second < min) min = kv.second;
    }

    cout << max - min << endl;

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return help();

    return polymerization(argv[1]);
}