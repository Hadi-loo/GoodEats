#ifndef _GOODEATS_HPP_
#define _GOODEATS_HPP_

#include "test.hpp"
class GoodEats
{
public:
    GoodEats();
    ~GoodEats();
    void get_input();
    void get_input_type(string _input_);
    void get_POST_input();
    void get_GET_input();
    void get_DELETE_input();
    void get_PUT_input();
    bool username_exists(string _username_);
    bool email_exists(string _email_);
    void get_signup_info();
    void signup(string _username_, string _password_, string _type_);
    void signup_supplier(string _name_, string _email_, string _password_);
    void get_login_info();
    void log_in(string _username_, string _password_);
    void log_in_supplier(string _email_, string _password_);
    void logout();
    void show_recipes_info();
    shared_ptr<Recipe> find_recipe_by_id(int _recipe_id_);
    void show_recipe_info(int _recipe_id_);
    void get_rates_info(bool is_POSTed);
    void add_recipe_rate(int _recipe_id_, int _score_);
    void edit_recipe_rate(int _recipe_id_, int _score_);
    void rate_recipe(int _recipe_id_, int _score_, bool is_POSTed);
    void get_shelve_info();
    void add_shelve(string _name_);
    void show_shelves_of_user(string _user_name_, int _limit_);
    void get_shelves_recipes_info(bool is_PUTted);
    void add_recipe_to_shelve(int _shelve_id_, int _recipe_id_);
    shared_ptr<Shelve> find_shelve_by_id(int _shelve_id_);
    void show_recipes_in_shelve(int _shelve_id_);
    void delete_recipe_from_shelve(int _shelve_id_, int _recipe_id_);
    void show_chefs_info();
    shared_ptr<User> find_user_by_username(string _User_username_);
    shared_ptr<Chef> find_chef_by_username(string _chef_username_);
    shared_ptr<Supplier> find_supplier_by_email(string _email_);
    void show_chef_info(string _chef_username_);
    void show_users_info();
    void delete_recipe(int _recipe_id_);
    int find_index(int _recipe_id_);
    void get_recipe_info();
    void add_recipe(string _title_, vector <string> _ingredients_, bool _vegeterian_, int _minutes_to_ready_, 
           vector <string> _tags_, string _image_address_, shared_ptr<Chef> _origin_chef_, GoodEats* _goodeats_);
    void get_supp_signup_info();
    void get_offer_info(bool is_POSTed);
    void add_offer(string _ingredient_, double _price_, int _count_, double _packaging_);
    void edit_offer(string _ingredient_, double _price_, int _count_);
    void delete_offer(string _ingredient_);
    int find_offer_index(string _ingredient_);
    void add_order(int _recipe_id_);
    shared_ptr<Offer> find_offer(string _ingredient_);
    int get_count(string _ingredient_);

private:
    vector <shared_ptr<User>> users;
    vector <shared_ptr<Chef>> chefs;
    vector <shared_ptr<Supplier>> suppliers;
    vector <shared_ptr<Recipe>> recipes;
    vector <shared_ptr<Shelve>> shelves;
    vector <shared_ptr<Offer>> offers;
    bool cur_user_stat;
    bool cur_chef_stat;
    bool cur_supp_stat;
    shared_ptr<User> cur_user;
    shared_ptr<Chef> cur_chef;
    shared_ptr<Supplier> cur_supp;
};

#endif