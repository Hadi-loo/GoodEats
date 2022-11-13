#ifndef _TEST_HPP_
#define _TEST_HPP_

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>
#include <memory>
#include <algorithm>
#include <iomanip>
using namespace std;
extern int recipe_ID;
extern int shelve_ID;

class GoodEats;
class User;
class Chef;
class Shelve;
class Recipe;
class Rate;

void show_message(string content);
double round_up (double _num_);
bool compare_chefs(shared_ptr<Chef> aptr, shared_ptr<Chef> bptr);
vector<shared_ptr<Chef>> sort_chefs(vector<shared_ptr<Chef>> _chefs_);
bool compare_recipes(shared_ptr<Recipe> aptr, shared_ptr<Recipe> bptr);
vector<shared_ptr<Recipe>> sort_recipes(vector<shared_ptr<Recipe>> _recipes_);
bool compare_users(shared_ptr<User> aptr, shared_ptr<User> bptr);
vector<shared_ptr<User>> sort_users(vector<shared_ptr<User>> _users_);

#endif