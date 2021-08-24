#ifndef __GAMEDRIVER_H__
#define __GAMEDRIVER_H__

#include <vector>
#include "Player.h"
#include "Head.h"

using namespace std;

enum class GAME_STATE {
    REPEAT_TURN   = -1,
    END_TURN      = 0,
    CONTINUE_PLAY = 1,
};

class GameDriver
{
private:
    int no_players;
    vector<Player> players;
    vector<Head> heads;
    bool testing_mode;

    bool start_turn(int player);
    int play_card(int player_index, Card &current_card);
    vector<Card> create_deck_and_shuffle();
    void distribute_to_player();
    GAME_STATE check_rules(Card card, int head_index, int player_index);
    void cut_off_head(int player_index);
    void insert_head(Card card);
    Head return_oldest_head();
    void print(int current_player, int remain_turn = 0);
    void print_head();
    void print_players(int current_player, int remain_turn);

public:
    explicit GameDriver(int no_players, bool testing = false);
    ~GameDriver();

    void start_game();
};

#endif // __GAMEDRIVER_H__
