#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Bingo {
    int board[5][5];
    bool checked[5][5];
};

int help() {
    cout << "Usage: ./main <filename>" << endl;

    return -1;
}

int uncheckedSum(Bingo bingo) {
    int sum = 0;
    for (int j = 0; j < 5; j++) {
        for (int k = 0; k < 5; k++) {
            if (!bingo.checked[j][k]) sum += bingo.board[j][k];
        }
    }

    return sum;
}

bool checkWin(Bingo bingo) {
    int vertical = 0, horizontal = 0;

    for (int j = 0; j < 5; j++) {
        vertical = 0;
        horizontal = 0;
        for (int k = 0; k < 5; k++) {
            if (bingo.checked[j][k]) {
                horizontal++;
            }
            if (bingo.checked[k][j]) {
                vertical++;
            }
        }

        if (horizontal == 5 || vertical == 5) return true;
    }

    return false;
}

int play(const string& line, vector<Bingo> &bingo) {
    stringstream ss(line);
    string number;
    while (getline(ss, number, ',')) {
        for (int i = 0; i < bingo.size(); i++) {
            for (int j = 0; j < 5; j++) {
                for (int k = 0; k < 5; k++) {
                    if (bingo[i].board[j][k] == stoi(number)) {
                        bingo[i].checked[j][k] = true;
                        if (checkWin(bingo[i])) {
                            return uncheckedSum(bingo[i]) * stoi(number);
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int bingo(const string &filename) {
    ifstream file(filename);
    int num, bingoIndex = 0, iIndex = 0, jIndex = 0;
    string line;
    vector<Bingo> bingo;

    if (!file.is_open()) {
        return help();
    }

    getline(file, line);

    bingo.push_back({});
    while (file >> num) {
        bingo[bingoIndex].board[iIndex][jIndex] = num;
        bingo[bingoIndex].checked[iIndex][jIndex] = false;

        iIndex++;
        if (iIndex == 5) {
            iIndex = 0;
            jIndex++;
            if (jIndex == 5) {
                jIndex = 0;
                bingo.push_back({});
                bingoIndex++;
            }
        }
    }
    bingo.pop_back();

    cout << play(line, bingo) << endl;

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return help();

    return bingo(argv[1]);
}