#include <iostream>
#include "Graph.h"
#include <fstream>
#include <random>
#include <exception>

OrderedGraphCost readFile(char file[20]) {
    std::ifstream fin(file);
    int nrV, nrE;
    fin >> nrV >> nrE;
    OrderedGraphCost G(nrV);
    for (int i = 0; i < nrE; ++i) {
        int v1, v2, cost;
        fin >> v1 >> v2 >> cost;
        G.addEdge(v1, v2, cost);
    }
    return G;
}

OrderedGraphCost generateGraph(int nrV, int nrE) {
    OrderedGraphCost G(nrV);
    int v1, v2, cost;
    for (int i = 0; i < nrE; ++i) {
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(0, nrV);
        std::uniform_int_distribution<int> distribution1(-100, 100);
        v1 = distribution(generator);
        v2 = distribution(generator);
        cost = distribution1(generator);
        if (G.isEdge(v1, v2)) {
            continue;
        }
        G.addEdge(v1, v2, cost);
    }
    return G;
}
OrderedGraphCost readWish() {
    std::cout << "Graph program: 1 - generate, 2 - read from file\n";
    int cmd;
    std::cin >> cmd;
    if (cmd != 1 and cmd != 2) {
        std::cout << "Invalid";
        throw std::exception();
    }
    if (cmd == 2) {
        std::cout << "Enter text name: ";
        char file[20];
        std::cin >> file;
        OrderedGraphCost g = readFile(file);
        return g;
    } else {
        std::cout << "Please enter number of vertices: ";
        int nrV, nrE;
        std::cin >> nrV;
        std::cout << "Please enter number of edges: ";
        std::cin >> nrE;
        OrderedGraphCost g = generateGraph(nrV, nrE);
        return g;
    }
}
void printMenu(OrderedGraphCost G) {
    std::cout << "Graph Operations\n1. Get the number of vertices\n2. The set of vertices\n3. Check if there is an edge between 2 vertices\n4. In degree of a vertex\n5. Out degree of a vertex\n6. The outbound edges of a vertex\n7. The inbound edges of a vertex\n8. Get the cost of an edge\n9. Modify the cost of an edge\n10. Add edge\n11. Remove edge\n12. Add vertex\n13. Remove vertex\n14. Copy graph and save it to file\n15. Save graph\n0. Exit\n";
    int cmd;
    std::cout << "Command: ";
    std::cin >> cmd;
    switch (cmd) {
        case 1:
            std::cout << G.nrVertices() << '\n';
            break;
        case 2: {
            auto p = G.setOfVertices();
            for (auto i = p.first; i != p.second; ++i) {
                std::cout << i->first << ' ';
            }
            std::cout << '\n';
            break;
        }
        case 3: {
            int v1, v2;
            std::cout << "Vertices: ";
            std::cin >> v1 >> v2;
            std::cout << G.isEdge(v1, v2) << '\n';
            break;
        }
        case 4: {
            int v1;
            std::cout << "Vertex: ";
            std::cin >> v1;
            std::cout << G.inDegree(v1) << '\n';
            break;
        }
        case 5: {
            int v1;
            std::cout << "Vertex: ";
            std::cin >> v1;
            std::cout << G.outDegree(v1) << '\n';
            break;
        }
        case 6: {
            int v1;
            std::cout << "Vertex: ";
            std::cin >> v1;
            auto p = G.outboundEdge(v1);
            for (auto i = p.first; i != p.second; ++i) {
                std::cout << *i << '\n';
            }
            break;
        }
        case 7: {
            int v1;
            std::cout << "Vertex: ";
            std::cin >> v1;
            auto p = G.inboundEdge(v1);
            for (auto i = p.first; i != p.second; ++i) {
                std::cout << *i << '\n';
            }
            break;
        }
        case 8: {
            int v1, v2;
            std::cout << "Edge: ";
            std::cin >> v1 >> v2;
            std::cout << G.getCost(v1, v2) << '\n';
            break;
        }
        case 9: {
            int v1, v2, cost;
            std::cout << "Edge: ";
            std::cin >> v1 >> v2;
            std::cout << "Cost: ";
            std::cin >> cost;
            G.changeCost(v1, v2, cost);
            break;
        }
        case 10: {
            int v1, v2, cost;
            std::cout << "Edge: ";
            std::cin >> v1 >> v2;
            std::cout << "Cost: ";
            std::cin >> cost;
            G.addEdge(v1, v2, cost);
            break;
        }
        case 11: {
            int v1, v2;
            std::cout << "Edge: ";
            std::cin >> v1 >> v2;
            G.removeEdge(v1, v2);
            break;
        }
        case 12: {
            int v1;
            std::cout << "Vertex: ";
            std::cin >> v1;
            G.addVertex(v1);
            break;
        }
        case 13: {
            int v1;
            std::cout << "Vertex: ";
            std::cin >> v1;
            G.removeVertex(v1);
            break;
        }
        case 0:
            throw 0;
            break;
        default:
            std::cout << "Invalid command\n";
            break;
    }
}
int main() {
    OrderedGraphCost G = OrderedGraphCost(0);
    try {
        G = readWish();
    }catch (std::exception& e) {
        std::cout << "Invalid data\n";
    }
    while (true) {
        try {
            printMenu(G);
        }catch (int e) {
            return 0;
        }
    }

    return 0;
}
