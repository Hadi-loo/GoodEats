#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "../server/server.hpp"
#include <cstdlib> 
#include <ctime>  
#include <iostream>
class GoodEats;

class SignupHandler : public RequestHandler 
{
public:
  SignupHandler(GoodEats*);
  Response* callback(Request*);
private:
  GoodEats* goodeats;
};

class LoginHandler : public RequestHandler 
{
public:
  LoginHandler(GoodEats*);
  Response* callback(Request*);
private:
  GoodEats* goodeats;
};

class UserHomePage : public RequestHandler
{
public:
  UserHomePage(GoodEats*);
  Response* callback(Request*);
private:
  GoodEats* goodeats;
};

class RecipeInfoHandler : public RequestHandler
{
public:
  RecipeInfoHandler(GoodEats*);
  Response* callback(Request*);
private:
  GoodEats* goodeats;
};

class RateRecipe : public RequestHandler
{
public:
  RateRecipe(GoodEats*);
  Response* callback(Request*);
private:
  GoodEats* goodeats;
};

class RateRecipeHandler : public RequestHandler
{
public:
  RateRecipeHandler(GoodEats*);
  Response* callback(Request*);
private:
  GoodEats* goodeats;
};

class ShelvesHandler : public RequestHandler
{
public:
  ShelvesHandler(GoodEats*);
  Response* callback(Request*);
private:
  GoodEats* goodeats;
};

class AddShelfHandler : public RequestHandler
{
public:
  AddShelfHandler(GoodEats*);
  Response* callback(Request*);
private:
  GoodEats* goodeats;
};

class ShelfInfoHandler : public RequestHandler
{
public:
  ShelfInfoHandler(GoodEats*);
  Response* callback(Request*);
private:
  GoodEats* goodeats;
};


class AddRecipetoShelf : public RequestHandler
{
public:
  AddRecipetoShelf(GoodEats*);
  Response* callback(Request*);
private:
  GoodEats* goodeats;
};

class AddRecipetoShelfHandler : public RequestHandler
{
public:
  AddRecipetoShelfHandler(GoodEats*);
  Response* callback(Request*);
private:
  GoodEats* goodeats;
};

class RemoveRecipefromShelf : public RequestHandler
{
public:
  RemoveRecipefromShelf(GoodEats*);
  Response* callback(Request*);
private:
  GoodEats* goodeats;
};

class RemoveRecipefromShelfHandler : public RequestHandler
{
public:
  RemoveRecipefromShelfHandler(GoodEats*);
  Response* callback(Request*);
private:
  GoodEats* goodeats;
};

class ChefHomePage : public RequestHandler
{
public:
  ChefHomePage(GoodEats*);
  Response* callback(Request*);
private:
  GoodEats* goodeats;
};

class AddRecipeHandler : public RequestHandler
{
public:
  AddRecipeHandler(GoodEats*);
  Response* callback(Request*);
private:
  GoodEats* goodeats;  
};

class RemoveRecipeHandler : public RequestHandler
{
public:
  RemoveRecipeHandler(GoodEats*);
  Response* callback(Request*);
private:
  GoodEats* goodeats;
};


#endif
