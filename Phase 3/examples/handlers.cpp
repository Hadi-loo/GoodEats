#include "handlers.hpp"
#include "goodeats.hpp"
#include "user.hpp"
#include "chef.hpp"
#include "recipe.hpp"
#include "shelf.hpp"
#include <sstream>

using namespace std;


SignupHandler::SignupHandler(GoodEats* _goodeats_)
{
  goodeats = _goodeats_;
}

Response* SignupHandler::callback(Request *req) {
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  string type = req->getBodyParam("user_type");
  int _session_id_ = goodeats->get_signup_info(username, password, type);
  string __session_id__ = req->getSessionId(); 
  if (type == "user")
  {
    Response *res = Response::redirect("/UserHomePage"); 
    res->setSessionId(to_string(_session_id_)); 
    return res;
  }
  else if (type == "chef")
  {
    Response *res = Response::redirect("/ChefHomePage"); 
    res->setSessionId(to_string(_session_id_)); 
    return res;
  }
}

LoginHandler::LoginHandler(GoodEats* _goodeats_)
{
  goodeats = _goodeats_;
}

Response* LoginHandler::callback(Request *req) {
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  shared_ptr<User> _user_ = goodeats->find_user_by_username(username);
  if (_user_ == nullptr)
  {
    shared_ptr<Chef> _chef_ = goodeats->find_chef_by_username(username);
    if (_chef_ == nullptr)
    {
      throw Server::Exception("Bad Request. username not found."); // complete
    }
    else
    {
      if (_chef_->has_password(password))
      {
        Response *res = Response::redirect("/ChefHomePage"); // complete
        res->setSessionId(to_string(_chef_->get_id())); // complete 
        return res;
      }
      else
      {
        throw Server::Exception("Bad Request. password incorrect."); // complete
      }
    }
  }
  else
  {
    if (_user_->has_password(password))
    {
      Response *res = Response::redirect("/UserHomePage"); // complete
      res->setSessionId(to_string(_user_->get_id())); // complete
      return res;
    }
    else
    {
      throw Server::Exception("Bad Request. password incorrect."); // complete
    }
  }
}

UserHomePage::UserHomePage(GoodEats* _goodeats_)
{
  goodeats = _goodeats_;
}

Response* UserHomePage::callback(Request* req)
{
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string _session_id_ = req->getSessionId();
  res->setSessionId(_session_id_);
  shared_ptr<User> _user_ = goodeats->find_user_by_id(stoi(_session_id_));
  stringstream ss;
  ss << "<!DOCTYPE html>";
  ss << "<html>";
  ss << "<body style=\"text-align: center;\">";
  ss << "<h1>Goodeats</h1>";
  ss << "<h2>";
  ss << "Recipes:"; 
  ss << "</h2>";
  ss << "<p>";
  ss << goodeats->get_recipes_info();
  ss << "</p>";
  ss << "<form action=\"/UserHomePage/Shelves\" method=\"get\">";
  ss << "<button type=\"submit\"> Manage Shelves </button>";
  ss << "</form>";
  ss << "<br />";
  ss << "<form action=\"/\" method=\"post\">";
  ss << "<button type=\"submit\"> Sign out </button>";
  ss << "</form>";
  ss << "</body>";
  ss << "</html>";
  res->setBody(ss.str());
  return res;
}

RecipeInfoHandler::RecipeInfoHandler(GoodEats* _goodeats_)
{
  goodeats = _goodeats_;
}

Response* RecipeInfoHandler::callback(Request* req)
{
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string _session_id_ = req->getSessionId();
  res->setSessionId(_session_id_);
  string _recipe_id_ = req->getQueryParam("id");
  shared_ptr<Recipe> _recipe_ = goodeats->find_recipe_by_id(stoi(_recipe_id_));
  stringstream ss;
  ss << "<!DOCTYPE html>";
  ss << "<html>";
  ss << "<body style=\"text-align: center;\">";
  ss << "<h1>Recipe Info</h1>";
  ss << "<p>";
  ss << _recipe_->get_detailed_info();
  ss << "</p>";
  ss << "<form action=\"/UserHomePage/RateRecipe\"";
  ss << "method=\"get\">";
  ss << "<button type=\"submit\" name=\"RecipeID\" value=\"";
  ss << _recipe_id_;
  ss << "\"> Rate Recipe </button>";
  ss << "</form>";
  ss << "<br />";
  ss << "<form action=\"/\" method=\"post\">";
  ss << "<button type=\"submit\"> Sign out </button>";
  ss << "</form>";
  ss << "</body>";
  ss << "</html>";
  res->setBody(ss.str());
  return res;
}

RateRecipe::RateRecipe(GoodEats* _goodeats_)
{
  goodeats = _goodeats_;
}

Response* RateRecipe::callback(Request* req)
{
  Response* res = new Response;
  res->setHeader("Content-Type", "text/html");
  string _session_id_ = req->getSessionId();
  res->setSessionId(_session_id_);
  string _recipe_id_ = req->getQueryParam("RecipeID");
  shared_ptr<Recipe> _recipe_ = goodeats->find_recipe_by_id(stoi(_recipe_id_));
  stringstream ss;
  ss << "<!DOCTYPE html>";
  ss << "<html>";
  ss << "<body style=\"text-align: center;\">";
  ss << "<h1>Rate Recipe</h1>";
  ss << "<form action=\"/UserHomePage/RateRecipe?RecipeID=";
  ss << _recipe_id_ << "\"";
  ss << "method=\"post\">";
  ss << "<input name=\"rate\" type=\"number\" placeholder=\"Score\" min=\"1\" max=\"5\" required />";
  ss << "<button type=\"submit\"> Confirm </button>";
  ss << "</form>";
  ss << "<br />";
  ss << "<form action=\"/\" method=\"post\">";
  ss << "<button type=\"submit\"> Sign out </button>";
  ss << "</form>";
  ss << "</body>";
  ss << "</html>";
  res->setBody(ss.str());
  return res;
}

RateRecipeHandler::RateRecipeHandler(GoodEats* _goodeats_)
{
  goodeats = _goodeats_;
}

Response* RateRecipeHandler::callback(Request* req)
{
  string _session_id_ = req->getSessionId();
  Response* res = Response::redirect("/UserHomePage");
  res->setSessionId(_session_id_);
  int _recipe_id_ = stoi(req->getQueryParam("RecipeID"));
  int _rate_ = stoi(req->getBodyParam("rate"));
  shared_ptr<User> _user_ = goodeats->find_user_by_id(stoi(_session_id_));
  goodeats->rate_recipe(_recipe_id_, _rate_, _user_);
  return res;
}

ShelvesHandler::ShelvesHandler(GoodEats* _goodeats_)
{
  goodeats = _goodeats_;
}

Response* ShelvesHandler::callback(Request* req)
{
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string _session_id_ = req->getSessionId();
  res->setSessionId(_session_id_);
  shared_ptr<User> _user_ = goodeats->find_user_by_id(stoi(_session_id_));
  stringstream ss;
  ss << "<!DOCTYPE html>";
  ss << "<html>";
  ss << "<body style=\"text-align: center;\">";
  ss << "<h1>GoodEats</h1>";
  ss << "<h2>";
  ss << "Your Shelves:"; 
  ss << "</h2>";
  ss << "<p>";
  ss << _user_->get_shelves();
  ss << "</p>";
  ss << "<form action=\"/UserHomePage/AddShelf\" method=\"get\">";
  ss << "<button type=\"submit\"> Add Shelf </button>";
  ss << "</form>";
  ss << "<br />";
  ss << "<form action=\"/\" method=\"post\">";
  ss << "<button type=\"submit\"> Sign out </button>";
  ss << "</form>";
  ss << "</body>";
  ss << "</html>";
  res->setBody(ss.str());
  return res;
}

AddShelfHandler::AddShelfHandler(GoodEats* _goodeats_)
{
  goodeats = _goodeats_;
}

Response* AddShelfHandler::callback(Request* req)
{
  string name = req->getBodyParam("name");
  string _session_id_ = req->getSessionId();
  shared_ptr<User> _user_ = goodeats->find_user_by_id(stoi(_session_id_));
  goodeats->add_shelve(name, _user_);
  Response* res = Response::redirect("/UserHomePage");
  res->setSessionId(_session_id_);
  return res;
}

ShelfInfoHandler::ShelfInfoHandler(GoodEats* _goodeats_)
{
  goodeats = _goodeats_;
}

Response* ShelfInfoHandler::callback(Request* req)
{
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string _session_id_ = req->getSessionId();
  res->setSessionId(_session_id_);
  string _shelf_id_ = req->getQueryParam("id");
  shared_ptr<Shelve> _shelf_ = goodeats->find_shelve_by_id(stoi(_shelf_id_));
  stringstream ss;
  ss << "<!DOCTYPE html>";
  ss << "<html>";
  ss << "<body style=\"text-align: center;\">";
  ss << "<h1>Shelf Info</h1>";
  ss << "<p>";
  ss << _shelf_->get_detailed_info();
  ss << "</p>";
  ss << "<form action=\"/UserHomePage/AddRecipe\"";
  ss << "method=\"get\">";
  ss << "<button type=\"submit\" name=\"ShelfID\" value=\"";
  ss << _shelf_id_;
  ss << "\"> Add Recipe to this Shelf </button>";
  ss << "</form>";
  ss << "<br />";
  ss << "<form action=\"/UserHomePage/RemoveRecipe\"";
  ss << "method=\"get\">";
  ss << "<button type=\"submit\" name=\"ShelfID\" value=\"";
  ss << _shelf_id_;
  ss << "\"> Remove Recipe from this Shelf </button>";
  ss << "</form>";
  ss << "<br />";
  ss << "<form action=\"/\" method=\"post\">";
  ss << "<button type=\"submit\"> Sign out </button>";
  ss << "</form>";
  ss << "</body>";
  ss << "</html>";
  res->setBody(ss.str());
  return res;
}


AddRecipetoShelf::AddRecipetoShelf(GoodEats* _goodeats_)
{
  goodeats = _goodeats_;
}

Response* AddRecipetoShelf::callback(Request* req)
{
  Response* res = new Response;
  res->setHeader("Content-Type", "text/html");
  string _session_id_ = req->getSessionId();
  res->setSessionId(_session_id_);
  string _shelf_id_ = req->getQueryParam("ShelfID");

  stringstream ss;
  ss << "<!DOCTYPE html>";
  ss << "<html>";
  ss << "<body style=\"text-align: center;\">";
  ss << "<h1>Add Recipe to Shelf</h1>";
  ss << "<form action=\"/UserHomePage/AddRecipe?ShelfID=";
  ss << _shelf_id_ << "\"";
  ss << "method=\"post\">";
  ss << "<input name=\"recipe_id\" type=\"number\" placeholder=\"Recipe ID\" min=\"1\" required />";
  ss << "<button type=\"submit\"> Confirm </button>";
  ss << "</form>";
  ss << "<br />";
  ss << "<form action=\"/\" method=\"post\">";
  ss << "<button type=\"submit\"> Sign out </button>";
  ss << "</form>";
  ss << "</body>";
  ss << "</html>";
  res->setBody(ss.str());
  return res;
}

AddRecipetoShelfHandler::AddRecipetoShelfHandler(GoodEats* _goodeats_)
{
  goodeats = _goodeats_;
}

Response* AddRecipetoShelfHandler::callback(Request* req)
{
  string _session_id_ = req->getSessionId();
  Response* res = Response::redirect("/UserHomePage");
  res->setSessionId(_session_id_);
  int _shelf_id_ = stoi(req->getQueryParam("ShelfID"));
  int _recipe_id_ = stoi(req->getBodyParam("recipe_id"));
  shared_ptr<User> _user_ = goodeats->find_user_by_id(stoi(_session_id_));
  goodeats->add_recipe_to_shelve(_shelf_id_, _recipe_id_, _user_);
  return res;
}

RemoveRecipefromShelf::RemoveRecipefromShelf(GoodEats* _goodeats_)
{
  goodeats = _goodeats_;
}

Response* RemoveRecipefromShelf::callback(Request* req)
{
  Response* res = new Response;
  res->setHeader("Content-Type", "text/html");
  string _session_id_ = req->getSessionId();
  res->setSessionId(_session_id_);
  string _shelf_id_ = req->getQueryParam("ShelfID");

  stringstream ss;
  ss << "<!DOCTYPE html>";
  ss << "<html>";
  ss << "<body style=\"text-align: center;\">";
  ss << "<h1>Remove Recipe from Shelf</h1>";
  ss << "<form action=\"/UserHomePage/RemoveRecipe?ShelfID=";
  ss << _shelf_id_ << "\"";
  ss << "method=\"post\">";
  ss << "<input name=\"recipe_id\" type=\"number\" placeholder=\"Recipe ID\" min=\"1\" required />";
  ss << "<button type=\"submit\"> Confirm </button>";
  ss << "</form>";
  ss << "<br />";
  ss << "<form action=\"/\" method=\"post\">";
  ss << "<button type=\"submit\"> Sign out </button>";
  ss << "</form>";
  ss << "</body>";
  ss << "</html>";
  res->setBody(ss.str());
  return res;
}

RemoveRecipefromShelfHandler::RemoveRecipefromShelfHandler(GoodEats* _goodeats_)
{
  goodeats = _goodeats_;
}

Response* RemoveRecipefromShelfHandler::callback(Request* req)
{
  string _session_id_ = req->getSessionId();
  Response* res = Response::redirect("/UserHomePage");
  res->setSessionId(_session_id_);
  int _shelf_id_ = stoi(req->getQueryParam("ShelfID"));
  int _recipe_id_ = stoi(req->getBodyParam("recipe_id"));
  shared_ptr<User> _user_ = goodeats->find_user_by_id(stoi(_session_id_));
  goodeats->delete_recipe_from_shelve(_shelf_id_, _recipe_id_, _user_);
  return res;
}

ChefHomePage::ChefHomePage(GoodEats* _goodeats_)
{
  goodeats = _goodeats_;
}

Response* ChefHomePage::callback(Request* req)
{
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string _session_id_ = req->getSessionId();
  res->setSessionId(_session_id_);
  shared_ptr<Chef> _chef_ = goodeats->find_chef_by_id(stoi(_session_id_));
  stringstream ss;
  ss << "<!DOCTYPE html>";
  ss << "<html>";
  ss << "<body style=\"text-align: center;\">";
  ss << "<h1>Goodeats</h1>";
  ss << "<h2>";
  ss << "Recipes:"; 
  ss << "</h2>";
  ss << "<p>";
  ss << _chef_->get_recipes_info();
  ss << "</p>";
  ss << "<form action=\"ChefHomePage/AddRecipe\" method=\"get\">";
  ss << "<button type=\"submit\"> Add Recipe </button>";
  ss << "</form>";
  ss << "<br />";
  ss << "<form action=\"ChefHomePage/RemoveRecipe\" method=\"get\">";
  ss << "<button type=\"submit\"> Remove Recipe </button>";
  ss << "</form>";
  ss << "<br />";
  ss << "<form action=\"/\" method=\"post\">";
  ss << "<button type=\"submit\"> Sign out </button>";
  ss << "</form>";
  ss << "</body>";
  ss << "</html>";
  res->setBody(ss.str());
  return res;
}

AddRecipeHandler::AddRecipeHandler(GoodEats* _goodeats_)
{
  goodeats = _goodeats_;
}

Response* AddRecipeHandler::callback(Request* req)
{
  string title = req->getBodyParam("title");
  string ingredients = req->getBodyParam("ingredients");
  string vegetarian = req->getBodyParam("vegetarian");
  string minutes_to_ready = req->getBodyParam("minutes_to_ready");
  string tags = req->getBodyParam("tags");
  string image_address = req->getBodyParam("image_address");
  string _session_id_ = req->getSessionId();
  goodeats->add_recipe(title, ingredients, vegetarian, minutes_to_ready, tags, image_address, _session_id_, goodeats);
  Response* res = Response::redirect("/ChefHomePage");
  res->setSessionId(_session_id_);
  return res;
}

RemoveRecipeHandler::RemoveRecipeHandler(GoodEats* _goodeats_)
{
  goodeats = _goodeats_;
}

Response* RemoveRecipeHandler::callback(Request* req)
{
  string _recipe_id_ = req->getBodyParam("recipe_id");
  string _session_id_ = req->getSessionId();
  goodeats->delete_recipe(_session_id_, _recipe_id_);
  Response* res = Response::redirect("/ChefHomePage");
  res->setSessionId(_session_id_);
  return res;
}