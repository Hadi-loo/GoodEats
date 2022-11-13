#ifndef _SHELF_HPP_
#define _SHELF_HPP_

#include "test.hpp"
class Shelve
{
public:
	Shelve(string _name_,shared_ptr<User> _cur_user_, GoodEats* _goodeats_);
	~Shelve();
    string get_info();
    void show_info();
    int get_id();
    void add_recipe(shared_ptr<Recipe> _recipe_);
    void show_recipes();
    void delete_recipe(int _recipe_id_);
    int find_index(int _recipe_id_);
    bool has_recipe(int _recipe_id_);
    string get_detailed_info();
private:
    string name;
    int shelve_id;
    shared_ptr<User> origin_user;
    vector <shared_ptr<Recipe>> recipes;
    GoodEats* goodeats;
};

#endif