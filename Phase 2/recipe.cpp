#include "recipe.hpp"
#include "rate.hpp"
#include "chef.hpp"

Recipe::Recipe(string _title_, vector <string> _ingredients_, bool _vegeterian_, int _minutes_to_ready_, 
               vector <string> _tags_, string _image_address_, shared_ptr<Chef> _origin_chef_, GoodEats* _goodeats_)
{
    title = _title_;
    ingredients = _ingredients_;
    vegeterian = _vegeterian_;
    minutes_to_ready = _minutes_to_ready_;
    tags = _tags_;
    image_address = _image_address_;
    recipe_ID++;
    recipe_id = recipe_ID;
    origin_chef = _origin_chef_;
    rating = 0;
    goodeats = _goodeats_;
}

Recipe::~Recipe()
{
	// ?1
}

bool Recipe::operator<(const Recipe &_recipe_) const
{
    return title < _recipe_.title;
}

void Recipe::show_info()
{
    cout << recipe_id << " " << title << " ";
    if (vegeterian)
    {
        cout << "Yes ";
    }
    else
    {
        cout << "No ";
    }
    cout << minutes_to_ready << endl;
}

void Recipe::show_info_with_rating()
{
    cout << recipe_id << " " << title << " ";
    if (vegeterian)
    {
        cout << "Yes ";
    }
    else
    {
        cout << "No ";
    }
    cout << minutes_to_ready << " " << fixed << setprecision(1) << round_up(rating) << endl;
}

void Recipe::show_detailed_info()
{
    cout << recipe_id << endl;
    cout << title << endl;
    cout << "vegetarian: ";
    if (vegeterian)
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
    cout << endl;
    cout << "ingredients: [";
    for (int i = 0; i<ingredients.size(); i++)
    {
        cout << ingredients[i];
        if (i != ingredients.size()-1)
        {
            cout << ", ";
        }
    }
    cout << "]" << endl;
    cout << "minutes to ready: " << minutes_to_ready << endl;
    cout << "tags: [";
    for (int i = 0; i<tags.size(); i++)
    {
        cout << tags[i];
        if (i != tags.size()-1)
        {
            cout << ", ";
        }
    }
    cout << "]" << endl;
    cout << "rating: " << fixed << setprecision(1) << round_up(rating) << endl;
}

shared_ptr<Rate> Recipe::find_rate(shared_ptr<User> _user_)
{
    for (int i = 0; i < rates.size(); i++)
    {
        if (rates[i]->get_owner() == _user_)
        {
            return rates[i];
        }
    }
    return nullptr;
}

void Recipe::add_rate(shared_ptr<User> _user_, int _score_)
{
    shared_ptr<Rate> _new_rate_ = make_shared<Rate>(_user_ , _score_, goodeats);
    rates.push_back(_new_rate_);
    update_rating(); 
}

void Recipe::update_rating()
{
    int rates_sum = 0;
    int rates_count = 0;
    int _score_;
    for (int i = 0; i < rates.size(); i++)
    {
        _score_ = rates[i]->get_rate();
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
    origin_chef->update_rating();
}

int Recipe::get_id()
{
    return recipe_id;
}

bool Recipe::has_same_id(int _recipe_id_)
{
    if (recipe_id == _recipe_id_)
    {
        return true;
    }
    return false;
}

double Recipe::get_rate()
{
    return rating;
}

string Recipe::get_title()
{
    return title;
}

vector<string> Recipe::get_ingredients()
{
    return ingredients;
}