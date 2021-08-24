#include "Card.h"

#include <string>
#include <iostream>
#include <vector>
#include <cstring>

#include "Utils.h"

using namespace std;

Card::Card(const string &card_name)
{
    joker = false;
    value = INVALID;
    set_name(card_name);
}

Card::Card()
{
    joker = false;
    value = INVALID;
    set_name("");
}

Card::~Card()
{
}

void Card::set_name(const string &new_name)
{
    this->name = new_name;

    if (new_name == "Joker")
    {
        joker = true;
        value = 2;
        return;
    }

    value = check_valid_name(new_name);
}

string Card::get_name() const
{
    return name;
}

int Card::get_value() const
{
    return value;
}

bool Card::get_is_joker() const
{
    return joker;
}

int Card::check_valid_name(string new_name)
{
    if (new_name.length() > 3)
    {
        value = INVALID;
        return value;
    }
    
    if (new_name[0] == 'A')
    {
        value = 1;
    }
    else if (new_name[0] == 'J')
    {
        value = 11;
    }
    else if (new_name[0] == 'Q')
    {
        value = 12;
    }
    else if (new_name[0] == 'K')
    {
        value = 13;
    }
    else if (new_name[0] >= '2' && new_name[0] <= '9')
    {
        value = stoi(new_name);
    }
    else if (new_name.find("10") != string::npos)
    {
        value = 10;
    }
    else
    {
        value = INVALID;
    }
    return value;
}
