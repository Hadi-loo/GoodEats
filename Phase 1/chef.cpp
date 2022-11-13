#include "chef.hpp"
#include "recipe.hpp"

Chef::Chef(string _user_name_, string _password_, GoodEats* _goodeats_)
{
    username = _user_name_;
    password = _password_;
    goodeats = _goodeats_;
    rating = 0;
}
Chef::~Chef()
{

}

bool Chef::has_same_username(string _username_)
{
    if (_username_ == username)
    {
        return true;
    }
    return false;
}

void Chef::show_info()
{
    cout << username << " " << fixed << setprecision(1) << round_up(rating) << endl;
}

void Chef::show_detailed_info()
{
    cout << username << endl;
    cout << fixed << setprecision(1) << round_up(rating) << endl;
    cout << "recipes:" << endl;
    vector<shared_ptr<Recipe>> sorted_recipes = sort_recipes(recipes);
    for (auto x : sorted_recipes)
    {
        x->show_info_with_rating();
    }
}

bool Chef::has_recipe(int _recipe_id_)
{
    for (auto x : recipes)
    {
        if (x->get_id() == _recipe_id_)
        {
            return true;
        }
    }
    return false;
}

void Chef::show_recipes_info()
{
    if (recipes.size() == 0)
    {
        cout << "Empty" << endl;
    }
    else
    {
        vector<shared_ptr<Recipe>> sorted_recipes = sort_recipes(recipes); 
        for (int i = 0;i<sorted_recipes.size();i++)
        {
            sorted_recipes[i]->show_detailed_info();
            cout << endl;
        }
    }
}

string Chef::get_username()
{
    return username;
}

bool Chef::has_password(string _password_)
{
    if (password == _password_)
    {
        return true;
    }
    return false;
}

void Chef::add_recipe(shared_ptr<Recipe> _new_recipe_)
{
    recipes.push_back(_new_recipe_);
}

void Chef::delete_recipe(int _recipe_id_)
{
    int index;
    for (int i =0; i < recipes.size(); i++)
    {
        if (recipes[i]->get_id() == _recipe_id_)
        {
            index = i;
            break;
        }
    }
    auto it = next(recipes.begin() , index);
    recipes.erase(it);
}
void Chef::update_rating()
{
    double rates_sum = 0;
    int rates_count = 0;
    double _score_;
    for (int i = 0; i < recipes.size(); i++)
    {
        _score_ = recipes[i]->get_rate();
        if (_score_ != 0)
        {
            rates_sum += _score_;
            rates_count++;
        }
    }
    if (rates_count == 0)
    {
        rating = 0;
    }
    else
    {
        rating = ((double)rates_sum)/((double)rates_count);
    }
}