#include "Player.h"
#include <algorithm>
#include <ctime>
#include <iostream>
#include <stdlib.h>

#include "Utils.h"

Player::Player(bool testing) 
{
    draw_pile.clear();
    discard_pile.clear();
    current_card.set_name("");
    reserve.set_name("");
    testing_mode = testing;
}

Player::~Player() 
{
    
}

Card Player::draw_card()
{
    if (draw_pile_empty() == true)
    {
        discard_to_draw_pile();
    }

    if (draw_pile_empty() == false)
    {
        if (testing_mode == true)
        {
            current_card = test_draw_card();
        }
        else
        {
            current_card = draw_pile.back();
        }
        draw_pile.pop_back();
    }

    return current_card;
}

Card Player::test_draw_card()
{
    string value;
    string suit;
    Card card;
    while (true)
    {
        value = util.custom_cin(value, "You are in testing mode, please type in a card value?");

        card.set_name(value);
        if (value == "Joker")
        {
            break;
        }
        else if (card.get_value() != INVALID)
        {
            suit = util.custom_cin(suit, "Please type in the suit? (S, H, C, D)");
            if (suit == "S" || suit == "H" || suit == "C" || suit == "D")
            {
                card.set_name(value + suit);
                break;
            }
            else
            {
                cout << "Invalid suit. Valid suits are S, H, C or D." << endl;
            }
        }
    }
    return card;
}

void Player::set_current_card(const Card &card) 
{
    current_card = card;
}

Card Player::get_current_card()
{
    return current_card;
}

void Player::reserve_to_drawpile() 
{
    if (reserve.get_name() != "")
    {
        draw_pile.push_back(reserve);
        reserve.set_name("");
    }
}

void Player::cutoff_to_discard(vector<Card> head_cards)
{
    for (int i = 0; i < static_cast<int>(head_cards.size()); i++)
    {
        discard_pile.push_back(head_cards[i]);
    }
}

void Player::shuffle()
{
    srand ( unsigned ( time(0) ) );
    random_shuffle (discard_pile.begin(), discard_pile.end());
}

Card Player::play_card()
{
    return get_current_card();
}

void Player::insert_reserve(const Card &card)
{
    if (reserve.get_name() == "")
    {
        reserve = card;
    }
}

Card& Player::get_reserve() 
{
    return reserve;
}

Card Player::swap_reserve(Card &card)
{
    if (testing_mode == true)
    {
        cout << "What card do you want in reserve?" << endl;
        reserve = test_draw_card();
    }
    Card temp = reserve;
    reserve = card;
    card = temp;

    return reserve;
}

bool Player::is_won()
{
    return (draw_pile_empty() && discard_pile_empty() && (reserve.get_value() == INVALID));
}

void Player::insert_to_drawpile(Card card)
{
    draw_pile.push_back(card);
}

void Player::insert_to_discardpile(Card card) 
{
    discard_pile.push_back(card);
}

bool Player::draw_pile_empty()
{
    return draw_pile.empty();
}

bool Player::discard_pile_empty()
{
    return discard_pile.empty();
}

void Player::discard_to_draw_pile()
{
    this->shuffle();
    draw_pile = discard_pile;
    discard_pile.clear();
}

void Player::print_players()
{
    cout << draw_pile.size() + discard_pile.size();
    cout << " (" << draw_pile.size() << " draw, ";
    cout << discard_pile.size() << " discard)" << endl;
}

void Player::print_current_players(int remain_turns)
{
    cout << draw_pile.size() + discard_pile.size();
    cout << " (" << draw_pile.size() << " draw, ";
    cout << discard_pile.size() << " discard)";
    cout << " + 1 in hand, " << remain_turns << " remaining, ";
    cout << ((reserve.get_value() == INVALID) ? 0 : 1) << " in reserve" << endl;
}

