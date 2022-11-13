#ifndef _SUPPLIER_HPP_
#define _SUPPLIER_HPP_

#include "test.hpp"
class Supplier
{
public:
    Supplier(string _name_, string _email_, string _password_, GoodEats* _goodeats_);
    ~Supplier();
    string get_name();
    string get_email();
    bool has_password(string _password_);
    shared_ptr<Offer> find_offer(string _ingredient_);
    void add_offer(shared_ptr<Offer> _new_offer_);
    void delete_offer(string _ingredient_);
    int find_offer_index(string _ingredient_);
    void increase_credit(double _cost_);
    void show_credit();
private:
    string name;
    string email;
    string password;
    GoodEats* goodeats;
    double credit;
    vector<shared_ptr<Offer>> offers;
};

#endif