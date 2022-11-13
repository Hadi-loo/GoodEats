#ifndef _CHEF_HPP_
#define _CHEF_HPP_

#include "test.hpp"
class Chef
{
public:
    Chef(string _user_name_, string _password_, GoodEats* _goodeats_);
    ~Chef();
    bool has_same_username(string _username_);
    void show_info();
    void show_detailed_info();
    bool has_recipe(int _recipe_id_);
    void show_recipes_info();
    string get_username();
    bool has_password(string _password_);
    void add_recipe(shared_ptr<Recipe> _new_recipe_);
    void delete_recipe(int _recipe_id_);
    void update_rating();
private:
    string username;
    string password;
    double rating;
    vector <shared_ptr<Recipe>> recipes;
    GoodEats* goodeats;
};

#endif