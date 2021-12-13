#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <vector>
#include <cstring>

using namespace std;

struct Graph {
    map<string, list<string>> connections;
};

int help() {
    cout << "Usage: ./main <filename>" << endl;

    return -1;
}

bool isUpper(const string &string) {
    for (int i = 0; i < string.size(); i++) {
        if (!isupper(string[i])) return false;
    }
    return true;
}

void addConnection(Graph &g, const string &u, const string &v) {
    g.connections[u].push_back(v);
    g.connections[v].push_back(u);
}

void findPathsHelper(Graph &g, const string &start, const string &end, map<string, bool> &visited, vector<string> &path,
                     int &index, int &paths) {
    if (path.size() > index) path.resize(index);

    visited[start] = true;
    path.push_back(start);
    index++;

    if (start == end) {
        for (int i = 0; i < index; i++) {
            cout << path[i] << " ";
        }
        cout << endl;
        ++paths;
    } else {
        for (string node : g.connections[start]) {
            if (!visited[node] || isUpper(node)) findPathsHelper(g, node, end, visited, path, index, paths);
        }
    }

    index--;
    visited[start] = false;
}

void findPaths(Graph &g, const string &start, const string &end) {
    map<string, bool> visited;
    vector<string> path(g.connections.size());
    int index = 0, paths = 0;

    findPathsHelper(g, start, end, visited, path, index, paths);

    cout << paths << endl;
}

int passagePathing(const string &filename) {
    ifstream file(filename);
    string start, end;
    Graph graph;

    if (!file.is_open()) {
        return help();
    }

    while (getline(file, start, '-')) {
        getline(file, end);
        addConnection(graph, start, end);
    }

    findPaths(graph, "start", "end");

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return help();

    return passagePathing(argv[1]);
}