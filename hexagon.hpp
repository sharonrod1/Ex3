#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include "vertex.hpp"
#include "edge.hpp"
#include <vector>
#include <memory>
#include <string>

namespace ariel {
    class hexagon {
    private:
        std::string resource;
        int cube;
        std::vector<std::shared_ptr<edge>> edges; // Use shared pointers for edges
        std::vector<std::shared_ptr<vertex>> vertices;
    public:
        hexagon(const std::string& resource = "", int cube = 0); 
        void setresource(string resource);
        void setcube(int cube);
        std::string getresource() const;
        int getcube() const;
        void setedge(int index, std::shared_ptr<edge> e);
        std::shared_ptr<edge> getedge(int index) const;
        std::shared_ptr<vertex> getvertecs(int index) const;
        void setvertex(int index, std::shared_ptr<vertex> v);
        hexagon& gethexagon(size_t row, size_t col); 
        void printroads();
        void printvertices();
        void addvertex(int vertex, int building,player d);
        void addedge(int edge, int road,player d);

        // giving the co pilot to continue like the edges


    };
}

#endif
