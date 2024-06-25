#include "catan.hpp"
#include "board.hpp"
#include "player.hpp"
#include <iostream>
#include <limits>
using namespace std;

namespace ariel {
    int catan::turn = 1; // Static variable to keep track of the current turn number.

    // Constructor for the catan class, initializing the game with a board and three players.
    catan::catan(board &c, player &p1, player &p2, player &p3) : b(c), p1(p1), p2(p2), p3(p3) {}

    // Prints the current state of the game, including player names and the current turn.
    void catan::printmap() {
        cout << "player 1: " << p1.getname() << endl;
        cout << "player 2: " << p2.getname() << endl;
        cout << "player 3: " << p3.getname() << endl;
        cout << "turn: " << turn << endl;
        this->b.printmap();
    }

    // Rolls two six-sided dice and returns their sum.
    int catan::rolldices() {
        srand(static_cast<unsigned int>(time(0))); // Seed the random number generator.
        int dice1 = rand() % 6 + 1; // Generate a random number between 1 and 6.
        int dice2 = rand() % 6 + 1;
        int sum = dice1 + dice2; // Sum of both dice rolls.
        return sum;
    }

    // Attempts to place a village at the specified coordinates and vertex. Returns true if successful.
    bool catan::placevillage(int x, int y, player &player, int vertex) {
        if (vertex > 5) {
            cout << "vertex number is invalid" << endl;
            return false;
        }
        // Check if coordinates are within the bounds of the board.
        if ((x < 0) || (y < 0) || (x > 4) || (y > 4) || (y >= b.getsizeC(size_t(x)))) {
            cout << "out of bounds" << endl;
            return false;
        }
        auto a = b.gethexagon(x, y).getvertecs(vertex);

        // Check if a building already exists at this vertex.
        if (a->getbuilding() != 0) {
            cout << "there is already a building here" << endl;
            return false;
        }
        // Add the village to the specified vertex.
        b.gethexagon(x, y).addvertex(vertex, 1, player);
        return true;
    }

    // Attempts to place a city at the specified coordinates and vertex. Returns true if successful.
    bool catan::placecity(int x, int y, player &player, int vertex) {
        if (vertex > 5) {
            cout << "vertex number is invalid" << endl;
            return false;
        }
        // Check if coordinates are within the bounds of the board.
        if ((x < 0) || (y < 0) || (x > 4) || (y > 4) || (y >= b.getsizeC(size_t(x)))) {
            cout << "out of bounds" << endl;
            return false;
        }
        auto a = b.gethexagon(x, y).getvertecs(vertex);

        // Check if a building already exists at this vertex.
        if (a->getbuilding() != 0) {
            cout << "there is already a building here" << endl;
            return false;
        }
        // Upgrade the building to a city at the specified vertex.
        b.gethexagon(x, y).addvertex(vertex, 2, player);
        return true;
    }

    // Attempts to place a road at the specified coordinates and edge. Returns true if successful.
    bool catan::placeroad(int x, int y, player &player, int edge) {
        if (edge > 5) {
            cout << "vertex number is invalid" << endl;
            return false;
        }

        // Check if coordinates are within the bounds of the board.
        if ((x < 0) || (y < 0) || (x > 4) || (y > 4) || (y >= b.getsizeC(size_t(x)))) {
            cout << "out of bounds" << endl;
            return false;
        }
        auto a = b.gethexagon(x, y).getedge(edge);
        if (a->getroad() != 0) {
            cout << "there is already a road here" << endl;
            return false;
        }
        auto a1 = b.gethexagon(x, y).getedge((edge + 1) % 5);
        if (edge == 0) {
            auto a2 = b.gethexagon(x, y).getedge(5);
            if (a2->getroad() != 0) {
                if (player.getid() == a2->getplayer().getid()) {
                    b.gethexagon(x, y).addedge(edge, 1, player);
                    return true;
                }
            }
        } else {
            auto a2 = b.gethexagon(x, y).getedge((edge - 1) % 5);
            if (a2->getroad() != 0) {
                if (player.getid() == a2->getplayer().getid()) {
                    b.gethexagon(x, y).addedge(edge, 1, player);
                    return true;
                }
            }
        }

        if (a1->getroad() != 0) {
            if (player.getid() == a1->getplayer().getid()) {
                b.gethexagon(x, y).addedge(edge, 1, player);
                return true;
            }
        }

        auto t = b.gethexagon(x, y).getvertecs(edge);
        auto t2 = b.gethexagon(x, y).getvertecs((edge + 1) % 5);
        if ((t->getbuilding() == 0) && (t2->getbuilding() == 0)) {
            cout << "you need to build a village first" << endl;
            return false;
        }
        if (t->getbuilding()) {
            if (player.getid() != t->getplayer()->getid()) {
                cout << "you need to build a village first" << endl;
                return false;
            }
        }
        if (t2->getbuilding()) {
            if (player.getid() != t2->getplayer()->getid()) {
                cout << "you need to build a village first" << endl;
                return false;
            }
        }
        // Place the road if there is a valid village or road connection.
        b.gethexagon(x, y).addedge(edge, 1, player);
        return true;
    }

    // Returns a copy of the current board state.
    board catan::getboard() {
        return b;
    }

    // Determines the starting positions for each player's first and second settlements and roads.
    void catan::choosestarting() {
        int x1, y1, x2, z1, y2, z2, x3, y3, z3, x4, y4, z4;
        p1.addpoints(2);
        p2.addpoints(2);
        p3.addpoints(2);
        cout << "The game is starting!" << endl;
        for (int i = 0; i < 3; i++) {
            player *s;
            if (i == 0) {
                s = &p1;
            }
            if (i == 1) {
                s = &p2;
            }
            if (i == 2) {
                s = &p3;
            }
            cout << "its your turn " << s->getname() << endl;
            while (true) {
                cout << "choose a resource to place your first settlement on: " << endl;
                x1 = getValidatedInteger("");
                y1 = getValidatedInteger("");
                z1 = getValidatedInteger("");
                if (placevillage(x1, y1, *s, z1)) {
                    break;
                }
            }

            while (true) {
                cout << "choose a resource to place your second settlement on: " << endl;
                x2=getValidatedInteger("");
                y2=getValidatedInteger("");
                z2=getValidatedInteger("");
                if (placevillage(x2, y2, *s, z2)) {
                    break;
                }
            }
            while (true) {
                cout << "choose a place to place your first road on: " << endl;
                x3=getValidatedInteger("");
                y3=getValidatedInteger("");
                z3=getValidatedInteger("");
                if (placeroad(x3, y3, *s, z3)) {
                    break;
                }
            }
            while (true) {
                cout << "choose a place to place your second road on: " << endl;
                x4=getValidatedInteger("");
                y4=getValidatedInteger("");
                z4=getValidatedInteger("");
                if (placeroad(x4, y4, *s, z4)) {
                    break;
                }
            }
        }
    }

    // Checks if the game is over based on the points of each player.
    bool catan::isgameover() {
        if (p1.getpoints() >= 10) {
            cout << "player 1 wins" << endl;
            return true;
        }
        if (p2.getpoints() >= 10) {
            cout << "player 2 wins" << endl;
            return true;
        }
        if (p3.getpoints() >= 10) {
            cout << "player 3 wins" << endl;
            return true;
        }
        return false;
    }

    // Ends the game and prints the final scores.
    void catan::game_over() {
        cout << "game over" << endl;
        if (isgameover()) {
            cout << "player 1: " << p1.getname() << " points: " << p1.getpoints() << endl;
            cout << "player 2: " << p2.getname() << " points: " << p2.getpoints() << endl;
            cout << "player 3: " << p3.getname() << " points: " << p3.getpoints() << endl;
            return;
        } else {
            cout << "player 1: " << p1.getname() << " points: " << p1.getpoints() << endl;
            cout << "player 2: " << p2.getname() << " points: " << p2.getpoints() << endl;
            cout << "player 3: " << p3.getname() << " points: " << p3.getpoints() << endl;
            cout << "no one has won" << endl;
        }
    }

    // Adds specified items to a player's inventory.
    void catan::additemstoplayer(player &player, string item, int amount) {
        if (item == "brick") {
            player.addbrick(amount);
        }
        if (item == "wood") {
            player.addwood(amount);
        }
        if (item == "wheat") {
            player.addwheat(amount);
        }
        if (item == "ore") {
            player.addore(amount);
        }
        if (item == "wool") {
            player.addwool(amount);
        }
    }


    void catan::getResourcesFromMap(int cube) {
        bool flag = false;
        if (cube == 0) {
            flag = true;
        }
        // Loop through all hexagons on the board.
        for (int i = 0; i < b.getsize(); ++i) {
                for (int j = 0; j < b.getsizeC(i); ++j) {
                    if(b.gethexagon(i, j).getcube()==cube||flag){
                        for (size_t k = 0; k < 6; k++) {
                            auto a = b.gethexagon(i, j).getvertecs(k);
                            // Check if there is a building at the vertex.
                            if (a->getbuilding() != 0) {
                                // Distribute resources based on the building level (1 for village, 2 for city).
                                if(a->getplayer()->getid()==1){
                                    additemstoplayer(p1, b.gethexagon(i, j).getresource(), a->getbuilding());
                                }
                                if(a->getplayer()->getid()==2){
                                    additemstoplayer(p2, b.gethexagon(i, j).getresource(), a->getbuilding());
                                }
                                if(a->getplayer()->getid()==3){
                                    additemstoplayer(p3, b.gethexagon(i, j).getresource(), a->getbuilding());}
                            }
                        }
                    }
                }
            }
        }


    void catan::printRoadesVillagesCities() {
        int sum = 0;
        int sums=0;
        int sum1 = 0;
        int sum2 = 0;
        int sum3 = 0;
        // Loop through all hexagons and count roads and buildings.
        for (int i = 0; i < b.getsize(); ++i) {
            for (int j = 0; j < b.getsizeC(i); ++j) {
                sum=0;
                sums=0;
                for (size_t k = 0; k < 6; k++) {
                    auto a = b.gethexagon(i, j).getvertecs(k);
                    if (a->getbuilding() != 0) {
                        sum++;
                        // Count buildings for each player.
                        if(a->getplayer()->getid()==1){
                            sum1++;
                        }
                        if(a->getplayer()->getid()==2){
                            sum2++;
                        }
                        if(a->getplayer()->getid()==3){
                            sum3++;
                        }
                    }
                
                    auto c = b.gethexagon(i, j).getedge(k);
                    if (c->getroad() != 0) {
                        sums++;
                        // Count roads for each player.
                        if(c->getplayer().getid()==1){
                            sum1++;
                        }
                        if(c->getplayer().getid()==2){
                            sum2++;
                        }
                        if(c->getplayer().getid()==3){
                            sum3++;
                        }
                    }
                }
                cout << "hexagon: " << i << " " << j << " villages: " << sum << " roads: " << sums << endl;
            }
        }
    cout<<"player 1 villages and roads: "<<sum1<<endl;
    cout<<"player 2 villages and roads: "<<sum2<<endl;
    cout<<"player 3 villages and roads: "<<sum3<<endl;
    }
    void catan::trade(player &player1, player &player2,vector<std::string> item1, vector<std::string> item2, vector<int> amount1, vector<int> amount2){
        for (size_t i = 0; i < item1.size(); i++) {
            if (item1[i] == "brick") {
                player1.addbrick(-amount1[i]);
                player2.addbrick(amount1[i]);
            }
            if (item1[i] == "wood") {
                player1.addwood(-amount1[i]);
                player2.addwood(amount1[i]);

            }
            if (item1[i] == "wheat") {
                player1.addwheat(-amount1[i]);
                player2.addwheat(amount1[i]);
            }
            if (item1[i] == "ore") {
                player1.addore(-amount1[i]);
                player2.addore(amount1[i]);
            }
            if (item1[i] == "wool") {
                player1.addwool(-amount1[i]);
                player2.addwool(amount1[i]);
            }
        }
        for (size_t i = 0; i < item2.size(); i++) {
            if (item2[i] == "brick") {
                player2.addbrick(-amount2[i]);
                player1.addbrick(amount2[i]);
                cout<<"player 1 has "<<player1.getbrick()<<" bricks"<<endl;
            }
            if (item2[i] == "wood") {
                player2.addwood(-amount2[i]);
                player1.addwood(amount2[i]);
                cout<<"player 1 has "<<player1.getwood()<<" wood"<<endl;

            }
            if (item2[i] == "wheat") {
                player2.addwheat(-amount2[i]);
                player1.addwheat(amount2[i]);
            }
            if (item2[i] == "ore") {
                player2.addore(-amount2[i]);
                player1.addore(amount2[i]);
            }
            if (item2[i] == "wool") {
                player2.addwool(-amount2[i]);
                player1.addwool(amount2[i]);
            }
        }
    }
    bool catan:: istradevalid(player &player1,vector<std::string> item1, vector<int> amount1){
        bool flag = true;
        for (size_t i = 0; i < item1.size(); i++) {
            if (item1[i] == "brick") {
                if (player1.getbrick() < amount1[i]) {
                    flag = false;
                }
            }
            if (item1[i] == "wood") {
                if (player1.getwood() < amount1[i]) {
                    flag = false;
                }
            }
            if (item1[i] == "wheat") {
                if (player1.getwheat() < amount1[i]) {
                    flag = false;
                }
            }
            if (item1[i] == "ore") {
                if (player1.getore() < amount1[i]) {
                    flag = false;
                }
            }
            if (item1[i] == "wool") {
                if (player1.getwool() < amount1[i]) {
                    flag = false;
                }
            }
        }
        return flag;
    }
    void catan::tradeproccess(int i){
            int x1;
            player players[3] = {p1, p2, p3};
            bool valid = true;
            while (true)
            {
                cout << "Enter player index(0,1,2) to trade with: ";
                x1=getValidatedInteger("");
                x1=x1%3;
                
                if(x1==i){
                    cout<<"You can't trade with yourself"<<endl;
                    cout<<"if you want to trade with another player press 1 else press 0"<<endl;
                    int s;
                    s=getValidatedInteger("");
                    if (s==0){
                        valid=false;
                        break;
                    }
                }
                else{
                    valid=true;
                    break;
                }

            }

            if(!valid){
                return;
            }
            vector<string> items1;
            vector<string> items2;
            vector<int> amounts2;
            vector <int> amounts1;
            string item;
            int amount;
            while(true){
                cout << "Enter item to trade: ";
                cin >> item;
                cout<<"Enter amount to trade: ";
                amount=getValidatedInteger("");
                if((item=="wood"||item=="brick"||item=="wool"||item=="wheat"||item=="ore")&&amount>0){
                    items1.push_back(item);
                    amounts1.push_back(amount);
                    cout<<"if you want to trade another item press 1 else press 0"<<endl;
                    int s;
                    s=getValidatedInteger("");
                    if (s==0){
                        break;
                    }
                }
                else{
                    cout<<"Invalid item"<<endl;
                    cout<<"if you want to trade another item press 1 else press 0"<<endl;
                    int s;
                    s=getValidatedInteger("");
                    if (s==0){
                        valid=false;
                        break;
                    }
                }

            }
            while (true)
            {
                cout << "Enter item to get: ";
                cin >> item;
                cout<<"Enter amount to get: ";
                std::cin >> amount;
                if((item=="wood"||item=="brick"||item=="wool"||item=="wheat"||item=="ore")&&amount>0){
                    items2.push_back(item);
                    amounts2.push_back(amount);
                    cout<<"if you want to trade another item press 1 else press 0"<<endl;
                    int s;
                    s=getValidatedInteger("");
                    if (s==0){
                        break;
                    }
                }
                else{
                    cout<<"Invalid item"<<endl;
                    cout<<"if you want to trade another item press 1 else press 0"<<endl;
                    int s;
                    s=getValidatedInteger("");
                    if (s==0){
                        valid=false;
                        break;
                    }
                }
            }
            if(!valid){
                return;
            }
            bool x = istradevalid(players[i], items1, amounts1);
            bool y = istradevalid(players[x1], items2, amounts2);
            if(x&&y){
                cout<<"Trade is valid"<<endl;
                if(i==1&&x1==2){
                trade(p2, p3, items1, items2, amounts1, amounts2);
                }
                if(i==1&&x1==0){
                trade(p2, p1, items1, items2, amounts1, amounts2);
                }
                if(i==0&&x1==1){
                trade(p1, p2, items1, items2, amounts1, amounts2);
                }
                if(i==0&&x1==2){
                trade(p1, p3, items1, items2, amounts1, amounts2);
                }
                if(i==2&&x1==1){
                trade(p3, p2, items1, items2, amounts1, amounts2);
                }
                if(i==2&&x1==0){
                trade(p3, p1, items1, items2, amounts1, amounts2);
                }
                

            }
            else{
                if(x){
                    cout<<"Trade is not valid from your side"<<endl;
                }
                else{
                    cout<<"Trade is not valid from the other player side"<<endl;
                }
            }
    }
    void catan::printresources() {
        p1.printresources();
        p2.printresources();
        p3.printresources();
    }
    bool catan::buyCard(int i){
        if(i==0){
            if(p1.getore()>=1&&p1.getwool()>=1&&p1.getwheat()>=1){
                p1.addore(-1);
                p1.addwool(-1);
                p1.addwheat(-1);
            }
            else{
                return false;
            }
        }
        if(i==1){
            if(p2.getore()>=1&&p2.getwool()>=1&&p2.getwheat()>=1){
                p2.addore(-1);
                p2.addwool(-1);
                p2.addwheat(-1);
            }
            else{
                return false;
            }

        }
        if(i==2){
            if(p3.getore()>=1&&p3.getwool()>=1&&p3.getwheat()>=1){
                p3.addore(-1);
                p3.addwool(-1);
                p3.addwheat(-1);
            }
            else{
                return false;
            }
        }
        return true;
    }
    int catan:: randomizeCard(){
        srand(static_cast<unsigned int>(time(0)));
        int x = rand() % 4 + 1;
        return x;
    }
    void catan::getcard(int i,int z){
        if(z==0){
        if(i==0){
            cout<<"player 1 got a card monopoly"<<endl;
            p1.addwildcard(i);
        }
        if(i==1){
            p1.addwildcard(i);
            cout<<"player 1 got a card roadbuilding"<<endl;
        }
        if(i==2){
            p1.addwildcard(i);
            cout<<"player 1 got a card yearofplenty"<<endl;
        }
        if(i==3){
            p1.addwildcard(i);
            cout<<"player 1 got a card knight"<<endl;
        }
        }
        if(z==1){
        if(i==0){
            cout<<"player 2 got a card monopoly"<<endl;
            p2.addwildcard(i);
        }
        if(i==1){
            p2.addwildcard(i);
            cout<<"player 2 got a card roadbuilding"<<endl;
        }
        if(i==2){
            p2.addwildcard(i);
            cout<<"player 2 got a card yearofplenty"<<endl;
        }
        if(i==3){
            p2.addwildcard(i);
            cout<<"player 2 got a card knight"<<endl;
        }
        }
        if(z==2){
        if(i==0){
            cout<<"player 3 got a card monopoly"<<endl;
            p3.addwildcard(i);
        }
        if(i==1){
            p3.addwildcard(i);
            cout<<"player 3 got a card roadbuilding"<<endl;
        }
        if(i==2){
            p3.addwildcard(i);
            cout<<"player 3 got a card yearofplenty"<<endl;
        }
        if(i==3){
            p3.addwildcard(i);
            cout<<"player 3 got a card knight"<<endl;
        }
        }
    }
    void catan::roadBuildingCard(int i){
        int x1, y1, z1, x4, y4, z4;
        if(i==1){
            p2.substructwildcard(1);
            while (true) {
                cout << "choose a place to place your first road on: " << endl;
                x1=getValidatedInteger("");
                y1=getValidatedInteger("");
                z1=getValidatedInteger("");
                if (placeroad(x1, y1, p2, z1)) {
                    break;
                }
            }
            while (true) {
                cout << "choose a place to place your second road on: " << endl;
                x4=getValidatedInteger("");
                y4=getValidatedInteger("");
                z4=getValidatedInteger("");
                if (placeroad(x4, y4, p2, z4)) {
                    break;
                }
            }
        }
        if(i==2){
            p3.substructwildcard(1);
            while (true) {
                cout << "choose a place to place your first road on: " << endl;
                x1=getValidatedInteger("");
                y1=getValidatedInteger("");
                z1=getValidatedInteger("");
                if (placeroad(x1, y1, p3, z1)) {
                    break;
                }
            }
            while (true) {
                cout << "choose a place to place your second road on: " << endl;
                x4=getValidatedInteger("");
                y4=getValidatedInteger("");
                z4=getValidatedInteger("");
                if (placeroad(x4, y4, p3, z4)) {
                    break;
                }
            }
        }
        if(i==0){
            p1.substructwildcard(1);
            while (true) {
                cout << "choose a place to place your first road on: " << endl;
                x1=getValidatedInteger("");
                y1=getValidatedInteger("");
                z1=getValidatedInteger("");
                if (placeroad(x1, y1, p1, z1)) {
                    break;
                }
            }
            while (true) {
                cout << "choose a place to place your second road on: " << endl;
                x1=getValidatedInteger("");
                y1=getValidatedInteger("");
                z1=getValidatedInteger("");
                if (placeroad(x4, y4, p1, z4)) {
                    break;
                }
            }
        }
    }
    void catan::monopolCard(int i){
        string item;
        cout<<"Enter the item you want to monopolize: ";
        cin>>item;
        if(i==0){
            p1.substructwildcard(0);
            if(item=="brick"){
               if(p2.getbrick()>0){
                   p1.addbrick(1);
                   p2.addbrick(-1);
               }
               if(p3.getbrick()>0){
                   p1.addbrick(1);
                   p3.addbrick(-1);
               }
            }
            if(item=="wood"){
               if(p2.getwood()>0){
                   p1.addwood(1);
                   p2.addwood(-1);
               }
                if(p3.getwood()>0){
                     p1.addwood(1);
                     p3.addwood(-1);
                }
            }
            if(item=="wheat"){
               if(p2.getwheat()>0){
                   p1.addwheat(1);
                   p2.addwheat(-1);
               }
                if(p3.getwheat()>0){
                     p1.addwheat(1);
                     p3.addwheat(-1);
                }
            }
            if(item=="ore"){
               if(p2.getore()>0){
                   p1.addore(1);
                   p2.addore(-1);
               }
                if(p3.getore()>0){
                     p1.addore(1);
                     p3.addore(-1);
                }
            }
            if(item=="wool"){
               if(p2.getwool()>0){
                   p1.addwool(1);
                   p2.addwool(-1);
               }
                if(p3.getwool()>0){
                     p1.addwool(1);
                     p3.addwool(-1);
                }
            }
        }
        if(i==1){
            p2.substructwildcard(0);
          if(item=="brick"){
                if(p1.getbrick()>0){
                     p2.addbrick(1);
                     p1.addbrick(-1);
                }
                if(p3.getbrick()>0){
                     p2.addbrick(1);
                     p3.addbrick(-1);
                }}
                if(item=="wood"){
                if(p1.getwood()>0){
                     p2.addwood(1);
                     p1.addwood(-1);
                }
                 if(p3.getwood()>0){
                        p2.addwood(1);
                        p3.addwood(-1);
                 }
                }
                if(item=="wheat"){
                if(p1.getwheat()>0){
                     p2.addwheat(1);
                     p1.addwheat(-1);
                }
                 if(p3.getwheat()>0){
                    p2.addwheat(1);
                    p3.addwheat(-1);
                 }
                }
                if(item=="ore"){
                if(p1.getore()>0){
                     p2.addore(1);
                     p1.addore(-1);
                }
                 if(p3.getore()>0){
                    p2.addore(1);
                    p3.addore(-1);
                 }
                }
                if(item=="wool"){
                if(p1.getwool()>0){
                     p2.addwool(1);
                     p1.addwool(-1);
                }
                 if(p3.getwool()>0){
                        p2.addwool(1);
                        p3.addwool(-1);
                 }
                }
          }
          if(i==2){
            p3.substructwildcard(0);
            if(item=="brick"){
                if(p1.getbrick()>0){
                     p3.addbrick(1);
                     p1.addbrick(-1);
                }
                if(p2.getbrick()>0){
                     p3.addbrick(1);
                     p2.addbrick(-1);
                }}
                if(item=="wood"){
                if(p1.getwood()>0){
                     p3.addwood(1);
                     p1.addwood(-1);
                }
                 if(p2.getwood()>0){
                        p3.addwood(1);
                        p2.addwood(-1);
                 }
                }
                if(item=="wheat"){
                if(p1.getwheat()>0){
                     p3.addwheat(1);
                     p1.addwheat(-1);
                }
                 if(p2.getwheat()>0){
                    p3.addwheat(1);
                    p2.addwheat(-1);
                 }
                }
                if(item=="ore"){
                if(p1.getore()>0){
                     p3.addore(1);
                     p1.addore(-1);
                }
                 if(p2.getore()>0){
                    p3.addore(1);
                    p2.addore(-1);
                 }
                }
                if(item=="wool"){
                if(p1.getwool()>0){
                     p3.addwool(1);
                     p1.addwool(-1);
                }
                 if(p2.getwool()>0){
                        p3.addwool(1);
                        p2.addwool(-1);
                 }
                }
            }  
    }
    void catan::yearOfPlentyCard(int i){
        string item;
        string item2;
        cout<<"Enter the first item you want to get: ";
        cout<<"Enter the second item you want to get: ";
        cin>>item;
        cin>>item2;
        if(i==0){
            p1.substructwildcard(2);
            if((item=="brick")||(item2=="brick")){
                if(item==item2){
                    p1.addbrick(2);
                }
                p1.addbrick(1);
            }
            if((item=="wood")||(item2=="wood")){
                if(item==item2){
                    p1.addwood(2);
                }
                p1.addwood(1);
            }
            if((item=="wheat")||(item2=="wheat")){
                if(item==item2){
                    p1.addwheat(2);
                }
                p1.addwheat(1);
            }
            if((item=="ore")||(item2=="ore")){
                if(item==item2){
                    p1.addore(2);
                }
                p1.addore(1);
            }
            if((item=="wool")||(item2=="wool")){
                if(item==item2){
                    p1.addwool(2);
                }
                p1.addwool(1);
            }
        }
        if(i==1){
            p2.substructwildcard(2);
            if((item=="brick")||(item2=="brick")){
                if(item==item2){
                    p2.addbrick(2);
                }
                p2.addbrick(1);
            }
            if((item=="wood")||(item2=="wood")){
                if(item==item2){
                    p2.addwood(2);
                }
                p2.addwood(1);
            }
            if((item=="wheat")||(item2=="wheat")){
                if(item==item2){
                    p2.addwheat(2);
                }
                p2.addwheat(1);
            }
            if((item=="ore")||(item2=="ore")){
                if(item==item2){
                    p2.addore(2);
                }
                p2.addore(1);
            }
            if((item=="wool")||(item2=="wool")){
                if(item==item2){
                    p2.addwool(2);
                }
                p2.addwool(1);
            }
        }
        if(i==2){
            p3.substructwildcard(2);
            if((item=="brick")||(item2=="brick")){
                if(item==item2){
                    p3.addbrick(2);
                }
                p3.addbrick(1);
            }
            if((item=="wood")||(item2=="wood")){
                if(item==item2){
                    p3.addwood(2);
                }
                p3.addwood(1);
            }
            if((item=="wheat")||(item2=="wheat")){
                if(item==item2){
                    p3.addwheat(2);
                }
                p3.addwheat(1);
            }
            if((item=="ore")||(item2=="ore")){
                if(item==item2){
                    p3.addore(2);
                }
                p3.addore(1);
            }
            if((item=="wool")||(item2=="wool")){
                if(item==item2){
                    p3.addwool(2);
                }
                p3.addwool(1);
            }
        }            
    }
    void catan::knightCard(int i){
        if(i==0){
            p1.addwildcard(3);
            bool v= p1.check3Knights();
            if(v){
                cout<<"player 1 has the largest army"<<endl;
                p1.addpoints(2);
                }
        }
        if(i==1){
            p2.addwildcard(3);
            bool v2=p2.check3Knights();
            if(v2){
                cout<<"player 2 has the largest army"<<endl;
                p2.addpoints(2);
            }

        }
        if(i==2){
            p3.addwildcard(3);
            bool v3=p3.check3Knights();
            if(v3){
                cout<<"player 3 has the largest army"<<endl;
                p3.addpoints(2);
            }
        }
    }
    bool catan::checkCard(int i,int wildcard){
        if(i==0){
            if(p1.getwildcard(wildcard)>0){
                return true;
            }
        }
        if(i==1){
            if(p2.getwildcard(wildcard)>0){
                return true;
            }
        }
        if(i==2){
            if(p3.getwildcard(wildcard)>0){
                return true;
            }
        }
        return false;
    }
    bool catan :: checkCity(int i){// need one from each 
        if(i==0){
            if(p1.getbrick()>=1&&p1.getwheat()>=1&&p1.getwood()>=1&&p1.getore()>=1&&p1.getwool()>=1){
                return true;
            }
            
        }
        if(i==1){
            if(p2.getbrick()>=1&&p2.getwheat()>=1&&p2.getwood()>=1&&p2.getore()>=1&&p2.getwool()>=1){
                return true;
            }
        }
        if(i==2){
            if(p3.getbrick()>=1&&p3.getwheat()>=1&&p3.getwood()>=1&&p3.getore()>=1&&p3.getwool()>=1){
                return true;
            }
        }
        return false;
    }
    bool catan::checkRoad(int i){
        if(i==0){
            if(p1.getwood()>=1){
                return true;
            }
        }
        if(i==1){
            if(p2.getwood()>=1){
                return true;
            }
        }
        if(i==2){
            if(p3.getwood()>=1){
                return true;
            }
        }
        return false;
    }
    void catan::buildCity(int i){
        if(i==0){
            p1.addbrick(-1);
            p1.addwheat(-1);
            p1.addwood(-1);
            p1.addore(-1);
            p1.addwool(-1);
            p1.addpoints(2);
        }
        if(i==1){
            p2.addbrick(-1);
            p2.addwheat(-1);
            p2.addwood(-1);
            p2.addore(-1);
            p2.addwool(-1);
            p2.addpoints(2);
        }
        if(i==2){
            p3.addbrick(-1);
            p3.addwheat(-1);
            p3.addwood(-1);
            p3.addore(-1);
            p3.addwool(-1);
            p3.addpoints(2);
        }
    }
    void catan::buildRoad(int i){
        if(i==0){
            p1.addwood(-1);
        }
        if(i==1){
            p2.addwood(-1);
        }
        if(i==2){
            p3.addwood(-1);
        }
    }
    bool catan::checkVillage(int i ){//need break and wheat
        if (i==0){
            if(p1.getbrick()>=1&&p1.getwheat()>=1){
                return true;
            }
        }
        if (i==1){
            if(p2.getbrick()>=1&&p2.getwheat()>=1){
                return true;
            }
        }
        if (i==2){
            if(p3.getbrick()>=1&&p3.getwheat()>=1){
                return true;
            }
        }
        return false;
    }
    void catan::buildVillage(int i){
        if(i==0){
            p1.addbrick(-1);
            p1.addwheat(-1);
            p1.addpoints(1);
        }
        if(i==1){
            p2.addbrick(-1);
            p2.addwheat(-1);
            p2.addpoints(1);
        }
        if(i==2){
            p3.addbrick(-1);
            p3.addwheat(-1);
            p3.addpoints(1);
        }
    }
    int catan:: getValidatedInteger(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the input
            cout << "Invalid input. Please enter a valid integer." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any leftover input
            return value;
        }
    }
}
}
