#include "order.hpp"

Order::Order(int _recipe_id_, double _total_price_, string _detail_)
{
    recipe_id = _recipe_id_;
    total_price = _total_price_;
    detail = _detail_;
}

Order::~Order()
{

}

void Order::show_info()
{
    cout << recipe_id << endl;
    cout << detail << endl;
    cout << (int)total_price << endl;
}

void Order::show_info_without_id()
{
    cout << detail << endl;
    cout << (int)total_price << endl;
}