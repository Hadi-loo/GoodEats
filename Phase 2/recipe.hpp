#ifndef _RECIPE_HPP_
#define _RECIPE_HPP_

#include "test.hpp"
class Recipe
{
public:
	Recipe(string _title_, vector <string> _ingredients_, bool _vegeterian_, int _minutes_to_ready_, 
           vector <string> _tags_, string _image_address_, shared_ptr<Chef> _origin_chef_, GoodEats* _goodeats_);
	~Recipe();
    bool operator<(const Recipe &_recipe_) const;
    void show_info();
    void show_info_with_rating();
    void show_detailed_info();
    shared_ptr<Rate> find_rate(shared_ptr<User> _user_);
    void add_rate(shared_ptr<User> _user_, int _score_);
    void update_rating();
    int get_id();
    bool has_same_id(int _recipe_id_);
    double get_rate();
    string get_title();
    vector<string> get_ingredients();
private:
    string title;
    vector <string> ingredients;
    bool vegeterian;
    int minutes_to_ready;
    vector <string> tags;
    string image_address;
    int recipe_id;
    shared_ptr<Chef> origin_chef;
    vector <shared_ptr<Rate>> rates;
    double rating;
    GoodEats* goodeats;
};

#endif