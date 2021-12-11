#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int help() {
    cout << "Usage: ./main <filename>" << endl;

    return -1;
}

int eraseSubstring(string &main, const string &substring) {
    size_t pos = main.find(substring);
    if (pos != string::npos) main.erase(pos, substring.length());

    return pos;
}

bool incomplete(const string &line) {
    return line.find('}') == string::npos && line.find(']') == string::npos && line.find('>') == string::npos &&
           line.find(')') == string::npos;
}

int illegalCharacter(const string &line) {
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == ')') return 3;
        else if (line[i] == ']') return 57;
        else if (line[i] == '}') return 1197;
        else if (line[i] == '>') return 25137;
    }
    return 0;
}

uint64_t autocompleteLine(const string &line) {
    uint64_t score = 0;
    for (int i = line.size() - 1; i >= 0; i--) {
        score *= 5;
        if (line[i] == '(') score += 1;
        else if (line[i] == '[') score += 2;
        else if (line[i] == '{') score += 3;
        else if (line[i] == '<') score += 4;
    }
    return score;
}

int syntaxScoring(const string &filename) {
    ifstream file(filename);
    string line;
    int illegal = 0;
    vector<uint64_t> autocompletes;

    if (!file.is_open()) {
        return help();
    }

    while (getline(file, line)) {
        while (eraseSubstring(line, "()") != -1
               || eraseSubstring(line, "<>") != -1
               || eraseSubstring(line, "{}") != -1
               || eraseSubstring(line, "[]") != -1) {}

        if (!incomplete(line)) illegal += illegalCharacter(line);
        else autocompletes.push_back(autocompleteLine(line));
    }
    sort(autocompletes.begin(), autocompletes.end());

    cout << "ILLEGAL CHARACTERS: " << illegal << endl;
    cout << "AUTOCOMPLETE: " << autocompletes[(int) autocompletes.size() / 2] << endl;

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return help();

    return syntaxScoring(argv[1]);
}