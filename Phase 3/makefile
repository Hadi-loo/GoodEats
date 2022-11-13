CC=g++
STD=-std=c++11 -Wall
CF=$(STD)
BUILD_DIR=build
TEMPLATE_DIR=.template

all: $(BUILD_DIR) myserver.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: examples/handlers.cpp examples/handlers.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp examples/goodeats.hpp examples/user.hpp examples/chef.hpp examples/recipe.hpp examples/shelf.hpp
	$(CC) $(CF) -c examples/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/my_server.o: examples/my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c examples/my_server.cpp -o $(BUILD_DIR)/my_server.o



$(BUILD_DIR)/exceptions.o: examples/exceptions.cpp examples/exceptions.hpp examples/test.hpp
	$(CC) -c examples/exceptions.cpp -o $(BUILD_DIR)/exceptions.o

$(BUILD_DIR)/rate.o: examples/rate.cpp examples/rate.hpp examples/test.hpp
	$(CC) -c examples/rate.cpp -o $(BUILD_DIR)/rate.o

$(BUILD_DIR)/offer.o: examples/offer.cpp examples/offer.hpp examples/test.hpp
	$(CC) -c examples/offer.cpp -o $(BUILD_DIR)/offer.o

$(BUILD_DIR)/recipe.o: examples/recipe.cpp examples/recipe.hpp examples/rate.hpp examples/chef.hpp examples/test.hpp
	$(CC) -c examples/recipe.cpp -o $(BUILD_DIR)/recipe.o

$(BUILD_DIR)/order.o: examples/order.cpp examples/order.hpp examples/test.hpp
	$(CC) -c examples/order.cpp -o $(BUILD_DIR)/order.o

$(BUILD_DIR)/shelf.o: examples/shelf.cpp examples/shelf.hpp examples/recipe.hpp examples/exceptions.hpp examples/test.hpp
	$(CC) -c examples/shelf.cpp -o $(BUILD_DIR)/shelf.o

$(BUILD_DIR)/supplier.o: examples/supplier.cpp examples/supplier.hpp examples/offer.hpp examples/test.hpp
	$(CC) -c examples/supplier.cpp -o $(BUILD_DIR)/supplier.o

$(BUILD_DIR)/user.o: examples/user.cpp examples/user.hpp examples/shelf.hpp examples/order.hpp examples/test.hpp
	$(CC) -c examples/user.cpp -o $(BUILD_DIR)/user.o

$(BUILD_DIR)/chef.o: examples/chef.cpp examples/chef.hpp examples/recipe.hpp examples/test.hpp
	$(CC) -c examples/chef.cpp -o $(BUILD_DIR)/chef.o

$(BUILD_DIR)/goodeats.o: examples/goodeats.cpp examples/goodeats.hpp examples/exceptions.hpp examples/chef.hpp examples/user.hpp examples/supplier.hpp examples/recipe.hpp examples/rate.hpp examples/shelf.hpp examples/test.hpp
	$(CC) -c examples/goodeats.cpp -o $(BUILD_DIR)/goodeats.o

$(BUILD_DIR)/test.o: examples/test.cpp examples/test.hpp examples/chef.hpp examples/user.hpp examples/supplier.hpp examples/recipe.hpp examples/goodeats.hpp examples/offer.hpp
	$(CC) -c examples/test.cpp -o $(BUILD_DIR)/test.o



$(BUILD_DIR)/main.o: examples/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp examples/goodeats.hpp
	$(CC) $(CF) -c examples/main.cpp -o $(BUILD_DIR)/main.o

myserver.out: $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/exceptions.o $(BUILD_DIR)/rate.o $(BUILD_DIR)/offer.o $(BUILD_DIR)/recipe.o $(BUILD_DIR)/order.o $(BUILD_DIR)/shelf.o $(BUILD_DIR)/supplier.o $(BUILD_DIR)/user.o $(BUILD_DIR)/chef.o $(BUILD_DIR)/goodeats.o $(BUILD_DIR)/test.o
	$(CC) $(CF) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o  $(BUILD_DIR)/exceptions.o $(BUILD_DIR)/rate.o $(BUILD_DIR)/offer.o $(BUILD_DIR)/recipe.o $(BUILD_DIR)/order.o $(BUILD_DIR)/shelf.o $(BUILD_DIR)/supplier.o $(BUILD_DIR)/user.o $(BUILD_DIR)/chef.o $(BUILD_DIR)/goodeats.o $(BUILD_DIR)/test.o -o myserver.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
