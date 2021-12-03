#include <iostream>
#include <fstream>

using namespace std;

int help() {
    cout << "Usage: ./main <filename>" << endl;

    return -1;
}

int pilot(const string &filename) {
    ifstream file(filename);
    string command;
    int commandArgs, horizontal = 0, depth = 0;

    if (!file.is_open()) {
        return help();
    }

    while (file >> command >> commandArgs) {
        if (command == "forward") {
            horizontal += commandArgs;
        } else if (command == "up") {
            depth -= commandArgs;
        } else if (command == "down") {
            depth += commandArgs;
        }
    }

    cout << horizontal << " " << depth << " " << horizontal * depth << endl;

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return help();

    return pilot(argv[1]);
}