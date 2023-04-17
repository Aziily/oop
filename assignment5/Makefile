object = ./temp/main.o ./temp/fraction.o
Flag = -std=c++11 -O3

fraction: $(object)
	g++ -o ./bin/main $(object) $(Flag)
./temp/main.o: ./temp/main.cpp
	g++ -c ./temp/main.cpp -o ./temp/main.o $(Flag)
./temp/fraction.o: ./temp/fraction.cpp
	g++ -c ./temp/fraction.cpp -o ./temp/fraction.o $(Flag)
clean:
	rm -f ./temp/*.cpp
	rm -f ./temp/*.o
	rm -f ./bin/main