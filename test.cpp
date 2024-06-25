#include "doctest.h"
#include "catan.hpp"
#include "board.hpp"
#include "player.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace ariel;
using namespace std;
TEST_CASE("checking trade"){
    player p1("Player1");
    player p2("Player2");
    player p3("Player3");

    // Give initial resources to players
    p1.addbrick(3);
    p1.addwood(3);
    p2.addbrick(1);
    p2.addwood(1);

    // Redirect cout to ostringstream
    std::ostringstream oss;
    std::streambuf* cout_buf = std::cout.rdbuf(); // Save old buffer
    std::cout.rdbuf(oss.rdbuf()); // Redirect cout to oss

    // Items and amounts to trade
    vector<string> items1 = {"brick", "wood"};
    vector<string> items2 = {"brick", "wood"};
    vector<int> amounts1 = {1, 2};
    vector<int> amounts2 = {1, 1};

    // Create a catan object (assuming the board is not needed for this specific test)
    board b;
    catan game(b, p1, p2, p3);

    // Perform the trade
    game.trade(p1, p2, items1, items2, amounts1, amounts2);

    // Restore cout
    std::cout.rdbuf(cout_buf);

    // Expected output string
    std::string expected_output = 
        "player 1 has 3 bricks\n"
        "player 1 has 2 wood\n";

    // Check if the output is as expected
    std::string output = oss.str();
    CHECK(output == expected_output);

    // Verify resource counts (as a sanity check)
    CHECK(p1.getbrick() == 3);  // 3 - 1 + 1
    CHECK(p1.getwood() == 2);   // 3 - 2 + 1
    CHECK(p2.getbrick() == 1);  // 1 - 1 + 1
    CHECK(p2.getwood() == 2);   // 1 - 1 + 2
}
TEST_CASE("checking buyCard") {
    // Initialize players
    player p1("Player1");
    player p2("Player2");
    player p3("Player3");

    // Initialize the game with a board and players
    board b;
    catan game(b, p1, p2, p3);

    // Give resources to player 1 to buy a card
    p1.addore(1);
    p1.addwool(1);
    p1.addwheat(1);

    // Redirect cout to ostringstream to capture output
    std::ostringstream oss;
    std::streambuf* cout_buf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    // Attempt to buy a card for player 1
    bool cardBought = game.buyCard(0);
    CHECK(cardBought == true);

    // Randomize and get a card for player 1
    int cardType = game.randomizeCard();
    game.getcard(cardType, 0);

    // Restore cout
    std::cout.rdbuf(cout_buf);

    // Check output and resources
    std::string output = oss.str();
    if (cardType == 0) {
        CHECK(output.find("player 1 got a card monopoly") != std::string::npos);
    } else if (cardType == 1) {
        CHECK(output.find("player 1 got a card roadbuilding") != std::string::npos);
    } else if (cardType == 2) {
        CHECK(output.find("player 1 got a card yearofplenty") != std::string::npos);
    } else if (cardType == 3) {
        CHECK(output.find("player 1 got a card knight") != std::string::npos);
    }

    // Verify resources after buying a card
    CHECK(p1.getore() == 0);
    CHECK(p1.getwool() == 0);
    CHECK(p1.getwheat() == 0);
}
TEST_CASE("checking useCard - monopoly") {
    // Initialize players
    player p1("Player1");
    player p2("Player2");
    player p3("Player3");

    // Initialize the game with a board and players
    board b;
    catan game(b, p1, p2, p3);

    // Give resources to players
    p1.addwildcard(0); // Player 1 has a monopoly card
    p2.addbrick(3);    // Player 2 has bricks
    p3.addbrick(2);    // Player 3 has bricks

    // Simulate input for monopoly card usage
    std::istringstream input("brick\n");
    std::cin.rdbuf(input.rdbuf());  // Redirect cin to use the input string

    // Redirect cout to ostringstream to capture output
    std::ostringstream oss;
    std::streambuf* cout_buf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    // Use the monopoly card for player 1
    game.monopolCard(0);

    // Restore cout and cin
    std::cout.rdbuf(cout_buf);
    std::cin.rdbuf(input.rdbuf()); // Restore original cin buffer

    // Check output and resources
    std::string output = oss.str();
    CHECK(output.find("Enter the item you want to monopolize: ") != std::string::npos);

    // Verify resources after using the monopoly card
    CHECK(p1.getbrick() == 2);  // Player 1 should have 5 bricks (3 from p2 + 2 from p3)
    CHECK(p2.getbrick() == 2);  // Player 2 should have no bricks left
    CHECK(p3.getbrick() == 1);  // Player 3 should have no bricks left
}


TEST_CASE("checking useCard - yearofplenty") {
    // Initialize players
    player p1("Player1");
    player p2("Player2");
    player p3("Player3");

    // Initialize the game with a board and players
    board b;
    catan game(b, p1, p2, p3);

    // Give resources to players
    p1.addwildcard(2); // Player 1 has a yearofplenty card

    // Simulate input for year of plenty card usage
    std::istringstream input("brick\nwood\n");
    std::cin.rdbuf(input.rdbuf());  // Redirect cin to use the input string

    // Redirect cout to ostringstream to capture output
    std::ostringstream oss;
    std::streambuf* cout_buf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    // Use the yearofplenty card for player 1
    game.yearOfPlentyCard(0);

    // Restore cout and cin
    std::cout.rdbuf(cout_buf);
    std::cin.rdbuf(input.rdbuf()); // Restore original cin buffer

    // Check output and resources
    std::string output = oss.str();
    CHECK(output.find("Enter the first item you want to get: ") != std::string::npos);
    CHECK(output.find("Enter the second item you want to get: ") != std::string::npos);

    // Verify resources after using the year of plenty card
    CHECK(p1.getbrick() == 1);  // Player 1 should have received 1 bricks
    CHECK(p1.getwood() == 1);   // Player 1 should have received 1 wood
}

TEST_CASE("checking useCard - knight") {
    // Initialize players
    player p1("Player1");
    player p2("Player2");
    player p3("Player3");

    // Initialize the game with a board and players
    board b;
    catan game(b, p1, p2, p3);

    // Give resources to players
    p1.addwildcard(3); // Player 1 has a knight card
    p1.addwildcard(3); // Player 1 has a knight card
    game.knightCard(0);

    

    // Check if player 1 now has the largest army
    CHECK(p1.getpoints() == 2);
    CHECK(p2.getpoints() == 0);
    CHECK(p3.getpoints() == 0);   
}

TEST_CASE("checking rolldices") {
    // Initialize players
    player p1("Player1");
    player p2("Player2");
    player p3("Player3");

    // Initialize the game with a board and players
    board b;
    catan game(b, p1, p2, p3);

    // Roll the dice multiple times to check the range and randomness
    for (int i = 0; i < 5; ++i) {
        int sum = game.rolldices();
        CHECK(sum >= 2);  // The minimum possible sum (1 + 1)
        CHECK(sum <= 12); // The maximum possible sum (6 + 6)
    }
}
TEST_CASE("checking getResourcesFromMap") {
    // Initialize players
    player p1("Player1");
    player p2("Player2");
    player p3("Player3");

    // Initialize the game with a board and players
    board b;
    catan game(b, p1, p2, p3);

    // Simulate setting up the board
    // Manually set up a hexagon with a resource and a building for the test purpose.
    // Set the resources and the cube number for the hexagons
    b.gethexagon(0, 0).setresource("wood");
    b.gethexagon(0, 0).setcube(6);
    b.gethexagon(0, 0).getvertecs(0)->setbuilding(1); // Set a village at vertex 0
    b.gethexagon(0, 0).getvertecs(0)->setplayer(p1); // Assign player 1 to the vertex

    b.gethexagon(0, 1).setresource("brick");
    b.gethexagon(0, 1).setcube(4);
    b.gethexagon(0, 1).getvertecs(0)->setbuilding(2); // Set a city at vertex 0
    b.gethexagon(0, 1).getvertecs(0)->setplayer(p2); // Assign player 2 to the vertex

    // Give initial resources to players for testing
    p1.addwood(0);
    p2.addbrick(0);
    p3.addwood(0);

    // Roll the dice with a value of 8 and distribute resources
    game.getResourcesFromMap(8);

    // Check that resources were distributed correctly
    CHECK(p1.getwood() == 0);  // Player 1 should receive 1 wood for the village
    CHECK(p2.getbrick() == 0); // Player 2 should receive 2 bricks for the city
    CHECK(p3.getwood() == 0);  // Player 3 should receive no wood
}
TEST_CASE("checking quit functionality") {
    // Initialize players
    player p1("Player1");
    player p2("Player2");
    player p3("Player3");

    // Initialize the game with a board and players
    board b;
    catan game(b, p1, p2, p3);

    // Give some points to players for testing
    p1.addpoints(3);
    p2.addpoints(5);
    p3.addpoints(2);

    // Redirect cout to ostringstream to capture output
    std::ostringstream oss;
    std::streambuf* cout_buf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    // Simulate the quit command
    game.game_over();

    // Restore cout
    std::cout.rdbuf(cout_buf);

    // Check the output
    std::string output = oss.str();
    CHECK(output.find("game over") != std::string::npos);
    CHECK(output.find("player 1: Player1 points: 3") != std::string::npos);
    CHECK(output.find("player 2: Player2 points: 5") != std::string::npos);
    CHECK(output.find("player 3: Player3 points: 2") != std::string::npos);
    CHECK(output.find("no one has won") != std::string::npos);
}


