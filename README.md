Catan Game
Welcome to the Catan game! This is a simple implementation of the popular board game "Catan". Below are the instructions on how to set up and play the game.

How to Run
first you compile using make 
After compiling, you can run the game using the following command: ./m
Game Setup
When you start the game, you will be prompted to enter names for three players.
The game will then initialize the board and players.
Gameplay
The game consists of a series of turns where players can perform various actions. Here is a breakdown of the commands and their functions:

Commands
roll dices: Roll the dice to determine resource production for the turn.
trade: Initiate a trade with another player.
buycard: Buy a development card.
usecard: Use a development card. You will be prompted to specify the type of card to use (monopol, roadbuilding, yearofplenty, knight).
build: Build a structure. You will be prompted to specify what you want to build (village, city, road) and provide coordinates.
printmap: Display the current state of the game board.
finish: End your turn.
quit: Quit the game.
Building
When you choose to build, you will be asked to specify what you want to build:

village: Requires sufficient resources. You will need to provide the x and y coordinates and the vertex number where you want to place the village.
city: Requires sufficient resources. You will need to provide the x and y coordinates and the vertex number where you want to place the city.
road: Requires sufficient resources. You will need to provide the x and y coordinates and the edge number where you want to place the road.
Development Cards
If you choose to use a development card, you will be prompted to specify the type of card:

monopol: Steal all resources of one type from other players.
roadbuilding: Build two roads for free.
yearofplenty: Take any two resource cards from the bank.
knight: Move the robber and steal a resource from another player.
Ending the Game
You can end the game at any time by entering the quit command. If you choose to quit, you will be prompted to check the result by typing 1.

if you wanna run the test you write make test and then ./test
