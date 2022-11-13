#include "user.hpp"
#include "shelf.hpp"
#include "order.hpp"

User::User(string _user_name_, string _password_, GoodEats* _goodeats_)
{
    username = _user_name_;
    password = _password_;
    goodeats = _goodeats_;
    user_ID++;
    id =  user_ID;
    credit = 0;
}

User::~User()
{
	// ?!
}

string User::get_shelves()
{
    if (shelves.size() != 0)
    {
        stringstream ss;
        for (int i = 0; i < shelves.size(); i++)
        {
            ss << shelves[i]->get_info() << "<br />" << "------------" << "<br />";
        }
        return ss.str();
    }
    else
    {
        return "Empty";
    }
}

void User::show_shelves(int _limit_)
{
    if (_limit_ > shelves.size())
    {
        _limit_ = shelves.size();
    }
    if (_limit_ != 0)
    {
        for (int i = 0; i < _limit_; i++)
        {
            shelves[i]->show_info(); 
        }
    }
    else
    {
        show_message("Empty");
    }
}

bool User::has_shelve(int _shelve_id_)
{
    for (int i = 0; i < shelves.size(); i++)
    {
        if (shelves[i]->get_id() == _shelve_id_)
        {
            return true;
        }
    }
    return false;
}

void User::show_info()
{
    cout << username << endl;
}

string User::get_username()
{
    return username;
}

bool User::has_password(string _password_)
{
    if (password == _password_)
    {
        return true;
    }
    return false;
}

void User::add_shelve(shared_ptr<Shelve> _new_shelve_)
{
    shelves.push_back(_new_shelve_);
}

void User::increase_credit(double amount)
{
    credit += amount;
}

void User::show_credit()
{
    cout << credit << endl;
}

bool User::can_pay(double _cost_)
{
    if (credit >= _cost_)
    {
        return true;
    }
    return false;
}

void User::add_order(shared_ptr<Order> _new_order_)
{
    orders.push_back(_new_order_);
}

void User::decrease_credit(double _cost_)
{
    credit -= _cost_;
}

void User::show_orders()
{
    for (int i = 0; i < orders.size(); i++)
    {
        cout << "====order" << i+1 << "====" << endl;
        orders[i]->show_info();
    }
}

int User::get_id()
{
    return id;
}