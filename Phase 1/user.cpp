#include "user.hpp"
#include "shelf.hpp"

User::User(string _user_name_, string _password_, GoodEats* _goodeats_)
{
    username = _user_name_;
    password = _password_;
    goodeats = _goodeats_;
}

User::~User()
{
	// ?!
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