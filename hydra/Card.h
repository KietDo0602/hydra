#ifndef __CARD_H__
#define __CARD_H__

#include <string>

using namespace std;

class Card
{
private:
    string name;
    int value;
    bool joker;

    int check_valid_name(string new_name);

public:
    explicit Card(const string &card_name);
    Card();
    ~Card();

    void set_name(const string &new_name);
    string get_name() const;
    int get_value() const;
    bool get_is_joker() const;
};

#endif // __CARD_H__
