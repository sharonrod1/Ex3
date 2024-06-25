#include "catan.hpp"
#include "board.hpp"
#include "player.hpp"
#include <iostream>
#include <string>
using namespace ariel;
using namespace std;


int main() {
    std::string player1_name;
    std::string player2_name;
    std::string player3_name;
    std::string command;
    cout<<"Welcome to Catan game"<<endl;
    std::cout << "Enter name for player 1: ";
    std::getline(std::cin, player1_name);
    std::cout << "Enter name for player 2: ";
    std::getline(std::cin, player2_name);
    std::cout << "Enter name for player 3: ";
    std::getline(std::cin, player3_name);

    // Create players using the input names
    player p1(player1_name);
    player p2(player2_name);
    player p3(player3_name);

    board b;
    ariel::catan c(b, p1, p2, p3);
    c.printmap();
    c.choosestarting();
    c.getResourcesFromMap(0);
    c.printresources();
    player players[3] = {p1, p2, p3};
    int sum=0;
    bool finishdT = true;
    bool role = true;
    bool quit = true;
        for (int i = 0; i < 3; i++)
        {   
            if(!quit){
                break;
            }
            finishdT = true;
            role = true;
            c.printmap();
            while(finishdT){
            while(true){
            cout << "Player " << players[i].getname() << " turn" << endl;
            cout << "Enter command:(roll dices,trade,buycard,usecard,quit,finish,build,printmap) ";
            std::getline(std::cin, command);
            if(command==""){
                std::getline(std::cin, command);
            }
                if (command == "roll dices" || command == "trade" || command == "buycard" || command == "usecard" || command == "quit"||(command=="finish")||command=="printmap"||command=="build")
                {
                    break;
                }
                else
                {
                    cout << "invalid command" << endl;
                }
            }
            if(command=="printmap"){
                c.printmap();
                c.printresources();
                continue;
            }
            if(command=="build"){
                cout<<"Enter what you want to build:(village,city,road) ";
                std::getline(std::cin, command);
                if(command=="village"){
                    if(!c.checkVillage(i)){
                        cout<<"you dont have enough resources"<<endl;
                        continue;
                    }
                    c.buildVillage(i);
                    cout<<"Enter x,y and vertex number: ";
                    int x,y,vertex;
                    x=c.getValidatedInteger("");
                    y=c.getValidatedInteger("");
                    vertex=c.getValidatedInteger("");
                    if(c.placevillage(x,y,players[i],vertex)){
                        cout<<"village was built"<<endl;
                    }
                    else{
                        cout<<"village wasnt built"<<endl;
                    }
                }
                else if(command=="city"){
                    if(!c.checkCity(i)){
                        cout<<"you dont have enough resources"<<endl;
                        continue;
                    }
                    cout<<"Enter x,y and vertex number: ";
                    c.buildCity(i);
                    int x,y,vertex;
                    x=c.getValidatedInteger("");
                    y=c.getValidatedInteger("");
                    vertex=c.getValidatedInteger("");
                    if(c.placecity(x,y,players[i],vertex)){
                        cout<<"city was built"<<endl;
                    }
                    else{
                        cout<<"city wasnt built"<<endl;
                    }
                }
                else if(command=="road"){
                    if(!c.checkRoad(i)){
                        cout<<"you dont have enough resources"<<endl;
                        continue;
                    }
                    c.buildRoad(i);
                    cout<<"Enter x,y and edge number: ";
                    int x,y,edge;
                    x=c.getValidatedInteger("");
                    y=c.getValidatedInteger("");
                    edge=c.getValidatedInteger("");
                    if(c.placeroad(x,y,players[i],edge)){
                        cout<<"road was built"<<endl;
                    }
                    else{
                        cout<<"road wasnt built"<<endl;
                    }
                }
                c.printresources();
                continue;
            
            }
            if (command == "roll dices")
            {
                if(!role){
                    cout<<"you already rolled the dices"<<endl;
                    continue;
                }
                sum = c.rolldices();
                c.getResourcesFromMap(sum);
                cout<<"the cube  is: "<<sum<<endl;
                c.printresources();
                role=false;
            }
            else if (command == "trade")
            {   
                c.tradeproccess(i);
                c.printresources();
            }
            else if (command == "quit")
            {
                c.game_over();
                quit=false;
                break;
                
            }
            else if(command=="finish"){
                finishdT = false;
                cout<<"finish turn"<<endl;
                if(i==3){
                    break;
                }

            }
            else if (command == "buycard")
            {   
                bool a =c.buyCard(i);
                if(a){
                    cout<<"card was bought"<<endl;
                    int z = c.randomizeCard();
                    c.getcard(z,i);
                }
                else{
                    cout<<"you dont have enough resources"<<endl;
                }
            }
            else if (command == "usecard")
            {
                cout << "Enter card type:(monopol,roadbuilding,yearofplenty,knight) ";
                std::getline(std::cin, command);
                if (command == "monopol")
                {
                    if (c.checkCard(i, 0) == false)
                    {
                        cout << "you dont have this card" << endl;
                        continue;
                    }
                    c.monopolCard(i);
                    c.printresources();
                }
                else if (command == "roadbuilding")
                {
                    if (c.checkCard(i, 1) == false)
                    {
                        cout << "you dont have this card" << endl;
                        continue;
                    }
                    c.roadBuildingCard(i);
                    c.printresources();
                }
                else if (command == "yearofplenty")
                {
                    if (c.checkCard(i, 2) == false)
                    {
                        cout << "you dont have this card" << endl;
                        continue;
                    }
                    c.yearOfPlentyCard(i);
                    c.printresources();
                }
                else if (command == "knight")
                {
                    if (c.checkCard(i, 3) == false)
                    {
                        cout << "you dont have this card" << endl;
                        continue;
                    }
                    c.knightCard(i);
                    c.printresources();
                }
            }
            

        }
    }
    if(quit){
    cout << "Game over" << endl;
    cout<< "if you wanna check the result type 1 else type 0"<<endl;
    int x;
    cin>>x;
    if(x==1){
        c.game_over();
        }
    }
    return 0;
}

