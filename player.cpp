#include "player.hpp"
#include <iostream>

int ariel::player::id = 0;

ariel::player::player() : wood(0), brick(0), wool(0), wheat(0), ore(0), points(0) {
    playerid = ++id;
}

ariel::player::player(const string &name) : name(name), wood(0), brick(0), wool(0), wheat(0), ore(0), points(0) {
    playerid = ++id;
    for (int i=0;i<4;i++){
    wildcards.push_back(0);}

}

string ariel::player::getname() const {
    return name;
}

void ariel::player::addwood(int amount) {
    wood += amount;
}

void ariel::player::addbrick(int amount) {
    brick += amount;
}

void ariel::player::addwool(int amount) {
    wool += amount;
}

void ariel::player::addwheat(int amount) {
    wheat += amount;
}

void ariel::player::addore(int amount) {
    ore += amount;
}
void ariel::player::addpoints(int amount) {
    points += amount;
}
void ariel::player::addwildcard(int index) {
    wildcards.at(index)++;
}
bool ariel::player::check3Knights() const {
    if(wildcards[3]==3){
        return true;
    
    }
    return false;
}
void ariel::player::printresources() const {
    cout << "player " << name << " has " << wood << " wood" << endl;
    cout << "player " << name << " has " << brick << " brick" << endl;
    cout << "player " << name << " has " << wool << " wool" << endl;
    cout << "player " << name << " has " << wheat << " wheat" << endl;
    cout << "player " << name << " has " << ore << " ore" << endl;
}
int ariel::player::getwildcard(int index) const {
    return wildcards[index];
}
