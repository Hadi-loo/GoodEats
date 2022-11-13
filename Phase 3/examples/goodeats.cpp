#include "goodeats.hpp"
#include "exceptions.hpp"
#include "chef.hpp"
#include "user.hpp"
#include "recipe.hpp"
#include "rate.hpp"
#include "shelf.hpp"
#include "supplier.hpp"
#include "offer.hpp"
#include "order.hpp"
#include "../server/server.hpp"

GoodEats::GoodEats()
{
    // ?!
}
GoodEats::~GoodEats()
{
	// ?!
}

bool GoodEats::username_exists(string _username_)
{
    for (auto x : users)
    {
        if (x->get_username() == _username_)
        {
            return true;
        }
    }
    for (auto x : chefs)
    {
        if (x->get_username() == _username_)
        {
            return true;
        }
    }
    return false;
}

int GoodEats::get_signup_info(string _username_, string _password_, string _type_)
{
    if (username_exists(_username_))
    {
        throw BadRequest("username exists.");
        //throw Server::Exception("Bad Request. username exists.");
    }
    else
    {
        return signup(_username_, _password_, _type_);
    }
}

int GoodEats::signup(string _username_, string _password_, string _type_)
{
    if (_type_ == "user")
    {
        shared_ptr<User> _user_ = make_shared<User>(_username_, _password_, this);
        users.push_back(_user_);
        return _user_->get_id(); // complete
    }
    else if (_type_ == "chef")
    {
        shared_ptr<Chef> _chef_ = make_shared<Chef>(_username_, _password_, this);
        chefs.push_back(_chef_);
        return _chef_->get_id(); // complete
    }
}

string GoodEats::get_recipes_info()
{
    vector <shared_ptr<Recipe>> sorted_recipes = sort_recipes(recipes);
    if (recipes.size() == 0)
    {
        return "Empty";
    }
    else
    {
        stringstream ss;
        for (auto x : sorted_recipes)
        {
            ss << x->get_info() << "<br />" << "------------" << "<br />";
        }
        return ss.str();
    }
}

shared_ptr<Recipe> GoodEats::find_recipe_by_id(int _recipe_id_)
{
    for(auto x : recipes)
    {
        if (x->has_same_id(_recipe_id_))
        {
            return x;
        }
    }
    return nullptr;
}

void GoodEats::add_recipe_rate(int _recipe_id_, int _score_, shared_ptr<User> _user_)
{
    shared_ptr<Recipe> _recipe_ = find_recipe_by_id(_recipe_id_);
    if (_recipe_ != nullptr)
    {
        shared_ptr<Rate> _rate_ = _recipe_->find_rate(_user_);
        if (_rate_ == nullptr)
        {
            _recipe_->add_rate(_user_, _score_);
            show_message("OK");
        }
        else
        {
            throw BadRequest();
        }
    }
    else
    {
        throw NotFound();
    }
}

void GoodEats::edit_recipe_rate(int _recipe_id_, int _score_, shared_ptr<User> _user_)
{
    shared_ptr<Recipe> _recipe_ = find_recipe_by_id(_recipe_id_);
    if (_recipe_ != nullptr)
    {
        shared_ptr<Rate> _rate_ = _recipe_->find_rate(_user_);
        if (_rate_ != nullptr)
        {
            _rate_->edit_rate(_score_);
            _recipe_->update_rating();
            show_message("OK");
        }
        else
        {
            throw BadRequest();
        }
    }
    else
    {
        throw NotFound();
    }
}

void GoodEats::rate_recipe(int _recipe_id_, int _score_, shared_ptr<User> _user_)
{
    shared_ptr<Recipe> _recipe_ = find_recipe_by_id(_recipe_id_);
    if (_recipe_ != nullptr)
    {
        shared_ptr<Rate> _rate_ = _recipe_->find_rate(_user_);
        if (_rate_ == nullptr)
        {
            add_recipe_rate(_recipe_id_, _score_, _user_);
        }
        else if (_rate_ != nullptr)
        {
            edit_recipe_rate(_recipe_id_, _score_, _user_);
        }
        else
        {
            throw BadRequest();
        }
    }
    else
    {
        throw NotFound();
    }
}

void GoodEats::add_shelve(string _name_, shared_ptr<User> _user_)
{
    shared_ptr<Shelve> _new_shelve_ = make_shared<Shelve>(_name_, _user_, this);
    shelves.push_back(_new_shelve_);
    _user_->add_shelve(_new_shelve_);
}

void GoodEats::add_recipe_to_shelve(int _shelve_id_, int _recipe_id_, shared_ptr<User> _user_)
{
    if (_user_->has_shelve(_shelve_id_))
    {   
        shared_ptr<Shelve> _shelve_ = find_shelve_by_id(_shelve_id_);
        shared_ptr<Recipe> _recipe_ = find_recipe_by_id(_recipe_id_);
        if (_recipe_ != nullptr)
        {
            if (_shelve_->has_recipe(_recipe_id_))
            {
                throw BadRequest();
            }
            else
            {
                _shelve_->add_recipe(_recipe_);
            }
        }
        else
        {
            throw NotFound();
        }
    }
    else
    {
        throw PermissionDenied();
    }
}


shared_ptr<Shelve> GoodEats::find_shelve_by_id(int _shelve_id_)
{
    for (int i = 0; i<shelves.size();i++)
    {
        if (shelves[i]->get_id() == _shelve_id_)
        {
            return shelves[i];
        }
    }
    return nullptr;
}

void GoodEats::delete_recipe_from_shelve(int _shelve_id_, int _recipe_id_, shared_ptr<User> _user_)
{
    if (_user_->has_shelve(_shelve_id_))
    {   
        shared_ptr<Shelve> _shelve_ = find_shelve_by_id(_shelve_id_);
        shared_ptr<Recipe> _recipe_ = find_recipe_by_id(_recipe_id_);
        if (_recipe_ != nullptr)
        {
            if (_shelve_->has_recipe(_recipe_id_))
            {
                _shelve_->delete_recipe(_recipe_id_);
            }
            else
            {
                throw BadRequest();
            }
        }
        else
        {
            throw NotFound();
        }
    }
    else
    {
        throw PermissionDenied();
    }
}

shared_ptr<User> GoodEats::find_user_by_username(string _User_username_)
{
    for (auto x : users)
    {
        if (x->get_username() == _User_username_)
        {
            return x;
        }
    }
    return nullptr;
}

shared_ptr<Chef> GoodEats::find_chef_by_username(string _chef_username_)
{
    for(auto x : chefs)
    {
        if (x->has_same_username(_chef_username_))
        {
            return x;
        }
    }
    return nullptr;
}

shared_ptr<User> GoodEats::find_user_by_id(int _user_id_)
{
    for (auto x : users)
    {
        if (x->get_id() == _user_id_)
        {
            return x;
        }
    }
    return nullptr;
}

shared_ptr<Chef> GoodEats::find_chef_by_id(int _chef_id_)
{
    for (auto x : chefs)
    {
        if (x->get_id() == _chef_id_)
        {
            return x;
        }
    }
    return nullptr;
}

void GoodEats::delete_recipe(string _Chef_ID_, string _Recipe_ID_)
{
    int _chef_id_ = stoi(_Chef_ID_);
    int _recipe_id_ = stoi(_Recipe_ID_);
    shared_ptr<Chef> cur_chef = find_chef_by_id(_chef_id_);
    if (cur_chef->has_recipe(_recipe_id_))
    {
        cur_chef->delete_recipe(_recipe_id_);
        int index = find_index(_recipe_id_);
        if (index != -1)
        {
            auto it = next(recipes.begin(), index);
            recipes.erase(it);
            show_message("OK");
        }
        else
        {
            throw NotFound();
        }
    }
    else
    {
        throw PermissionDenied();
    }
}

int GoodEats::find_index(int _recipe_id_)
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

void GoodEats::add_recipe(string _title_, string _IngredientS_, string _VegeteriaN_, string _Minutes_to_readY_, 
           string _TagS_, string _image_address_, string _Chef_ID_ , GoodEats* _goodeats_)
{
    vector <string> _ingredients_;
    vector<string> _tags_;
    bool _vegetarian_;
    int _minutes_to_ready_ = stoi(_Minutes_to_readY_);
    if (_VegeteriaN_ == "Yes")
    {
        _vegetarian_ = true;
    }
    else if (_VegeteriaN_ == "No")
    {
        _vegetarian_ = false;
    }
    int _chef_id_ = stoi(_Chef_ID_);
    shared_ptr<Chef> _origin_chef_ = _goodeats_->find_chef_by_id(_chef_id_);
    string delimiter = ",";
    size_t pos = 0;
    size_t _pos_ = 0;
    string token;
    string _token_;
    while ((pos = _IngredientS_.find(delimiter)) != std::string::npos) 
    {
        token = _IngredientS_.substr(0, pos);
        _ingredients_.push_back(token);
        _IngredientS_.erase(0, pos + delimiter.length());
    }
    _ingredients_.push_back(_IngredientS_);
    while ((_pos_ = _TagS_.find(delimiter)) != std::string::npos) 
    {
        _token_ = _TagS_.substr(0, _pos_);
        _tags_.push_back(_token_);
        _TagS_.erase(0, _pos_ + delimiter.length());
    }
    _tags_.push_back(_TagS_);

    shared_ptr<Recipe> _new_recipe_ = make_shared<Recipe>(_title_, _ingredients_, _vegetarian_, _minutes_to_ready_, _tags_, _image_address_, _origin_chef_, _goodeats_);
    recipes.push_back(_new_recipe_);
    _origin_chef_->add_recipe(_new_recipe_);
}