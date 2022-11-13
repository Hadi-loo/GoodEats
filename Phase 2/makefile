CC = g++ --std=c++11
EXE_FILE = goodeats.out

$(EXE_FILE): exceptions.o rate.o offer.o recipe.o order.o shelf.o user.o chef.o supplier.o goodeats.o test.o 
	$(CC) exceptions.o rate.o offer.o recipe.o order.o shelf.o user.o chef.o supplier.o goodeats.o test.o -o $(EXE_FILE)

exceptions.o: exceptions.cpp exceptions.hpp test.hpp
	$(CC) -c exceptions.cpp -o exceptions.o

rate.o: rate.cpp rate.hpp test.hpp
	$(CC) -c rate.cpp -o rate.o

offer.o: offer.cpp offer.hpp test.hpp
	$(CC) -c offer.cpp -o offer.o

recipe.o: recipe.cpp recipe.hpp rate.hpp chef.hpp test.hpp
	$(CC) -c recipe.cpp -o recipe.o

order.o: order.cpp order.hpp test.hpp
	$(CC) -c order.cpp -o order.o

shelf.o: shelf.cpp shelf.hpp recipe.hpp exceptions.hpp test.hpp
	$(CC) -c shelf.cpp -o shelf.o

supplier.o: supplier.cpp supplier.hpp offer.hpp test.hpp
	$(CC) -c supplier.cpp -o supplier.o

user.o: user.cpp user.hpp shelf.hpp order.hpp test.hpp
	$(CC) -c user.cpp -o user.o

chef.o: chef.cpp chef.hpp recipe.hpp test.hpp
	$(CC) -c chef.cpp -o chef.o

goodeats.o: goodeats.cpp goodeats.hpp exceptions.hpp chef.hpp user.hpp supplier.hpp recipe.hpp rate.hpp shelf.hpp test.hpp
	$(CC) -c goodeats.cpp -o goodeats.o

test.o: test.cpp test.hpp chef.hpp user.hpp supplier.hpp recipe.hpp goodeats.hpp offer.hpp
	$(CC) -c test.cpp -o test.o

clean:
	rm *.o *.out