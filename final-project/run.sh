mkdir bin
mkdir temp

cp src/*.cpp temp
cp src/*.hpp temp

cd temp
g++ -std=c++20 -o ../bin/program main.cpp
cd ..
rm -rf temp

cd bin
./program
rm program
rm *.txt
cd ..