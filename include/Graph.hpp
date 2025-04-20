#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <queue>
#include <vector>

struct Shelter {
    int x, y, r;

    Shelter(int r, int x, int y) : x(x), y(y), r(r) {}
};

class Graph {
    private:
    int Ax, Ay, Bx, By, n;
    int timer;
    std::vector<Shelter> shelters;
    std::vector<std::vector<int>> adj;
    std::vector<int> startNodes, endNodes;

    // Para DFS dos pontos críticos
    std::vector<bool> visited;
    std::vector<int> tin, low;
    std::vector<bool> isArticulation;

    bool areConnected(const Shelter& a, const Shelter& b) const;
    bool isInside(const Shelter& s, int px, int py) const;
    void dfs(int u, int p);

public:
    Graph();
    void readInput();
    int minimumPath(); // Parte 1
    int maxDistance(); // Parte 2
    std::vector<int> findArticulationPoints(); // Parte 3
};

#endif