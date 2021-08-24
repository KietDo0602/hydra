#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>

#include "Card.h"

using namespace std;

class Player
{
private:
    vector<Card> draw_pile;
    vector<Card> discard_pile;
    Card current_card;
    Card reserve;
    bool testing_mode;

    void shuffle();
    bool draw_pile_empty();
    bool discard_pile_empty();
    void discard_to_draw_pile();
    Card test_draw_card();
public:
    explicit Player(bool testing);
    ~Player();
    Card draw_card();
    void set_current_card(const Card &card);
    Card get_current_card();
    void reserve_to_drawpile();
    void cutoff_to_discard(vector<Card> head_cards);
    Card play_card();
    void insert_reserve(const Card &card);
    Card& get_reserve();
    Card swap_reserve(Card &card);
    bool is_won();
    void insert_to_drawpile(Card card);
    void insert_to_discardpile(Card card);
    
    void print_players();
    void print_current_players(int remain_turns);
};

#endif // __PLAYER_H__
