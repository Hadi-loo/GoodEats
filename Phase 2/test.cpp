#include "test.hpp"
#include "goodeats.hpp"
#include "chef.hpp"
#include "user.hpp"
#include "recipe.hpp"
#include "supplier.hpp"
#include "offer.hpp"

int recipe_ID = 0;
int shelve_ID = 0;

void show_message(string content)
{
    cout << content << endl;
}
double round_up (double _num_)
{
    double num = ceil(_num_*10);
    return (num/10.0);
}
bool compare_chefs(shared_ptr<Chef> aptr, shared_ptr<Chef> bptr)
{
	return ((aptr->get_username()) < (bptr->get_username()));
}
vector<shared_ptr<Chef>> sort_chefs(vector<shared_ptr<Chef>> _chefs_)
{
    sort(_chefs_.begin(), _chefs_.end(), compare_chefs);
    return _chefs_;
}

bool compare_recipes(shared_ptr<Recipe> aptr, shared_ptr<Recipe> bptr)
{
	return ((aptr->get_title()) < (bptr->get_title()));
}
vector<shared_ptr<Recipe>> sort_recipes(vector<shared_ptr<Recipe>> _recipes_)
{
    sort(_recipes_.begin(), _recipes_.end(), compare_recipes);
    return _recipes_;
}

bool compare_users(shared_ptr<User> aptr, shared_ptr<User> bptr)
{
	return ((aptr->get_username()) < (bptr->get_username()));
}
vector<shared_ptr<User>> sort_users(vector<shared_ptr<User>> _users_)
{
    sort(_users_.begin(), _users_.end(), compare_users);
    return _users_;
}

bool compare_offers(shared_ptr<Offer> aptr, shared_ptr<Offer> bptr)
{
    return ((aptr->get_ingredient()) < (bptr->get_ingredient()));
}

vector<shared_ptr<Offer>> sort_offers(vector<shared_ptr<Offer>> _offers_)
{
    sort(_offers_.begin(), _offers_.end(), compare_offers);
    return _offers_;
}

bool compare_suppliers(vector<shared_ptr<Offer>> aptr, vector<shared_ptr<Offer>> bptr)
{
    return ((aptr[0]->get_supplier()->get_name()) < (bptr[0]->get_supplier()->get_name()));
}

vector<vector<shared_ptr<Offer>>> sort_suppliers(vector<vector<shared_ptr<Offer>>> _suppliers_)
{
    sort(_suppliers_.begin(), _suppliers_.end(), compare_suppliers);
    return _suppliers_;
}

int main()
{
    GoodEats goodeats = GoodEats();
    goodeats.get_input();
    return 0;
}