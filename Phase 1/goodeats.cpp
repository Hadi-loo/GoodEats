#include "goodeats.hpp"
#include "exceptions.hpp"
#include "chef.hpp"
#include "user.hpp"
#include "recipe.hpp"
#include "rate.hpp"
#include "shelf.hpp"

GoodEats::GoodEats()
{
    cur_user = nullptr;
    cur_user_stat = false;
    cur_chef = nullptr;
    cur_chef_stat = false;
}
GoodEats::~GoodEats()
{
	// ?!
}
void GoodEats::get_input()
{
    string _input_;
    string _buffer_;
    while (cin >> _input_)
    {
        try
        {
            get_input_type(_input_);
        }
        catch (NotFound& _exception_)
        {
            string _error_ = _exception_.get_description();
            cout << _error_ << endl;
            getline(cin, _buffer_);
        }
        catch (BadRequest& _exception_)
        {
            string _error_ = _exception_.get_description();
            cout << _error_ << endl;
            getline(cin, _buffer_);
        }
        catch (PermissionDenied& _exception_)
        {
            string _error_ = _exception_.get_description();
            cout << _error_ << endl;
            getline(cin, _buffer_);
        }
    }
}

void GoodEats::get_input_type(string input)
{
    if (input == "POST")
    {
        get_POST_input();
    }
    else if (input == "GET")
    {
        get_GET_input();
    }
    else if (input == "DELETE")
    {
        get_DELETE_input();
    }
    else if (input == "PUT")
    {
        get_PUT_input();
    }
    else
    {
        throw BadRequest();
    }  
}

void GoodEats::get_POST_input()
{
    string input;
    cin >> input;
    if (input == "signup")
    {
        if ((cur_chef_stat) || (cur_user_stat))
        {
            throw PermissionDenied();
        }
        else
        {
            cin >> input;
            if (input == "?")
            {
                get_signup_info();
            }
            else
            {
                throw NotFound();
            }
        }
    }
    else if (input == "login")
    {
        if ((cur_chef_stat) || (cur_user_stat))
        {
            throw PermissionDenied();
        }
        else
        {
            cin >> input;
            if (input == "?")
            {
                get_login_info();
            }
            else
            {
                throw NotFound();
            }
        }
    }
    else if (input == "logout")
    {
        if ((cur_chef_stat) || (cur_user_stat))
        {
            logout();
        }
        else
        {
            throw PermissionDenied();
        }
    }

    else if (input == "rates")
    {
        if (cur_user_stat)
        {
            cin >> input;
            if (input == "?")
            {
                get_rates_info(true);
            }
        }
        else
        {
            throw PermissionDenied();
        }
    }
    else if (input == "shelves")
    {
        if (cur_user_stat)
        {
            cin >> input;
            if (input == "?")
            {
                get_shelve_info();
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
    else if (input == "recipes")
    {
        if (cur_chef_stat)
        {
            cin >> input;
            if (input == "?")
            {
                get_recipe_info();
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
    else
    {
        throw NotFound();
    }
}

void GoodEats::get_GET_input()
{
    string input;
    cin >> input;
    if (input == "recipes")
    {
        if (cur_user_stat)
        {
            if (cin.peek() == '\n')
            {
                show_recipes_info();
            }
            else
            {
                cin >> input;
                if (input == "?")
                {
                    cin >> input;
                    if (input == "id")
                    {   
                        int _recipe_id_;
                        if (cin >> _recipe_id_)
                        {
                            show_recipe_info(_recipe_id_);
                        }
                        else
                        {
                            throw NotFound();
                        }
                    }
                    else
                    {
                        throw NotFound();
                    }
                }   
            }
        }
        else
        {
            throw PermissionDenied();
        }   
    }

    else if (input == "shelves")
    {
        if (cur_user_stat)
        {
            cin >> input;
            if (input == "?")
            {
                cin >> input;
                if (input == "username")
                {
                    string _user_name_;
                    cin >> _user_name_;
                    cin >> input;
                    if (input == "limit")
                    {
                        int _limit_;
                        if (cin >> _limit_)
                        {
                            if (_limit_ > 0)
                            {
                                show_shelves_of_user(_user_name_, _limit_);
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
                        throw NotFound();
                    }

                }
                else
                {
                    throw NotFound();
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
    else if (input == "shelves_recipes")
    {
        if (cur_user_stat)
        {
            cin >> input;
            if (input == "?")
            {
                cin >> input;
                if (input == "shelf_id")
                {
                    int _shelve_id_;
                    if (cin >> _shelve_id_)
                    {
                        show_recipes_in_shelve(_shelve_id_);
                    }
                    else
                    {
                        throw NotFound();
                    }
                }
                else
                {
                    throw NotFound();
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
    else if (input == "chefs")
    {
        if (cur_user_stat)
        {
            if (cin.peek() == '\n')
            {
                show_chefs_info();
            }
            else
            {
                cin >> input;
                if (input == "?")
                {
                    cin >> input;
                    if (input == "chef_username")
                    {   
                        string _chef_username_;
                        cin >> _chef_username_;
                        show_chef_info(_chef_username_);
                    }
                    else
                    {
                        throw NotFound();
                    }
                }
                else
                {
                    throw NotFound();
                }
            }
        }
        else
        {
            throw PermissionDenied();
        }
    }
    else if (input == "users")
    {
        if (cur_user_stat)
        {
            show_users_info();
        }
        else
        {
            throw PermissionDenied();
        }
    }
    else if (input == "my_recipes")
    {
        if (cur_chef_stat)
        {
            cur_chef->show_recipes_info();
        }
        else
        {
            throw PermissionDenied();
        }
    }
    else
    {
        throw NotFound();
    }
}

void GoodEats::get_DELETE_input()
{
    string input;
    cin >> input;
    if (input == "shelves_recipes")
    {
        if (cur_user_stat)
        {
            cin >> input;
            if (input == "?")
            {
                get_shelves_recipes_info(false);
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
    else if (input == "recipes")
    {
        if (cur_chef_stat)
        {
            cin >> input;
            if (input == "?")
            {
                cin >> input;
                if (input == "id")
                {
                    int _recipe_id_;
                    if (cin >> _recipe_id_)
                    {
                        delete_recipe(_recipe_id_);
                    }
                    else
                    {
                        throw NotFound();
                    }
                }
                else
                {
                    throw NotFound();
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
    else
    {
        throw NotFound();
    }
}

void GoodEats::get_PUT_input()
{
    string input;
    cin >> input;
    if (input == "rates")
    {
        if (cur_user_stat)
        {
            cin >> input;
            if (input == "?")
            {
                get_rates_info(false);
            }
        }
        else
        {
            throw PermissionDenied();
        }
    }
    else if (input == "shelves_recipes")
    {
        if (cur_user_stat)
        {
            cin >> input;
            if (input == "?")
            {
                get_shelves_recipes_info(true);
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
    else
    {
        throw NotFound();
    }
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

void GoodEats::get_signup_info()
{
    if (cur_user_stat || cur_chef_stat)
    {
        throw PermissionDenied();
    }
    else
    {
        string input;
        cin >> input;
        if (input == "username")
        {
            string username;
            cin >> username;
            if (username_exists(username))
            {
                throw BadRequest();
            }
            else
            {
                cin >> input;
                if (input == "password")
                {
                    string password;
                    cin >> password;
                    cin >> input;
                    if (input == "type")
                    {
                        string type;
                        cin >> type;
                        if ((type == "user") || (type == "chef"))
                        {
                            signup(username, password, type);
                        }
                        else
                        {
                            throw NotFound();
                        }
                    }
                    else
                    {
                        throw NotFound();
                    }
                }
                else
                {
                    throw NotFound();
                }
            }
        }
        else
        {
            throw NotFound();
        }
    }
}

void GoodEats::signup(string _username_, string _password_, string _type_)
{
    if (_type_ == "user")
    {
        cur_user = make_shared<User>(_username_, _password_, this);
        cur_user_stat = true;
        users.push_back(cur_user);
    }
    else if (_type_ == "chef")
    {
        cur_chef = make_shared<Chef>(_username_, _password_, this);
        cur_chef_stat = true;
        chefs.push_back(cur_chef);
    }
    show_message("OK"); 
}

void GoodEats::get_login_info()
{
    if (cur_user_stat || cur_chef_stat)
    {
        throw PermissionDenied();
    }
    else
    {
        string input;
        cin >> input;
        if (input == "username")
        {
            string username;
            cin >> input;
            if (input == "password")
            {
                string password;
                cin >> password;
                log_in(username, password);
                // possible error ?!
            }
            else
            {
                throw NotFound();
            }
        }
        else
        {
           throw NotFound();
        }
    }
}

void GoodEats::log_in(string _username_, string _password_)
{
    shared_ptr<User> _user_ = find_user_by_username(_username_);
    shared_ptr<Chef> _chef_ = find_chef_by_username(_username_);
    if ((_user_ == nullptr) && (_chef_ == nullptr))
    {
        throw NotFound();
    }
    else if (_user_ != nullptr)
    {
        if (_user_->has_password(_password_))
        {
            cur_user = _user_;
            cur_user_stat = true;
            show_message("OK");
        }
        else
        {
            throw BadRequest();
        }
    }
    else if (_chef_ != nullptr)
    {
        if (_chef_->has_password(_username_))
        {
            cur_chef = _chef_;
            cur_chef_stat = true;
            show_message("OK");
        }
        else
        {
            throw BadRequest();
        }
    }
}

void GoodEats::logout()
{
    if (cur_user_stat)
    {   
        cur_user_stat = false;
        cur_user = nullptr;
        show_message("OK");
    }
    else if (cur_chef_stat)
    {
        cur_chef_stat = false;
        cur_chef = nullptr;
        show_message("OK");
    }
    else
    {
        throw PermissionDenied();
    }
}

void GoodEats::show_recipes_info()
{
    vector <shared_ptr<Recipe>> sorted_recipes = sort_recipes(recipes);
    if (recipes.size() == 0)
    {
        show_message("Empty");
    }
    else
    {
        for (auto x : sorted_recipes)
        {
            x->show_info();
        }
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

void GoodEats::show_recipe_info(int _recipe_id_)
{
    shared_ptr<Recipe> _recipe_ = find_recipe_by_id(_recipe_id_);
    if (_recipe_ == nullptr)
    {
        throw NotFound();
    }
    else
    {
        _recipe_->show_detailed_info();
    }
}

void GoodEats::get_rates_info(bool is_POSTed)
{
    string input;
    cin >> input;
    if (input == "recipe_id")
    {
        int _recipe_id_;
        if (cin >> _recipe_id_)
        {
            cin >> input;
            if (input == "score")
            {
                int _score_;
                if (cin >> _score_)
                {
                    if ((_score_ >= 1) && (_score_ <= 5))
                    {
                        rate_recipe(_recipe_id_, _score_, is_POSTed);
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
                throw NotFound();
            }
        }
        else
        {
            throw NotFound();
        }
    }
    else
    {
        throw NotFound();
    }
}

void GoodEats::add_recipe_rate(int _recipe_id_, int _score_)
{
    shared_ptr<Recipe> _recipe_ = find_recipe_by_id(_recipe_id_);
    if (_recipe_ != nullptr)
    {
        shared_ptr<Rate> _rate_ = _recipe_->find_rate(cur_user);
        if (_rate_ == nullptr)
        {
            _recipe_->add_rate(cur_user, _score_);
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

void GoodEats::edit_recipe_rate(int _recipe_id_, int _score_)
{
    shared_ptr<Recipe> _recipe_ = find_recipe_by_id(_recipe_id_);
    if (_recipe_ != nullptr)
    {
        shared_ptr<Rate> _rate_ = _recipe_->find_rate(cur_user);
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

void GoodEats::rate_recipe(int _recipe_id_, int _score_, bool is_POSTed)
{
    shared_ptr<Recipe> _recipe_ = find_recipe_by_id(_recipe_id_);
    if (_recipe_ != nullptr)
    {
        shared_ptr<Rate> _rate_ = _recipe_->find_rate(cur_user);
        if ((_rate_ == nullptr) && (is_POSTed))
        {
            add_recipe_rate(_recipe_id_, _score_);
        }
        else if ((_rate_ != nullptr) && (!(is_POSTed)))
        {
            edit_recipe_rate(_recipe_id_, _score_);
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

void GoodEats::get_shelve_info()
{
    string input;
    cin >> input;
    if (input == "name")
    {
        cin >> input;
        add_shelve(input);
    }
    else
    {
        throw NotFound();
    }
}

void GoodEats::add_shelve(string _name_)
{
    shared_ptr<Shelve> _new_shelve_ = make_shared<Shelve>(_name_, cur_user, this);
    shelves.push_back(_new_shelve_);
    cur_user->add_shelve(_new_shelve_);
    show_message(to_string(shelve_ID));
}

void GoodEats::show_shelves_of_user(string _user_name_, int _limit_)
{
    shared_ptr<User> _user_ = find_user_by_username(_user_name_);
    if (_user_ != nullptr)
    {
        _user_->show_shelves(_limit_);
    }
    else
    {
        throw NotFound();
    }
}

void GoodEats::get_shelves_recipes_info(bool is_PUTted)
{
    string input;
    int _shelve_id_;
    int _recipe_id_;
    cin >> input;
    if (input == "shelf_id")
    {
        if (cin >> _shelve_id_)
        {
            cin >> input;
            if (input == "recipe_id")
            {
                if (cin >> _recipe_id_)
                {
                    if (is_PUTted)
                    {
                        add_recipe_to_shelve(_shelve_id_, _recipe_id_);
                    }
                    else
                    {
                        delete_recipe_from_shelve(_shelve_id_, _recipe_id_);
                    }
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
            throw NotFound();
        }
    }
    else
    {
        throw NotFound();
    }
}

void GoodEats::add_recipe_to_shelve(int _shelve_id_, int _recipe_id_)
{
    if (cur_user->has_shelve(_shelve_id_))
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
                show_message("OK");
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

void GoodEats::show_recipes_in_shelve(int _shelve_id_)
{
    shared_ptr<Shelve> _shelve_ = find_shelve_by_id(_shelve_id_);
    if (_shelve_ != nullptr)
    {
        _shelve_->show_recipes();
    }
    else
    {
        throw NotFound();
    }
}

void GoodEats::delete_recipe_from_shelve(int _shelve_id_, int _recipe_id_)
{
    if (cur_user->has_shelve(_shelve_id_))
    {   
        shared_ptr<Shelve> _shelve_ = find_shelve_by_id(_shelve_id_);
        shared_ptr<Recipe> _recipe_ = find_recipe_by_id(_recipe_id_);
        if (_recipe_ != nullptr)
        {
            if (_shelve_->has_recipe(_recipe_id_))
            {
                _shelve_->delete_recipe(_recipe_id_);
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
    else
    {
        throw PermissionDenied();
    }
}

void GoodEats::show_chefs_info()
{
    vector <shared_ptr<Chef>> sorted_chefs = sort_chefs(chefs);
    if (chefs.size() == 0)
    {
        cout << "Empty" << endl;
    }
    else
    {
        for (auto x : sorted_chefs)
        {
            x->show_info();
        }
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

void GoodEats::show_chef_info(string _chef_username_)
{
    shared_ptr<Chef> _chef_ = find_chef_by_username(_chef_username_);
    if (_chef_ != nullptr)
    {
        _chef_->show_detailed_info();
    }
    else
    {
        throw NotFound();
    }
}

void GoodEats::show_users_info()
{
    if (users.size() == 0)
    {
        cout << "Empty" << endl;
    }
    else
    {
        vector<shared_ptr<User>> sorted_users = sort_users(users);
        for (auto x : sorted_users)
        {
            x->show_info();
        }
    }
}

void GoodEats::delete_recipe(int _recipe_id_)
{
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

void GoodEats::get_recipe_info()
{
    string input;
    cin >> input;
    if (input == "title")
    {
        string _title_;
        cin >> _title_;
        cin >> input;
        if (input == "ingredients")
        {
            vector <string> _ingredients_;
            string _IngredentS_;
            cin >> _IngredentS_;
            string delimiter = ",";
            size_t pos = 0;
            string token;
            while ((pos = _IngredentS_.find(delimiter)) != std::string::npos) 
            {
                token = _IngredentS_.substr(0, pos);
                _ingredients_.push_back(token);
                _IngredentS_.erase(0, pos + delimiter.length());
            }
            _ingredients_.push_back(_IngredentS_);
            cin >> input;
            if (input == "vegetarian")
            {
                string _vegeterian_;
                bool is_vegeterian_;
                cin >> _vegeterian_;
                if ((_vegeterian_ == "Yes") || (_vegeterian_ == "No"))
                {
                    if (_vegeterian_ == "Yes")
                    {
                        is_vegeterian_ = true;
                    }
                    else
                    {
                        is_vegeterian_ = false;
                    }
                    cin >> input;
                    if (input == "minutes_to_ready")
                    {
                        int _minutes_to_ready_;
                        if(cin >> _minutes_to_ready_)
                        {
                            cin >> input;
                            if (input == "tags")
                            {
                                string _TagS_;
                                cin >> _TagS_;
                                string _token_;
                                vector<string> _tags_;
                                size_t _pos_ = 0;
                                while ((_pos_ = _TagS_.find(delimiter)) != std::string::npos) 
                                {
                                    _token_ = _TagS_.substr(0, _pos_);
                                    _tags_.push_back(_token_);
                                    _TagS_.erase(0, _pos_ + delimiter.length());
                                }
                                _tags_.push_back(_TagS_);
                                cin >> input;
                                if (input == "image_address")
                                {   
                                    string _image_address_;
                                    cin >> _image_address_;
                                    add_recipe(_title_, _ingredients_, is_vegeterian_, _minutes_to_ready_, _tags_, _image_address_, cur_chef, this);
                                    show_message(to_string(recipe_ID));
                                }
                                else
                                {
                                   throw BadRequest();
                                }
                            }
                            else
                            {
                                throw BadRequest();
                            }
                        }
                        else
                        {
                            throw BadRequest();
                        }
                    }
                    else
                    {
                        throw BadRequest();
                    }
                }
                else
                {
                    throw BadRequest();
                }
            }
            else
            {
                throw BadRequest();
            }
        }
        else
        {
            throw BadRequest();
        }
    }
    else
    {
        throw BadRequest();
    }
}

void GoodEats::add_recipe(string _title_, vector <string> _ingredients_, bool _vegeterian_, int _minutes_to_ready_, 
           vector <string> _tags_, string _image_address_, shared_ptr<Chef> _origin_chef_, GoodEats* _goodeats_)
{
    shared_ptr<Recipe> _new_recipe_ = make_shared<Recipe>(_title_, _ingredients_, _vegeterian_, _minutes_to_ready_, _tags_, _image_address_, _origin_chef_, _goodeats_);
    recipes.push_back(_new_recipe_);
    _origin_chef_->add_recipe(_new_recipe_);
}