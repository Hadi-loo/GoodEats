#include "supplier.hpp"
#include "offer.hpp"
#include "exceptions.hpp"

Supplier::Supplier(string _name_, string _email_, string _password_, GoodEats* _goodeats_)
{
    name = _name_;
    email = _email_;
    password = _password_;
    goodeats = _goodeats_;
    credit = 0;
}
Supplier::~Supplier()
{

}
string Supplier::get_name()
{
    return name;
}
string Supplier::get_email()
{
    return email;
}

bool Supplier::has_password(string _password_)
{
    if (password == _password_)
    {
        return true;
    }
    return false;
}

shared_ptr<Offer> Supplier::find_offer(string _ingredient_)
{
    for (auto x : offers)
    {
        if (x->get_ingredient() == _ingredient_)
        {
            return x;
        }
    }
    return nullptr;
}

void Supplier::add_offer(shared_ptr<Offer> _new_offer_)
{
    offers.push_back(_new_offer_);
}

void Supplier::delete_offer(string _ingredient_)
{
    int index = find_offer_index(_ingredient_);
    if (index != -1)
    {
        auto it = next(offers.begin(), index);
        offers.erase(it);
    }
    else
    {
        throw NotFound();
    }
}

int Supplier::find_offer_index(string _ingredient_)
{
    for (int i = 0;i<offers.size();i++)
    {
        if (offers[i]->get_ingredient() == _ingredient_)
        {
            return i;
        }
    }
    return -1;
}

void Supplier::increase_credit(double _cost_)
{
    credit += _cost_;
}

void Supplier::show_credit()
{
    cout << credit << endl;
}