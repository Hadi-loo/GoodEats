#include "handlers.hpp"
#include "my_server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>
#include "goodeats.hpp"
#include "exceptions.hpp"

int recipe_ID = 0;
int shelve_ID = 0;
int user_ID = 0;

using namespace std;

int main(int argc, char **argv) {
  srand(time(NULL)); // for rand
  GoodEats* goodeats = new GoodEats();
  try {
    MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
    server.setNotFoundErrPage("static/404.html");
    server.get("/", new ShowPage("static/home.html"));
    server.post("/", new ShowPage("static/home.html"));
    server.get("/signup", new ShowPage("static/signup.html"));
    server.post("/signup", new SignupHandler(goodeats));
    server.get("/login", new ShowPage("static/logincss.html"));
    server.post("/login", new LoginHandler(goodeats));
    server.get("/UserHomePage", new UserHomePage(goodeats));
    server.post("/UserHomePage", new UserHomePage(goodeats));
    server.get("/ChefHomePage", new ChefHomePage(goodeats));
    //server.post("/ChefHomePage", new ChefHomePageHandler(goodeats));
    server.get("/ChefHomePage/AddRecipe", new ShowPage("static/addRecipe.html"));
    server.post("/ChefHomePage/AddRecipe", new AddRecipeHandler(goodeats));
    server.get("/ChefHomePage/RemoveRecipe", new ShowPage("static/removeRecipe.html"));
    server.post("/ChefHomePage/RemoveRecipe", new RemoveRecipeHandler(goodeats));
    server.get("/UserHomePage/RecipeInfo", new RecipeInfoHandler(goodeats));
    //server.post("/UserHomePage/RecipeInfo", new RecipeInfoHandler(goodeats));
    server.get("/UserHomePage/RateRecipe", new RateRecipe(goodeats));
    server.post("/UserHomePage/RateRecipe", new RateRecipeHandler(goodeats));
    server.get("/UserHomePage/Shelves", new ShelvesHandler(goodeats));
    //server.post("/UserHomePage/Shelves", new ShelvesHandler(goodeats));
    server.get("/UserHomePage/AddShelf", new ShowPage("static/addShelf.html"));
    server.post("/UserHomePage/AddShelf", new AddShelfHandler(goodeats));
    server.get("/UserHomePage/ShelfInfo", new ShelfInfoHandler(goodeats));
    //server.post("/UserHomePage/ShelfInfo", new ShelfInfoHandler(goodeats));
    server.get("/UserHomePage/AddRecipe", new AddRecipetoShelf(goodeats));
    server.post("/UserHomePage/AddRecipe", new AddRecipetoShelfHandler(goodeats));
    server.get("/UserHomePage/RemoveRecipe", new RemoveRecipefromShelf(goodeats));
    server.post("/UserHomePage/RemoveRecipe", new RemoveRecipefromShelfHandler(goodeats));
    server.run();
  } 
  catch (Server::Exception e) 
  {
    cerr << e.getMessage() << endl;
  }
}
