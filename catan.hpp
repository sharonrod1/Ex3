
#include "board.hpp"
#include "player.hpp"
#include <string>
#include <iostream>
using namespace std;

namespace ariel {
    class catan {
    private:
        board b;
        player &p1;
        player &p2;
        player &p3;
        static int turn;

    public:
        catan(board &c, player &p1, player &p2, player &p3);
        void printmap();
        int rolldices();
        bool placevillage(int x, int y, player &player, int vertex);
        bool placecity(int x, int y, player &player, int vertex);
        bool placeroad(int x, int y, player &player, int edge);
        board getboard();
        void choosestarting();
        bool isgameover();
        void game_over();
        void getResourcesFromMap(int cube);
        void printRoadesVillagesCities();
        void additemstoplayer(player &player, string item, int amount);
        void trade(player &player1, player &player2,vector<string> item1, vector<std::string> item2, vector<int> amount1, vector<int> amount2);
        bool istradevalid(player &player1,vector<std::string> item1, vector<int> amount1);
        void tradeproccess(int i);
        void printresources();
        bool buyCard(int i);
        int  randomizeCard();
        void monopolCard(int i);
        void roadBuildingCard(int i);
        void yearOfPlentyCard(int i);
        void knightCard(int i);
        void getcard(int i,int z);
        bool checkCard(int i, int wildcard);
        bool checkCity(int i);
        bool checkVillage(int i);
        bool checkRoad(int i);
        void buildVillage(int i);
        void buildCity(int i);
        void buildRoad(int i);
        int getValidatedInteger(const string&);

    };
}
