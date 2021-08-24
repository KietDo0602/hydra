#ifndef __HEAD_H__
#define __HEAD_H__

#include <vector>
#include "Card.h"

using namespace std;

class Head
{
private:
    vector<Card> pile;
    int head_index;

public:
    explicit Head(Card card, int head_index = 1);
    ~Head();

    Card get_top();
    void add_card(Card card);
    vector<Card> cut_off();
    int get_head_index();
    void print_head();
};

#endif // __HEAD_H__
