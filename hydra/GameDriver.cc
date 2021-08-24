#include "GameDriver.h"

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <ctime>

#include "Utils.h"

using namespace std;

GameDriver::GameDriver(int no_players, bool testing)
{
    this->no_players = no_players;
    testing_mode = testing;
    Player player(testing_mode);
    players.resize(no_players, player);
}

GameDriver::~GameDriver()
{
}

void GameDriver::start_game()
{
    distribute_to_player();
    int player_index = 0;
    while (true)
    {
        bool is_won = start_turn(player_index);
        if (is_won)
        {
            break;
        }

        player_index++;
        player_index = (player_index >= no_players) ? 0 : player_index;
    }
    cout << "Player " << player_index + 1 << " wins!" << endl;
}

vector<Card> GameDriver::create_deck_and_shuffle()
{
    vector<Card> total_cards;
    for (int i = 0; i < no_players; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 1; k < 14; k++)
            {
                string number;
                string suit;
                switch (j)
                {
                case 0:
                    suit = "H";
                    break;
                case 1:
                    suit = "D";
                    break;
                case 2:
                    suit = "S";
                    break;
                default:
                    suit = "C";
                    break;
                }
                if (k == 1)
                {
                    number = "A";
                }
                else if (k == 11)
                {
                    number = "J";
                }
                else if (k == 12)
                {
                    number = "Q";
                }
                else if (k == 13)
                {
                    number = "K";
                }
                else
                {
                    number = to_string(k);
                }
                string new_card = number + suit;
                Card card(new_card);
                total_cards.push_back(card);
            }
        }
        Card card("Joker");
        total_cards.push_back(card);
        total_cards.push_back(card);
    }
    srand ( unsigned ( time(0) ) );
    random_shuffle (total_cards.begin(), total_cards.end());
    return total_cards;
}

void GameDriver::distribute_to_player()
{
    vector<Card> decks = create_deck_and_shuffle();

    int no_of_cards = 54;
    if (testing_mode == true)
    {
        while (true)
        {
            no_of_cards = util.custom_cin(no_of_cards, "How many cards should each player have?");
            if (no_of_cards <= 0 || no_of_cards > 54)
                continue;
            else
                break;
        }
    }

    for (int i = 0; i < no_players; i++)
    {
        for (int j = 0; j < no_of_cards; j++)
        {
            players[i].insert_to_drawpile(decks[i * no_of_cards + j]);
        }
    }
}

GAME_STATE GameDriver::check_rules(Card card, int head_index, int player_index)
{

    if (card.get_name() == "Joker")
    {
        string temp = "";
        while (true)
        {
            temp = util.custom_cin(temp, "Joker value?");
            card.set_name(temp);

            if ((card.get_value() != INVALID) &&
                ((card.get_value() <= heads[head_index].get_top().get_value()) || (heads[head_index].get_top().get_value() == 1)))
            {
                break;
            }

            if (card.get_value() > heads[head_index].get_top().get_value())
            {
                return GAME_STATE::REPEAT_TURN;
            }
        }
    }

    if (card.get_value() < heads[head_index].get_top().get_value())
    {
        heads[head_index].add_card(card);
        return GAME_STATE::CONTINUE_PLAY;
    }
    else if (card.get_value() == heads[head_index].get_top().get_value())
    {
        heads[head_index].add_card(card);
        return GAME_STATE::END_TURN;
    }
    else if (heads[head_index].get_top().get_value() == 1)
    {
        heads[head_index].add_card(card);

        if (card.get_value() == 1)
        {
            return GAME_STATE::END_TURN;
        }
    }
    else if (card.get_value() > heads[head_index].get_top().get_value())
    {
        players[player_index].insert_to_discardpile(card);
        players[player_index].reserve_to_drawpile();
        players[player_index].cutoff_to_discard(return_oldest_head().cut_off());

        cut_off_head(player_index);

        return GAME_STATE::END_TURN;
    }
    return GAME_STATE::CONTINUE_PLAY;
}

void GameDriver::cut_off_head(int player_index)
{
    if (testing_mode == true)
    {
        cout << "You are about to cutoff head in testing mode, please set value for the 2 new heads" << endl;
    }

    insert_head(players[player_index].draw_card());
    insert_head(players[player_index].draw_card());
    for (int i = 0; i < static_cast<int>(heads.size() - 1); i++)
    {
        heads[i] = heads[i + 1];
    }
    heads.pop_back();
}

void GameDriver::insert_head(Card card)
{
    Head head(card, heads.back().get_head_index() + 1);
    heads.push_back(head);
}

Head GameDriver::return_oldest_head()
{
    return heads.front();
}

bool GameDriver::start_turn(int player_index)
{
    static bool first_turn = true;
    if ((first_turn == true) && (player_index == 0))
    {
        Head head(players[player_index].draw_card(), 1);
        heads.push_back(head);
        first_turn = false;
        print(-1);
    }
    else
    {
        Card current_card("");
        for (int i = 0; i < static_cast<int>(heads.size()); i++)
        {
            if (players[player_index].is_won())
            {
                return true;
            }

            print(-1);
            cout << endl;
            cout << "Player " << player_index + 1 << ", it is your turn." << endl;
            cout << endl;
            players[player_index].draw_card();
            print(player_index, heads.size() - i - 1);

            current_card = players[player_index].get_current_card();

            int idx = play_card(player_index, current_card);
            if (idx == INVALID)
                continue;

            GAME_STATE check = check_rules(current_card, idx, player_index);
            if (check == GAME_STATE::REPEAT_TURN)
            {
                i--;
                players[player_index].insert_to_drawpile(current_card);
            }
            else if (check == GAME_STATE::END_TURN)
            {
                break;
            }
            else if (check == GAME_STATE::CONTINUE_PLAY)
            {
                continue;
            }
        }

        if (players[player_index].is_won())
        {
            return true;
        }

        if (players[player_index].get_reserve().get_value() != INVALID)
        {
            players[player_index].insert_to_drawpile(players[player_index].get_reserve());
            players[player_index].get_reserve().set_name("");
        }
    }

    return false;
}

void GameDriver::print(int current_player, int remain_turn)
{
    cout << endl;
    print_head();
    cout << endl;
    print_players(current_player, remain_turn);
}

void GameDriver::print_head()
{
    cout << "Heads:" << endl;

    for (int i = 0; i < static_cast<int>(heads.size()); i++)
    {
        heads[i].print_head();
    }
}

void GameDriver::print_players(int current_player, int remain_turn)
{
    cout << "Players:" << endl;
    for (int i = 0; i < static_cast<int>(players.size()); i++)
    {
        cout << "Player " << i + 1 << ": ";
        if (i == current_player)
        {
            players[i].print_current_players(remain_turn);
        }
        else
        {
            players[i].print_players();
        }
    }
}

int GameDriver::play_card(int player_index, Card &current_card)
{
    int input_head_index = INVALID;
    int idx = INVALID;

    while (true)
    {
        cout << endl;
        cout << "Player " << player_index + 1 << ", you are holding a ";
        cout << current_card.get_name() << ". Your move?";
        idx = INVALID;
        input_head_index = util.custom_cin(input_head_index, "");
        for (int j = 0; j < static_cast<int>(heads.size()); j++)
        {
            if (input_head_index == heads[j].get_head_index() || input_head_index == 0)
            {
                idx = j;
                break;
            }
        }
        if (idx == INVALID)
        {
            cout << "Invalid head position" << endl;
            continue;
        }
        input_head_index = input_head_index - 1;

        if (input_head_index == -1)
        {
            if (heads.size() > 1)
            {
                if (players[player_index].get_reserve().get_value() == INVALID)
                {
                    players[player_index].insert_reserve(current_card);
                    players[player_index].set_current_card(current_card);
                    return INVALID;
                }
                else
                {
                    players[player_index].swap_reserve(current_card);
                    continue;
                }

                players[player_index].set_current_card(current_card);
            }
            else
            {
                cout << "Your move is invalid, please play another move" << endl;
                players[player_index].insert_to_drawpile(current_card);
                continue;
            }
        }
        break;
    }

    return idx;
}
