mkdir bin
mkdir temp
mkdir output

cp src/*.cpp temp
cp src/*.hpp temp

cd temp
g++ -std=c2x -Wall -Wextra -pedantic -O3 -o ../bin/program main.cpp
cd ..
rm -rf temp

cd bin
./program
rm program
# rm *.txt
cd ..