#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Line {
    int x1, y1, x2, y2;
};

bool replace(string &str, const string &from, const string &to) {
    size_t start_pos = str.find(from);
    if (start_pos == string::npos) return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

int help() {
    cout << "Usage: ./main <filename>" << endl;

    return -1;
}

void processNumber(int num, int &counter, Line &l, int &max) {
    if (num > max) max = num;

    if (counter == 0) l.x1 = num;
    if (counter == 1) l.y1 = num;
    if (counter == 2) l.x2 = num;
    if (counter == 3) l.y2 = num;
}

void drawLine(Line line, vector<vector<int>> &board) {
    if (line.x1 != line.x2 && line.y1 != line.y2) return;
    int start = line.x1 == line.x2 ? line.y1 : line.x1;
    int end = line.x1 == line.x2 ? line.y2 : line.x2;
    string endString = line.x1 == line.x2 ? "y2" : "x2";

    for (int i = start; start > end ? i >= end : i <= end; start > end ? i-- : i++) {
        ++board[endString == "y2" ? i : line.y2][start == line.y1 ? line.x1 : i];
    }
}

int hydrothermalVents(const string &filename) {
    ifstream file(filename);
    int num, counter = 0, maxX = 0, maxY = 0, sum = 0;
    string line;
    stringstream ss;
    vector<Line> lines;

    while (getline(file, line)) {
        Line l{};
        replace(line, " -> ", ",");
        ss = stringstream(line);

        while (ss >> num) {
            processNumber(num, counter, l, counter % 2 == 0 ? maxX : maxY);

            counter = (++counter == 4 ? 0 : counter);

            if (counter == 0) {
                lines.push_back(l);
            }

            if (ss.peek() == ',')
                ss.ignore();
        }
    }

    vector<vector<int>> board(maxY + 1, std::vector<int>(maxX + 1));

    for (int i = 0; i < lines.size(); i++) {
        drawLine(lines[i], board);
    }

    for (int i = 0; i <= maxY; i++) {
        for (int j = 0; j <= maxX; j++) {
            if (board[i][j] > 1) ++sum;
        }
    }

    cout << sum << endl;

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return help();

    return hydrothermalVents(argv[1]);
}