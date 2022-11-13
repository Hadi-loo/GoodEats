#ifndef _ORDER_HPP_
#define _ORDER_HPP_

#include "test.hpp"
class Order
{
public:
    Order(int _recipe_id_, double _total_price_, string _detail_);
    ~Order();
    void show_info();
    void show_info_without_id();
private:
    int recipe_id;
    string detail;
    double total_price;
};

#endif