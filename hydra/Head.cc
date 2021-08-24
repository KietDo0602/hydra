#include "Head.h"

#include <iostream>

using namespace std;

Head::Head(Card card, int head_index)
{
    pile.push_back(card);
    this->head_index = head_index;
}

Head::~Head()
{
}

Card Head::get_top()
{
    return pile.back();
}

void Head::add_card(Card card)
{
    pile.push_back(card);
}

vector<Card> Head::cut_off()
{
    return pile;
}

int Head::get_head_index()
{
    return head_index;
}

void Head::print_head()
{
    cout << head_index << ": ";
    if (get_top().get_is_joker() == true)
    {
        int value = get_top().get_value();
        switch (value)
        {
            case 1:
                cout << "AJ";
                break;
            case 11:
                cout << "JJ";
                break;
            case 12:
                cout << "QJ";
                break;
            case 13:
                cout << "KJ";
                break;
            default:
                cout << value << "J";
                break;
        }
    }
    else
    {
        cout << get_top().get_name();
    }
    cout << " (" << pile.size() << ")" << endl;
}

