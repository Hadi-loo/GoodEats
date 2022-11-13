#ifndef _RATE_HPP_
#define _RATE_HPP_

#include "test.hpp"
class Rate
{
public:
	Rate(shared_ptr<User> _user_, int _score_, GoodEats* _goodeats_);
	~Rate();
    shared_ptr<User> get_owner();
    void edit_rate(int _score_);
    int get_rate();

private:
    int rate;
    shared_ptr<User> rater;
 	GoodEats* goodeats;
};

#endif