#include "board.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

using namespace std;
using namespace ariel;

board::board() {
    initializeMap();
}

void board::initializeMap() {
    // Initialize the map with the specified number of hexagons in each row
    map.push_back(vector<hexagon>(3, hexagon())); // First row with 3 hexagons
    map.push_back(vector<hexagon>(4, hexagon())); // Second row with 4 hexagons
    map.push_back(vector<hexagon>(5, hexagon())); // Third row with 5 hexagons
    map.push_back(vector<hexagon>(4, hexagon())); // Fourth row with 4 hexagons
    map.push_back(vector<hexagon>(3, hexagon())); // Fifth row with 3 hexagons
    for (size_t j = 0; j < map.size(); ++j){
    for(size_t i = 0; i < map[j].size(); ++i){
        for(size_t k=0;k<6;k++){
        map[j][i].setedge(k, std::make_shared<edge>());
        map[j][i].setvertex(k, std::make_shared<vertex>());
        }
        }
    }
    // Initialize edges and vertices to ensure shared edges and vertices
    for (size_t i = 0; i < map.size(); ++i) {
        for (size_t j = 0; j < map[i].size(); ++j) {
            
            // Top-left edge (shared with the hexagon above)
            if ((i > 0 && j > 0)||(i>2)) {
                if (i>2){
                    map[i][j].setedge(1, map[i-1][j].getedge(4));
                    map[i][j].setvertex(2, map[i-1][j].getvertecs(4));
                    map[i][j].setvertex(1, map[i-1][j].getvertecs(5));
                    
                }
                else{
                    map[i][j].setedge(1, map[i-1][j-1].getedge(4));
                    map[i][j].setvertex(2, map[i-1][j-1].getvertecs(4));
                    map[i][j].setvertex(1, map[i-1][j-1].getvertecs(5));
                    
                }
            }

            // Top-right edge (shared with the hexagon above-right)
            if ((i > 0 && j < map[i-1].size())||(i>2)) {
                if (i>2){
                    map[i][j].setedge(0, map[i-1][j+1].getedge(3));
                    map[i][j].setvertex(0, map[i-1][j+1].getvertecs(4));
                    map[i][j].setvertex(1, map[i-1][j+1].getvertecs(3));
                    
                }
                else{
                    map[i][j].setedge(0, map[i-1][j].getedge(3));
                    map[i][j].setvertex(0, map[i-1][j].getvertecs(4));
                    map[i][j].setvertex(1, map[i-1][j].getvertecs(3));
                    
                }
                
            } 

            // Left edge (shared with the hexagon to the left)
            if (j > 0) {
                map[i][j].setedge(2, map[i][j-1].getedge(5));
                map[i][j].setvertex(2, map[i][j-1].getvertecs(0));
                map[i][j].setvertex(3, map[i][j-1].getvertecs(5));
                
            } 

            // // Bottom-left edge (shared with the hexagon below)
            if ((i + 1 < map.size() && j>0)||(i<2)) {
                if (i<2){
                    map[i][j].setedge(3, map[i+1][j].getedge(0));
                    
                }
                else{
                    map[i][j].setedge(3, map[i+1][j-1].getedge(0));
                    
                }
            } else {
                map[i][j].setedge(3, std::make_shared<edge>());
                
            }

            // // Bottom-right edge (shared with the hexagon below-right)
            if ((i + 1 < map.size() && j  < map[i+1].size())||(i<2)) {
                if (i<2){
                    map[i][j].setedge(4, map[i+1][j+1].getedge(1));
                   
                }
                else{
                    map[i][j].setedge(4, map[i+1][j].getedge(1));
                    
                }
            } else {
                map[i][j].setedge(4, std::make_shared<edge>());
                
            }

            // // Right edge (shared with the hexagon to the right)
            if (j + 1 < map[i].size()) {
                map[i][j].setedge(5, map[i][j+1].getedge(2));
                
            } else {
                map[i][j].setedge(5, std::make_shared<edge>());
             
            }

        
        }
    }
    board::randomizeResourses();
    board::randomsizeCube();    
    
}

void board::printmap()  {
    for (size_t i = 0; i < map.size(); ++i) {
        for (size_t j = 0; j < map[i].size(); ++j) {
            if(i==0&&j==0){
            cout<<"                     ";
            cout << map[i][j].getresource() << "(" << map[i][j].getcube() << ")" ;
            cout<<"        ";
            j++;} 
        
            if(i==0){
            cout << map[i][j].getresource() << "(" << map[i][j].getcube() << ") ";
            cout<<"        ";
            j++;
            cout << map[i][j].getresource() << "(" << map[i][j].getcube() << ") "<<endl;
            cout<<endl;
            
            }
            if(i==1&&j==0){
            cout<<"            ";
            for (size_t k = 0; k < 4; ++k) {
                cout << map[i][k].getresource() << "(" << map[i][k].getcube() << ") ";
                cout<<"        ";
            }
            cout<<endl;
            j=map[i].size();
            cout<<endl;
            }
            if(i==2&&j==0){
                cout<<"    ";
            for (size_t k = 0; k < 5; ++k) {
                cout << map[i][k].getresource() << "(" << map[i][k].getcube() << ") ";
                cout<<"        ";
            }
            cout<<endl;
            cout<<endl;}
            if(i==3&&j==0){
            cout<<"            ";
            for (size_t k = 0; k < 4; ++k) {
                cout << map[i][k].getresource() << "(" << map[i][k].getcube() << ") ";
                cout<<"        ";
            }
            cout<<endl;
            j=map[i].size();
            cout<<endl;
            }
            if(i==4&&j==0){
            cout<<"                     ";
            cout << map[i][j].getresource() << "(" << map[i][j].getcube() << ")" ;
            cout<<"         ";
            j++;
            cout << map[i][j].getresource() << "(" << map[i][j].getcube() << ") ";
            cout<<"         ";
            j++;
            cout << map[i][j].getresource() << "(" << map[i][j].getcube() << ") "<<endl;
            cout<<endl;
            }
        }
    }
    
}

hexagon& board::gethexagon(size_t row, size_t col) {
    return map[row][col];
}


void board::randomizeResourses() {
    // Randomize the resources of each hexagon
        // Create a vector of resources
        std::vector<std::string> resources;
        for (int i = 0; i < 4; ++i) resources.push_back("wood");
        for (int i = 0; i < 3; ++i) resources.push_back("brick");
        for (int i = 0; i < 4; ++i) resources.push_back("wheat");
        for (int i = 0; i < 3; ++i) resources.push_back("ore");
        for (int i = 0; i < 4; ++i) resources.push_back("wool");
        resources.push_back("desert");

        // Shuffle the resources vector
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(resources.begin(), resources.end(), g);

        // Assign resources to each hexagon in the map
        size_t resource_index = 0;
        for (size_t row = 0; row < map.size(); ++row) {
            for (size_t col = 0; col < map[row].size(); ++col) {
                map[row][col].setresource(resources[resource_index]);
                resource_index++;
            }
        }
    }
void board:: randomsizeCube(){
    std::vector<int> cube_numbers;
    for (int i = 2; i <= 12; ++i) {
        cube_numbers.push_back(i);
    }

    // Randomly select additional numbers to make the vector size 18
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<int> dist(2, 12);

    while (cube_numbers.size() < 18) {
        int random_number = dist(g);
        cube_numbers.push_back(random_number);
    }
    // std::random_device rd;
    // std::mt19937 g(rd());
    std::shuffle(cube_numbers.begin(), cube_numbers.end(), g);
     size_t cube_index = 0;
     
        for (size_t row = 0; row < map.size(); ++row) {
            for (size_t col = 0; col < map[row].size(); ++col) {
                if(cube_numbers[cube_index]==0){
                    cube_index++;
                }
                if(map[row][col].getresource()=="desert"){
                map[row][col].setcube(0);
                }
                else{
                map[row][col].setcube(cube_numbers[cube_index]);
                cube_index++;}
            }
        }

}
int board::getsize(){
    return map.size();
}
int board::getsizeC(size_t x){
    return map[x].size();
}
