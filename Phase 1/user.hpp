#ifndef _USER_HPP_
#define _USER_HPP_

#include "test.hpp"
class User
{
public:
    User(string _user_name_, string _password_, GoodEats* _goodeats_);
    ~User();
    void show_shelves(int _limit_);
    bool has_shelve(int _shelve_id_);
    void show_info();
    string get_username();
    bool has_password(string _password_);
    void add_shelve(shared_ptr<Shelve> _new_shelve_);

private:
    string username;
    string password;
    vector <shared_ptr<Shelve>> shelves;
    vector <shared_ptr<Rate>> rates;
    GoodEats* goodeats;
};

#endif