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
class Supplier;
class Offer;
class Order;

void show_message(string content);
double round_up (double _num_);
bool compare_chefs(shared_ptr<Chef> aptr, shared_ptr<Chef> bptr);
vector<shared_ptr<Chef>> sort_chefs(vector<shared_ptr<Chef>> _chefs_);
bool compare_recipes(shared_ptr<Recipe> aptr, shared_ptr<Recipe> bptr);
vector<shared_ptr<Recipe>> sort_recipes(vector<shared_ptr<Recipe>> _recipes_);
bool compare_users(shared_ptr<User> aptr, shared_ptr<User> bptr);
vector<shared_ptr<User>> sort_users(vector<shared_ptr<User>> _users_);
bool compare_offers(shared_ptr<Offer> aptr, shared_ptr<Offer> bptr);
vector<shared_ptr<Offer>> sort_offers(vector<shared_ptr<Offer>> _offers_);
bool compare_suppliers(vector<shared_ptr<Offer>> aptr, vector<shared_ptr<Offer>> bptr);
vector<vector<shared_ptr<Offer>>> sort_suppliers(vector<vector<shared_ptr<Offer>>> _suppliers_);

#endif