#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int help() {
    cout << "Usage: ./main <filename>" << endl;

    return -1;
}

void generatePolymer(map<string, uint64_t> frequencies, map<string, uint64_t> tempFrequencies,
                     map<string, string> instructions, map<string, uint64_t> &symbolFrequencies, int steps) {
    for (int i = 0; i < steps; i++) {
        for (auto &kv: frequencies) {
            tempFrequencies[string(1, kv.first[0]) + instructions[kv.first]] += kv.second;
            tempFrequencies[instructions[kv.first] + kv.first[1]] += kv.second;
            symbolFrequencies[instructions[kv.first]] += kv.second;
        }

        frequencies = tempFrequencies;
        tempFrequencies = map<string, uint64_t>();
    }
}

int polymerization(const string &filename, bool type) {
    ifstream file(filename);
    string line;
    map<string, uint64_t> frequencies;
    map<string, uint64_t> tempFrequencies;
    map<string, uint64_t> symbolFrequencies;
    map<string, string> instructions;
    long max = -std::numeric_limits<uint64_t>::max(), min = std::numeric_limits<uint64_t>::max();

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

    if (!type) generatePolymer(frequencies, tempFrequencies, instructions, symbolFrequencies, 10);
    else generatePolymer(frequencies, tempFrequencies, instructions, symbolFrequencies, 40);

    for (auto &kv: symbolFrequencies) {
        if (kv.second > max) max = kv.second;
        if (kv.second < min) min = kv.second;
    }

    cout << max - min << endl;

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return help();

    return polymerization(argv[1], true);
}