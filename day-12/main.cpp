#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <vector>

using namespace std;

struct Graph {
    map<string, list<string>> connections;
};

int help() {
    cout << "Usage: ./main <filename>" << endl;

    return -1;
}

bool isUpper(const string &string) {
    for (char i : string) if (!isupper(i)) return false;
    return true;
}

bool isVisited(map<string, int> &visited) {
    int counter = 0;
    for (const auto &kv : visited) if (kv.second > 1 && !isUpper(kv.first)) counter++;
    return counter <= 1;
}

void addConnection(Graph &g, const string &u, const string &v) {
    g.connections[u].push_back(v);
    g.connections[v].push_back(u);
}

void findPathsHelper(Graph &g, const string &start, const string &end, map<string, int> &visited, vector<string> &path,
                     int &index, int &paths, bool type) {
    if (path.size() > index) path.resize(index);

    ++visited[start];
    path.push_back(start);
    index++;

    if (start == end) ++paths;
    else {
        for (const string &node : g.connections[start]) {
            if (((visited[node] < 2 && isVisited(visited)) || isUpper(node)) && node != "start")
                findPathsHelper(g, node, end, visited, path, index, paths, type);
        }
    }

    index--;
    --visited[start];
}

void findPathsHelper(Graph &g, const string &start, const string &end, map<string, bool> &visited, vector<string> &path,
                     int &index, int &paths, bool type) {
    if (path.size() > index) path.resize(index);

    visited[start] = true;
    path.push_back(start);
    index++;

    if (start == end) ++paths;
    else {
        for (const string &node : g.connections[start]) {
            if (!visited[node] || isUpper(node))
                findPathsHelper(g, node, end, visited, path, index, paths, type);
        }
    }

    index--;
    visited[start] = false;
}

void findPaths(Graph &g, const string &start, const string &end, bool type) {
    vector<string> path(g.connections.size());
    int index = 0, paths = 0;

    if (type) {
        map<string, int> visited;
        findPathsHelper(g, start, end, visited, path, index, paths, type);
    } else {
        map<string, bool> visited;
        findPathsHelper(g, start, end, visited, path, index, paths, type);
    }

    cout << paths << endl;
}

int passagePathing(const string &filename, bool type) {
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

    findPaths(graph, "start", "end", type);

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return help();

    return passagePathing(argv[1], true);
}