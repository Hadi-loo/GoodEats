#ifndef _USER_HPP_
#define _USER_HPP_

#include "test.hpp"
class User
{
public:
    User(string _user_name_, string _password_, GoodEats* _goodeats_);
    ~User();
    void show_shelves(int _limit_);
    string get_shelves();
    bool has_shelve(int _shelve_id_);
    void show_info();
    string get_username();
    bool has_password(string _password_);
    void add_shelve(shared_ptr<Shelve> _new_shelve_);
    void increase_credit(double amount);
    void show_credit();
    bool can_pay(double _cost_);
    void add_order(shared_ptr<Order> _new_order_);
    void decrease_credit(double _cost_);
    void show_orders();
    int get_id();
private:
    string username;
    string password;
    vector <shared_ptr<Shelve>> shelves;
    vector <shared_ptr<Rate>> rates;
    GoodEats* goodeats;
    double credit;
    int id;
    vector <shared_ptr<Order>> orders;
};

#endif