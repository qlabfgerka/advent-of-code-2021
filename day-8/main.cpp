#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int help() {
    cout << "Usage: ./main <filename>" << endl;

    return -1;
}

void basic(const string &line, int &counter) {
    string symbol;
    stringstream ss;
    bool delimiter;
    ss = stringstream(line);

    delimiter = false;
    while (ss >> symbol) {
        if (delimiter && (symbol.size() == 2 || symbol.size() == 4 || symbol.size() == 3 || symbol.size() == 7))
            ++counter;

        if (symbol == "|") delimiter = true;
    }
}

int dictionarySize(vector<string> dictionary) {
    int size = 0;
    for (int i = 0; i < dictionary.size(); i++) {
        if (!dictionary[i].empty()) ++size;
    }

    return size;
}

int differences(const string &symbol, string number) {
    if (number.empty()) return symbol.size();
    int differences = number.size();
    for (int i = 0; i < number.size(); i++) {
        if (symbol.find(number[i]) != string::npos) --differences;
    }

    return differences;
}

int findIndex(vector<string> dictionary, const string &key) {
    for (int i = 0; i < dictionary.size(); i++) {
        if (differences(dictionary[i], key) == 0 && dictionary[i].size() == key.size()) return i;
    }
    return -1;
}

void handleDictionary(vector<string> &wires, vector<string> &dictionary, int dictIndex, int wireIndex) {
    dictionary[dictIndex] = wires[wireIndex];
    wires.erase(wires.begin() + wireIndex);
}

int ssd(const string &line) {
    int index = 0, num = 0, div = 1000;
    string symbol;
    stringstream ss;
    bool delimiter;
    ss = stringstream(line);
    vector<string> wires, output, dictionary(10);

    delimiter = false;
    while (ss >> symbol) {
        if (delimiter) output.push_back(symbol);
        if (symbol == "|") delimiter = true;
        if (!delimiter) wires.push_back(symbol);
    }

    for (int i = 0; i < 10; i++) {
        dictionary.emplace_back("");
    }

    while (true) {
        if (wires[index].size() == 2 && dictionary[1].empty())
            handleDictionary(wires, dictionary, 1, index);
        else if (wires[index].size() == 4 && dictionary[4].empty())
            handleDictionary(wires, dictionary, 4, index);
        else if (wires[index].size() == 3 && dictionary[7].empty())
            handleDictionary(wires, dictionary, 7, index);
        else if (wires[index].size() == 7 && dictionary[8].empty())
            handleDictionary(wires, dictionary, 8, index);
        else if (wires[index].size() == 5 && dictionary[3].empty() &&
                 differences(wires[index], dictionary[7]) == 0)
            handleDictionary(wires, dictionary, 3, index);
        else if (wires[index].size() == 6 && dictionary[9].empty() &&
                 differences(wires[index], dictionary[4]) == 0)
            handleDictionary(wires, dictionary, 9, index);
        else if (wires.size() == 4 && dictionary[0].empty() && differences(wires[index], dictionary[1]) == 0)
            handleDictionary(wires, dictionary, 0, index);
        else if (wires.size() == 3 && wires[index].size() == 6 && dictionary[6].empty())
            handleDictionary(wires, dictionary, 6, index);
        else if (wires.size() == 2 && dictionary[5].empty() && differences(wires[index], dictionary[6]) == 1)
            handleDictionary(wires, dictionary, 5, index);
        else if (wires.size() == 1)
            handleDictionary(wires, dictionary, 2, index);

        if (dictionarySize(dictionary) == 10) break;

        index = (++index >= wires.size() ? index = 0 : index);
    }

    for (int i = 0; i < output.size(); i++) {
        num += findIndex(dictionary, output[i]) * div;
        div /= 10;
    }
    return num;
}

int segments(const string &filename, bool type) {
    fstream file(filename);
    string line;
    int counter = 0;

    if (!file.is_open()) {
        return help();
    }

    while (getline(file, line)) {
        if (!type) basic(line, counter);
        else counter += ssd(line);
    }

    cout << counter << endl;

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return help();

    return segments(argv[1], true);
}