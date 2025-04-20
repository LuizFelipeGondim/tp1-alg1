#include <iostream>
#include "Graph.hpp"

int main() {
    Graph g;
    g.readInput();

    std::cout << "Parte 1: " << g.minimumPath() << std::endl;
    std::cout << "Parte 2: " << g.maxDistance() << std::endl;
    
    std::vector<int> articulationPoints = g.findArticulationPoints();
    std::cout << "Parte 3: " << articulationPoints.size();
    for (int idx : articulationPoints) {
        std::cout << " " << idx;
    }
    std::cout << std::endl;

    return 0;
}
