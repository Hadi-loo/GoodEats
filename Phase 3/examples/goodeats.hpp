#ifndef _GOODEATS_HPP_
#define _GOODEATS_HPP_

#include "test.hpp"
class GoodEats
{
public:
    GoodEats();
    ~GoodEats();
    bool username_exists(string _username_);
    int get_signup_info(string _username_, string _password_, string _type_);
    int signup(string _username_, string _password_, string _type_);
    void log_in(string _username_, string _password_);
    void logout();
    string get_recipes_info();
    shared_ptr<Recipe> find_recipe_by_id(int _recipe_id_);
    void add_recipe_rate(int _recipe_id_, int _score_, shared_ptr<User> _user_);
    void edit_recipe_rate(int _recipe_id_, int _score_, shared_ptr<User> _user_);
    void rate_recipe(int _recipe_id_, int _score_, bool is_POSTed);
    void rate_recipe(int _recipe_id_, int _score_, shared_ptr<User> _user_);
    void get_shelve_info();
    void add_shelve(string _name_, shared_ptr<User> _user_);
    void show_shelves_of_user(string _user_name_, int _limit_);
    void get_shelves_recipes_info(bool is_PUTted);
    void add_recipe_to_shelve(int _shelve_id_, int _recipe_id_, shared_ptr<User> _user_);
    shared_ptr<Shelve> find_shelve_by_id(int _shelve_id_);
    void delete_recipe_from_shelve(int _shelve_id_, int _recipe_id_, shared_ptr<User> _user_);
    shared_ptr<User> find_user_by_username(string _User_username_);
    shared_ptr<Chef> find_chef_by_username(string _chef_username_);
    shared_ptr<User> find_user_by_id(int _user_id_);
    shared_ptr<Chef> find_chef_by_id(int _chef_id_);
    void delete_recipe(int _recipe_id_);
    void delete_recipe(string _Chef_ID_, string _Recipe_ID_);
    int find_index(int _recipe_id_);
    void get_recipe_info();
    void add_recipe(string _title_, string _ingredients_, string _vegeterian_, string _minutes_to_ready_, 
           string _tags_, string _image_address_, string _chef_id_, GoodEats* _goodeats_);

private:
    vector <shared_ptr<User>> users;
    vector <shared_ptr<Chef>> chefs;
    vector <shared_ptr<Recipe>> recipes;
    vector <shared_ptr<Shelve>> shelves;
};

#endif