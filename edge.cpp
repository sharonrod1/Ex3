#include "edge.hpp"

using namespace ariel;

edge::edge(int road) : road(road) {}

void edge::setroad(int road) {
    this->road = road;
}

int edge::getroad() const {
    return road;
}

void edge::addvertex(int vertex) {
    vertices.push_back(vertex);
}

vector<int> edge::getvertices() const {
    return vertices;
}
void edge::setplayer(const player& p) {
    this->d = p;
}
