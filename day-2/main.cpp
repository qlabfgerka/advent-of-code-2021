#include <iostream>
#include <fstream>

using namespace std;

int help() {
    cout << "Usage: ./main <filename>" << endl;

    return -1;
}

int pilot(ifstream &file) {
    string command;
    int commandArgs, horizontal = 0, depth = 0;
    while (file >> command >> commandArgs) {
        if (command == "forward") {
            horizontal += commandArgs;
        } else if (command == "up") {
            depth -= commandArgs;
        } else if (command == "down") {
            depth += commandArgs;
        }
    }
    return horizontal * depth;
}

int pilotAdvanced(ifstream &file) {
    string command;
    int commandArgs, horizontal = 0, depth = 0, aim = 0;
    while (file >> command >> commandArgs) {
        if (command == "forward") {
            horizontal += commandArgs;
            depth += aim * commandArgs;
        } else if (command == "up") {
            aim -= commandArgs;
        } else if (command == "down") {
            aim += commandArgs;
        }
    }
    return horizontal * depth;
}

int pilotHelper(const string &filename, bool type) {
    ifstream file(filename);

    if (!file.is_open()) {
        return help();
    }

    if (type) {
        cout << pilot(file) << endl;
    } else {
        cout << pilotAdvanced(file) << endl;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return help();

    return pilotHelper(argv[1], false);
}