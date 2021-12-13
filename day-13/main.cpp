#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <tuple>

using namespace std;

struct Point {
    int x, y;
};

int help() {
    cout << "Usage: ./main <filename>" << endl;

    return -1;
}

void rotate(Point &p, int cx, int cy) {
    p.x = ((p.x - cx) * -1) + cx;
    p.y = ((p.y - cy) * -1) + cy;
}

tuple<int, int> getMax(vector<Point> points) {
    int maxX = 0, maxY = 0;
    for (int i = 0; i < points.size(); i++) {
        if (points[i].x > maxX) maxX = points[i].x;
        if (points[i].y > maxY) maxY = points[i].y;
    }

    return make_tuple(maxX + 1, maxY + 1);
}

int transparentOrigami(const string &filename, bool type) {
    ifstream file(filename);
    Point point{};
    int num;
    string line;
    stringstream ss;
    vector<Point> points;
    vector<string> instructions;

    if (!file.is_open()) {
        return help();
    }

    while (getline(file, line)) {
        if (line.find("fold") != string::npos) instructions.push_back(line);
        else {
            if (line.empty()) continue;
            ss = stringstream(line);
            getline(ss, line, ',');
            point.x = stoi(line);
            getline(ss, line);
            point.y = stoi(line);
            points.push_back(point);
        }
    }

    tuple<int, int> max = getMax(points);
    vector<vector<string>> board(get<1>(max), vector<string>(get<0>(max), "."));

    for (Point p : points) {
        board[p.y][p.x] = "#";
    }

    for (int i = 0; i < instructions.size(); i++) {
        num = stoi(instructions[i].substr(instructions[i].find('=') + 1, instructions[i].size()));
        if (instructions[i].find('y') != string::npos) {
            for (int i = 0; i < points.size(); i++) {
                if (points[i].y > num) {
                    board[points[i].y][points[i].x] = ".";
                    rotate(points[i], points[i].x, num);
                    board[points[i].y % num][points[i].x] = "#";
                }
            }
        } else if (instructions[i].find('x') != string::npos) {
            for (int i = 0; i < points.size(); i++) {
                if (points[i].x > num) {
                    board[points[i].y][points[i].x] = ".";
                    rotate(points[i], num, points[i].y);
                    board[points[i].y][points[i].x % num] = "#";
                }
            }
        }
        if (!type) break;
    }

    num = 0;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (type) cout << board[i][j] << " ";
            if (!type && board[i][j] == "#") ++num;
        }
        if (type) cout << endl;
    }

    if (!type) cout << num << endl;

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return help();

    return transparentOrigami(argv[1], true);
}