#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <cstring>
#include <string>
#include "GameDriver.h"
#include "Utils.h"

using namespace std;

int main(int argc, char const *argv[])
{
    bool testing_mode = false;
    if (argc > 1)
    {
        int res = strcmp(argv[1], "-testing");
        testing_mode = (res == 0) ? true : false;
        cout << "Testing mode is " << (testing_mode ? "on" : "off") << endl;
    }

    int no_players = INVALID;
    while (no_players <= 1)
    {
	cout << "You just started a game of Hydra." << endl;
        string output = "How many players do you want in the game? There must be more than 1 player for the game to run.";
	no_players = util.custom_cin(no_players, output);
	if (no_players < 1) {
	   cout << "Invalid Input. Please try again." << endl;
	}
    }

    GameDriver game_driver(no_players, testing_mode);
    game_driver.start_game();
}
