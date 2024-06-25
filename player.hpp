#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <vector>
#include <string>
using namespace std;
namespace ariel{
    class player{
        private:
        static int id;
        int playerid;
        string name;
        int wood;
        int brick;
        int wool;
        int wheat;
        int ore;
        int points;
        vector<int> wildcards;// first is monopoly, second is roadbuilding, third is yearofplenty, fourth is knight
        public:
        player();
        player( const string &name);
        string getname() const;
        int getid() const {return playerid;}
        int getpoints() const {return points;}
        int rolldices();
        void addpoints(int amount);
        void addwood(int amount);
        void addbrick(int amount);
        void addwool(int amount);
        void addwheat(int amount);
        void addore(int amount);
        void addwildcard(int index);
        int getwood() const {return wood;}
        int getbrick() const {return brick;}
        int getwool() const {return wool;}
        int getwheat() const {return wheat;}
        int getore() const {return ore;}
        void printresources() const;
        bool check3Knights() const;
        int getwildcard(int index) const;
        void substructwildcard(int index) {wildcards[index]--;}
        
    };
    
    }
#endif