#include "Graph.hpp"

Graph::Graph() : n(0), timer(0) {}

bool Graph::areConnected(const Shelter& a, const Shelter& b) const {
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    long long distSq = dx * dx + dy * dy;
    long long sumR = a.r + b.r;
    return distSq <= (long long)sumR * sumR;
}

bool Graph::isInside(const Shelter& s, int px, int py) const {
    long long dx = s.x - px;
    long long dy = s.y - py;
    long long distSq = dx * dx + dy * dy;
    return distSq <= (long long)s.r * s.r;
}

void Graph::readInput() {
    std::cin >> Ax >> Ay >> Bx >> By >> n;
    shelters.reserve(n);
    adj.resize(n);

    for (int i = 0; i < n; ++i) {
        int r, x, y;
        std::cin >> r >> x >> y;
        shelters.emplace_back(r, x, y);
    }

    // Conectar abrigos
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (areConnected(shelters[i], shelters[j])) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    // Determinar os abrigos de partida e chegada
    for (int i = 0; i < n; ++i) {
        if (isInside(shelters[i], Ax, Ay)) startNodes.push_back(i);
        if (isInside(shelters[i], Bx, By)) endNodes.push_back(i);
    }

    // Preparar estruturas para DFS também
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    isArticulation.assign(n, false);
}

int Graph::minimumPath() {
    const int INF = 1e9;
    std::vector<int> dist(n, INF);
    std::queue<int> q;

    for (int node : startNodes) {
        dist[node] = 0;
        q.push(node);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    int answer = INF;
    for (int node : endNodes) {
        if (dist[node] < answer) {
            answer = dist[node];
        }
    }

    return (answer == INF ? -1 : answer);
}

int Graph::maxDistance() {
    int maxDist = 0;
    for (int start = 0; start < n; ++start) {
        std::vector<bool> visitedLocal(n, false);
        std::queue<std::pair<int, int>> q;
        q.push({start, 0});
        visitedLocal[start] = true;
        
        while (!q.empty()) {
            int u = q.front().first;
            int dist = q.front().second;
            q.pop();
            
            if (dist > maxDist) {
                maxDist = dist;
            }
            
            for (int v : adj[u]) {
                if (!visitedLocal[v]) {
                    visitedLocal[v] = true;
                    q.push({v, dist + 1});
                }
            }
        }
    }
    
    return maxDist;
}

void Graph::dfs(int u, int p) {
    visited[u] = true;
    tin[u] = low[u] = timer++;
    int children = 0;
    
    for (int v : adj[u]) {
        if (v == p) continue;
        if (visited[v]) {
            if (low[u] > tin[v]) {
                low[u] = tin[v];
            }
        } else {
            dfs(v, u);
            if (low[u] > low[v]) {
                low[u] = low[v];
            }
            if (low[v] >= tin[u] && p != -1) {
                isArticulation[u] = true;
            }
            children++;
        }
    }
    
    if (p == -1 && children > 1) {
        isArticulation[u] = true;
    }
}

std::vector<int> Graph::findArticulationPoints() {
    for (int i = 0; i < n; ++i) {
        visited[i] = false;
        tin[i] = -1;
        low[i] = -1;
        isArticulation[i] = false;
    }
    timer = 0;

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i, -1);
        }
    }

    std::vector<int> criticals;
    for (int i = 0; i < n; ++i) {
        if (isArticulation[i]) {
            criticals.push_back(i + 1);
        }
    }

    return criticals;
}