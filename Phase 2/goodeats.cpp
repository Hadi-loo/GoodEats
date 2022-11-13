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

GoodEats::GoodEats()
{
    cur_user = nullptr;
    cur_user_stat = false;
    cur_chef = nullptr;
    cur_chef_stat = false;
    cur_supp = nullptr;
    cur_supp_stat = false;
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
        if ((cur_chef_stat) || (cur_user_stat) || (cur_supp_stat))
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
        if ((cur_chef_stat) || (cur_user_stat) || (cur_supp_stat))
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
        if ((cur_chef_stat) || (cur_user_stat) || (cur_supp_stat))
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
    else if (input == "signup_supplier")
    {
        if ((cur_supp_stat) || (cur_user_stat) || (cur_chef_stat))
        {
            throw PermissionDenied();
        }
        else
        {
            cin >> input;
            if (input == "?")
            {
                get_supp_signup_info();
            }
            else
            {
                throw BadRequest();
            }
        }
    }
    else if (input == "offers")
    {
        if (cur_supp_stat)
        {
            cin >> input;
            if (input == "?")
            {   
                get_offer_info(true);
            }
            else
            {
                throw BadRequest();
            }
        }
        else
        {
            throw PermissionDenied();
        }
    }
    else if (input == "orders")
    {
        if (cur_user_stat)
        {
            cin >> input;
            if (input == "?")
            {
                cin >> input;
                if (input == "recipe_id")
                {
                    int _recipe_id_;
                    if (cin >> _recipe_id_)
                    {
                        add_order(_recipe_id_);
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
    else if (input == "credits")
    {
        if (cur_user_stat)
        {
            cur_user->show_credit();
        }
        else if (cur_supp_stat)
        {
            cur_supp->show_credit();
        }
        else
        {
            throw PermissionDenied();
        }
    }
    else if (input == "orders")
    {
        if (cur_user_stat)
        {
            cur_user->show_orders();
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
    else if (input == "offers")
    {
        if (cur_supp_stat)
        {
            cin >> input;
            if (input == "?")
            {
                cin >> input;
                if (input == "ingredient")
                {
                    string _ingredient_;
                    cin >> _ingredient_;
                    if ((cur_supp->find_offer(_ingredient_)) == nullptr)
                    {
                        throw BadRequest();
                    }
                    else
                    {
                        delete_offer(_ingredient_);
                        cur_supp->delete_offer(_ingredient_);
                        show_message("OK");
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
    else if (input == "credits")
    {
        if (cur_user_stat)
        {
            cin >> input;
            if (input == "?")
            {
                cin >> input;
                if (input == "money")
                {
                    double _amount_;
                    if (cin >> _amount_)
                    {
                        cur_user->increase_credit(_amount_);
                        show_message("OK");
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
            throw PermissionDenied();
        }
    }
    else if (input == "offers")
    {
        if (cur_supp_stat)
        {
            cin >> input;
            if (input == "?")
            {
                get_offer_info(false);
            }
            else
            {
                throw BadRequest();
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
    for (auto x : suppliers)
    {
        if (x->get_name() == _username_)
        {
            return true;
        }
    }
    return false;
}

bool GoodEats::email_exists(string _email_)
{
    for (auto x : suppliers)
    {
        if (x->get_email() == _email_)
        {
            return true;
        }
    }
    return false;
}

void GoodEats::get_signup_info()
{
    if ((cur_user_stat) || (cur_chef_stat) || (cur_supp_stat))
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

void GoodEats::get_supp_signup_info()
{
    string input;
    cin >> input;
    if (input == "name")
    {
        string _name_;
        cin >> _name_;
        if (username_exists(_name_))  
        {
            throw BadRequest();
        }
        else
        {
            cin >> input;
            if (input == "email")
            {
                string _email_;
                cin >> _email_;
                if (email_exists(_email_)) 
                {
                    throw BadRequest();
                }
                else
                {
                    cin >> input;
                    if (input == "password")
                    {
                        string _password_;
                        cin >> _password_;
                        signup_supplier(_name_, _email_, _password_);
                    }
                    else
                    {
                        throw BadRequest();
                    }
                }
            }
            else
            {
                throw BadRequest();
            }
        }
    }
    else
    {
        throw BadRequest();
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

void GoodEats::signup_supplier(string _name_, string _email_, string _password_)
{
    cur_supp = make_shared<Supplier>(_name_, _email_, _password_, this);
    cur_supp_stat = true;
    suppliers.push_back(cur_supp);
    show_message("OK");
}

void GoodEats::get_login_info()
{
    if ((cur_user_stat) || (cur_chef_stat) || (cur_supp_stat))
    {
        throw PermissionDenied();
    }
    else
    {
        string input;
        cin >> input;
        if (input == "username")
        {
            string _username_;
            cin >> _username_;
            cin >> input;
            if (input == "password")
            {
                string _password_;
                cin >> _password_;
                log_in(_username_, _password_);
            }
            else
            {
                throw BadRequest();
            }
        }
        else if (input == "email")
        {   
            string _email_;
            cin >> _email_;
            cin >> input;
            if (input == "password")
            {
                string _password_;
                cin >> _password_;
                log_in_supplier(_email_, _password_);
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
        if (_chef_->has_password(_password_))
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

void GoodEats::log_in_supplier(string _email_, string _password_)
{
    shared_ptr<Supplier> _supplier_ = find_supplier_by_email(_email_);
    if (_supplier_ == nullptr)
    {
        throw NotFound();
    }
    else
    {
        if (_supplier_->has_password(_password_))
        {
            cur_supp = _supplier_;
            cur_supp_stat = true;
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
    else if (cur_supp_stat)
    {
        cur_supp_stat = false;
        cur_supp = nullptr;
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

shared_ptr<Supplier> GoodEats::find_supplier_by_email(string _email_)
{
    for (auto x : suppliers)
    {
        if (x->get_email() == _email_)
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

void GoodEats::get_offer_info(bool is_POSTed)
{
    string input;
    cin >> input;
    if (input == "ingredient")
    {
        string _ingredient_;
        cin >> _ingredient_;
        cin >> input;
        if (input == "price")
        {
            double _price_;
            if (cin >> _price_)
            {
                cin >> input;
                if (input == "count")
                {
                    int _count_;
                    if (cin >> _count_)
                    {
                        if (is_POSTed)
                        {
                            cin >> input;
                            if (input == "packaging")
                            {
                                double _packaging_;
                                if (cin >> _packaging_)
                                {
                                    add_offer(_ingredient_, _price_, _count_, _packaging_);
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
                            edit_offer(_ingredient_, _price_, _count_);
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

void GoodEats::add_offer(string _ingredient_, double _price_, int _count_, double _packaging_)
{
    if (cur_supp->find_offer(_ingredient_) == nullptr)
    {
        shared_ptr<Offer> _new_offer_ = make_shared<Offer>(_ingredient_, _price_, _packaging_, _count_, cur_supp);
        offers.push_back(_new_offer_);
        cur_supp->add_offer(_new_offer_);
        show_message("OK");
    }
    else
    {
        throw BadRequest();
    }
}


void GoodEats::edit_offer(string _ingredient_, double _price_, int _count_)
{
    shared_ptr<Offer> _the_offer_ = cur_supp->find_offer(_ingredient_);
    if (_the_offer_ == nullptr)
    {
        throw BadRequest();
    }
    else
    {
        _the_offer_->edit_price(_price_, _count_);
        show_message("OK");
    }
}

void GoodEats::delete_offer(string _ingredient_)
{
    int index = find_offer_index(_ingredient_);
    if (index != -1)
    {
        auto it = next(offers.begin(), index);
        offers.erase(it);
    }
    else
    {
        throw NotFound();
    }
}

int GoodEats::find_offer_index(string _ingredient_)
{
    for (int i = 0;i<offers.size();i++)
    {
        if (offers[i]->get_ingredient() == _ingredient_)
        {
            return i;
        }
    }
    return -1;
}

void GoodEats::add_order(int _recipe_id_)
{
    shared_ptr<Recipe> _recipe_ = find_recipe_by_id(_recipe_id_);
    if (_recipe_ == nullptr)
    {
        throw NotFound();
    }
    else
    {
        vector<string> _ingredients_ = _recipe_->get_ingredients();
        vector<shared_ptr<Offer>> offers_;
        for (string _ingredient_ : _ingredients_)
        {
            shared_ptr<Offer> _new_offer_ = find_offer(_ingredient_);
            if (_new_offer_ == nullptr)
            {
                throw NotFound();
            }
            else
            {
                offers_.push_back(_new_offer_);
            }
        }

        vector<vector<shared_ptr<Offer>>> _offers_;
        vector<shared_ptr<Offer>> sample;
        _offers_.push_back(sample);
        _offers_[0].push_back(offers_[0]);
        bool supplier_existed;
        for (int i = 1; i < offers_.size(); i++)
        {
            supplier_existed = false;
            for (int j = 0; j < _offers_.size(); j++)
            {
                if (offers_[i]->get_supplier() == _offers_[j][0]->get_supplier())
                {
                    _offers_[j].push_back(offers_[i]);
                    supplier_existed = true;
                    break;
                }
            }
            if (!(supplier_existed))
            {
                _offers_.push_back(sample);
                _offers_[_offers_.size() - 1].push_back(offers_[i]);
            }
        }

        double total_price = 0;
        for (int i = 0; i < _offers_.size(); i++)
        {   
            vector<shared_ptr<Offer>> _sorted_offers_ = sort_offers(_offers_[i]);
            _offers_[i] = _sorted_offers_;
        }
        vector<vector<shared_ptr<Offer>>> _sorted_suppliers_ = sort_suppliers(_offers_);
        _offers_ = _sorted_suppliers_;

        for (int i = 0; i < _offers_.size(); i++)
        {
            for (int j = 0; j < _offers_[i].size(); j++)
            {
                if (get_count(_offers_[i][j]->get_ingredient()) >= 20)
                {
                    total_price += (_offers_[i][j]->get_price()) * 0.9;
                }
                else
                {
                    total_price += (_offers_[i][j]->get_price());
                }          
            }
        }
        if (cur_user->can_pay(total_price))
        {
            stringstream ss;
            double this_supplier_price;
            for (int i = 0; i < _offers_.size(); i++)
            {
                this_supplier_price = 0;
                ss << _offers_[i][0]->get_supplier()->get_name() << " ";
                for (int j = 0; j < _offers_[i].size(); j++)
                {
                    ss << _offers_[i][j]->get_ingredient();
                    if (get_count(_offers_[i][j]->get_ingredient()) >= 20)
                    {
                        this_supplier_price += (_offers_[i][j]->get_price()) * 0.9;
                    }
                    else
                    {
                        this_supplier_price += (_offers_[i][j]->get_price());
                    }
                    _offers_[i][j]->decrease_balance();
                    if (j != (_offers_[i].size() - 1))
                    {
                        ss << " ";
                    }
                    else
                    {
                        ss << endl;
                    }
                }
                _offers_[i][0]->get_supplier()->increase_credit(this_supplier_price);
            }
            shared_ptr<Order> _new_order_ = make_shared<Order>(_recipe_id_ ,total_price, ss.str());
            cur_user->add_order(_new_order_);
            cur_user->decrease_credit(total_price);
            _new_order_->show_info_without_id();
        }
        else
        {
            throw BadRequest();
        }
    }
}

shared_ptr<Offer> GoodEats::find_offer(string _ingredient_)
{
    shared_ptr<Offer> _the_offer_ = nullptr;
    bool is_first = true;
    double lowest_price;
    for (auto x : offers)
    {
        if (x->get_ingredient() == _ingredient_)
        {
            if (x->has_balance())
            {
                if (is_first)
                {
                    _the_offer_ = x;
                    is_first = false;
                    lowest_price = x->get_price();
                }
                else
                {
                    if (x->get_price() < lowest_price)
                    {
                        _the_offer_ = x;
                        lowest_price = x->get_price();
                    }
                }
            }
        }
    }
    return _the_offer_;
}

int GoodEats::get_count(string _ingredient_)
{
    int _count_ = 0;
    for (auto x : offers)
    {
        if (x->get_ingredient() == _ingredient_)
        {
            _count_ += x->get_count();
        }
    }
    return _count_;
}