//
// Created by Octavian Custura on 26/02/2020.
//

#include "Graph.h"
#include <exception>

OrderedGraphCost::OrderedGraphCost(int nrVertices) {
    for (int i = 0; i < nrVertices; ++i) {
        inMap[i] = std::vector<int>();
        outMap[i] = std::vector<int>();
    }
}

void OrderedGraphCost::addEdge(int v1, int v2, int cost) {
    if (!isVertex(v1) or !isVertex(v2) or isEdge(v1, v2)) {
        throw std::exception();
    }
    costMap[std::make_pair(v1, v2)] = cost;
    outMap[v1].push_back(v2);
    inMap[v2].push_back(v1);
}

bool OrderedGraphCost::isVertex(int v) {
    if (inMap.find(v) != inMap.end()) {
        return true;
    }
    return false;
}
bool OrderedGraphCost::isEdge(int v1, int v2) {
    return std::find(outMap[v1].begin(), outMap[v1].end(), v2) != outMap[v1].end();
}

std::pair<std::map<int, std::vector<int>>::iterator , std::map<int, std::vector<int>>::iterator> OrderedGraphCost::setOfVertices() {
    return std::make_pair(outMap.begin(), outMap.end());
}

int OrderedGraphCost::nrVertices() {
    return outMap.size();
}

int OrderedGraphCost::nrEdges() {
    return costMap.size();
}

int OrderedGraphCost::inDegree(int x) {
    return inMap[x].size();
}

int OrderedGraphCost::outDegree(int x) {
    return outMap[x].size();
}

int OrderedGraphCost::getCost(int x, int y) {
    if (!isEdge(x, y)) {
        throw std::exception();
    }
    return costMap[std::make_pair(x, y)];
}

void OrderedGraphCost::changeCost(int x, int y, int val) {
    if (!isEdge(x, y)) {
        throw std::exception();
    }
    costMap[std::make_pair(x, y)] = val;
}

std::pair <std::vector<int>::iterator, std::vector<int>::iterator> OrderedGraphCost::inboundEdge(int x) {
    return std::make_pair(inMap[x].begin(), inMap[x].end());
}

std::pair<std::vector<int>::iterator, std::vector<int>::iterator> OrderedGraphCost::outboundEdge(int x) {
    return std::make_pair(outMap[x].begin(), outMap[x].end());
}

void OrderedGraphCost::removeEdge(int x, int y) {
    if (!isEdge(x, y)) {
        throw std::exception();
    }
    for (auto &elem : costMap) {
        if (y == elem.first.second and x == elem.first.first) {
            costMap.erase(elem.first);
            break;
        }
    }
    inMap[y].erase(std::find(inMap[y].begin(), inMap[y].end(), x));
    outMap[x].erase(std::find(inMap[x].begin(), inMap[x].end(), y));
}

void OrderedGraphCost::addVertex(int val) {
    if (isVertex(val)) {
        throw std::exception();
    }
    inMap[val] = std::vector<int>();
    outMap[val] = std::vector<int>();
}

void OrderedGraphCost::removeVertex(int val) {
    inMap.erase(inMap.find(val));
    outMap.erase(outMap.find(val));
    int len = costMap.size();
    std::vector<std::pair<int, int>> array;
    for (auto& el : costMap) {
        array.push_back(el.first);
    }
    int i = 0;
    while (i < len) {
        if (array[i].second == val or array[i].first == val) {
            costMap.erase(costMap.find(array[i]));
            array.erase(std::find(array.begin(), array.end(), array[i]));
            len--;
            continue;
        }
        i++;
    }
    for (auto el : inMap) {
        auto c = std::find(el.second.begin(), el.second.end(), val);
        if (c != el.second.end()) {
            el.second.erase(c);
        }
    }
    for (auto el : outMap) {
        auto c = std::find(el.second.begin(), el.second.end(), val);
        if (c != el.second.end()) {
            el.second.erase(c);
        }
    }
}