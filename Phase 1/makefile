CC = g++ --std=c++11
EXE_FILE = goodeats.out

$(EXE_FILE): exceptions.o rate.o recipe.o shelf.o user.o chef.o goodeats.o test.o 
	$(CC) exceptions.o rate.o recipe.o shelf.o user.o chef.o goodeats.o test.o -o $(EXE_FILE)

exceptions.o: exceptions.cpp exceptions.hpp test.hpp
	$(CC) -c exceptions.cpp -o exceptions.o

rate.o: rate.cpp rate.hpp test.hpp
	$(CC) -c rate.cpp -o rate.o

recipe.o: recipe.cpp recipe.hpp rate.hpp chef.hpp test.hpp
	$(CC) -c recipe.cpp -o recipe.o

shelf.o: shelf.cpp shelf.hpp recipe.hpp exceptions.hpp test.hpp
	$(CC) -c shelf.cpp -o shelf.o

user.o: user.cpp user.hpp shelf.hpp test.hpp
	$(CC) -c user.cpp -o user.o

chef.o: chef.cpp chef.hpp recipe.hpp test.hpp
	$(CC) -c chef.cpp -o chef.o

goodeats.o: goodeats.cpp goodeats.hpp exceptions.hpp chef.hpp user.hpp recipe.hpp rate.hpp shelf.hpp test.hpp
	$(CC) -c goodeats.cpp -o goodeats.o

test.o: test.cpp test.hpp chef.hpp user.hpp recipe.hpp goodeats.hpp test.hpp
	$(CC) -c test.cpp -o test.o

clean:
	rm *.o