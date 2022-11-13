#include "rate.hpp"

Rate::Rate(shared_ptr<User> _user_, int _score_, GoodEats* _goodeats_)
{
    rate = _score_;
    rater = _user_;
    goodeats = _goodeats_;
}

Rate::~Rate()
{

}

shared_ptr<User> Rate::get_owner()
{
    return rater;
}

void Rate::edit_rate(int _score_)
{
    rate = _score_;
}

int Rate::get_rate()
{
    return rate;
}