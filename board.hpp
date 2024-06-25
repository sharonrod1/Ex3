#ifndef BOARD_HPP
#define BOARD_HPP
#include "hexagon.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <utility>
using namespace std;
namespace ariel{
    class board
    {
    private:
        vector<vector<hexagon>> map;
        void initializeMap();
    public:
        board();
        void randomizeResourses();
        void randomsizeCube();
        void printmap()  ;
        int getsize();
        int getsizeC(size_t row);
        hexagon& gethexagon(size_t row, size_t col);
        hexagon& returnhexagonS();
        hexagon& returnhexagonC();

    };
    
    // board::board(/* args */)
    // {
    // }
    
    // // board::~board()
    // // {
    // // }

    
 }
#endif 