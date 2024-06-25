#include "vertex.hpp"
using namespace std;
using namespace ariel;

vertex::vertex(int building) {
    this->building=building;
}

void vertex::setbuilding(int building) {
    this->building = building;
}

int vertex::getbuilding() const {
    return building;
}

void vertex::setplayer(const player& p) {
    this->d = p;
}

// player vertex::getplayer() const {
//     return d;
// }


