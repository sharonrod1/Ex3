#ifndef EDGE_HPP
#define EDGE_HPP
#include "player.hpp"
#include <vector>

using namespace std;

namespace ariel {
    class edge {
    private:
        int road;
        vector<int> vertices;
        player d;
    public:
        edge(int road = 0); 
        void setroad(int road);
        int getroad() const;
        void addvertex(int vertex);
        void setplayer(const player& p);
        player getplayer() const{ return d;};
        vector<int> getvertices() const;
    };
}

#endif
