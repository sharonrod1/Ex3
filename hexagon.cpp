#include "hexagon.hpp"
#include "edge.hpp"
#include "vertex.hpp"
#include <iostream>
#include <string>
using namespace ariel;

hexagon::hexagon(const std::string& resource, int cube) : resource(resource), cube(cube), edges(6), vertices(6) {
    // Initialize all edges to null shared_ptr
    for (auto& edge : edges) {
        edge = nullptr;
    }
    for (auto& verte : vertices) {
        verte = nullptr;
    }
}

void hexagon::setresource( std::string resource) {
    this->resource = resource;
}
void hexagon::setcube(int cube) {
    this->cube = cube;
}

string hexagon::getresource() const {
    return resource;
}

int hexagon::getcube() const {
    return cube;
}

void hexagon::setedge(int index, std::shared_ptr<edge> e) {
    edges[index] = e;
}

std::shared_ptr<edge> hexagon::getedge(int index) const {
    return edges[index];
}

void hexagon::setvertex(int index, std::shared_ptr<vertex> v) {
    vertices[index] = v;
}
std::shared_ptr<vertex> hexagon::getvertecs(int index) const {
    return vertices[index];
}
void hexagon::printroads() {
    for (size_t i = 0; i < edges.size(); ++i) {
        if (edges[i]) {
            cout << "Road " << i << ": " << edges[i]->getroad() << endl;
        } else {
            cout << "Road " << i << ": No road" << endl;
        }
    }
}
void hexagon::printvertices() {
    for (size_t i = 0; i < vertices.size(); ++i) {
        if (vertices[i]) {
            cout << "Vertex " << i << ": " << vertices[i]->getbuilding() << endl;
        } else {
            cout << "Vertex " << i << ": No building" << endl;
        }
    }
}
void hexagon::addvertex(int vertex, int building,player d){
    auto v =vertices[vertex];
    v->setbuilding(building);
    v->setplayer(d);
}
void hexagon::addedge(int edge, int road,player d){
    auto e =edges[edge];
    e->setroad(road);
    e->setplayer(d);
}