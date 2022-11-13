#include "shelf.hpp"
#include "recipe.hpp"
#include "exceptions.hpp"

Shelve::Shelve(string _name_,shared_ptr<User> _cur_user_, GoodEats* _goodeats_)
{
    name = _name_;
    shelve_ID++;
    shelve_id = shelve_ID;
    origin_user = _cur_user_;
    goodeats = _goodeats_;
}

Shelve::~Shelve()
{

}

void Shelve::show_info()
{
    cout << shelve_id << " ";
    cout << name << endl;
}

int Shelve::get_id()
{
    return shelve_id;
}

void Shelve::add_recipe(shared_ptr<Recipe> _recipe_)
{
    recipes.push_back(_recipe_);
}

void Shelve::show_recipes()
{
    vector<shared_ptr<Recipe>> sorted_recipes = sort_recipes(recipes);
    for (int i = 0;i<sorted_recipes.size();i++)
    {
        sorted_recipes[i]->show_info();
    }
    if (sorted_recipes.size() == 0)
    {
        cout << "Empty" << endl;
    }
}

void Shelve::delete_recipe(int _recipe_id_)
{
    int index = find_index(_recipe_id_);
    if (index != -1)
    {
        auto it = next(recipes.begin() , index);
        recipes.erase(it);
        cout << "OK" << endl;
    }
    else
    {
        throw NotFound();
    }
}

int Shelve::find_index(int _recipe_id_)
{
    for (int i = 0;i<recipes.size();i++)
    {
        if (recipes[i]->get_id() == _recipe_id_)
        {
            return i;
        }
    }
    return -1;
}

bool Shelve::has_recipe(int _recipe_id_)
{
    for (int i =0; i<recipes.size();i++)
    {
        if (recipes[i]->get_id() == _recipe_id_)
        {
            return true;
        }
    }
    return false;
}