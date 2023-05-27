mkdir bin
mkdir output
mkdir temp

cp src/*.cpp temp
cp src/*.hpp temp

cd temp
g++ -std=c++2a -o ../bin/program main.cpp
cd ..
rm -rf temp

cd bin
./program
# rm program
cd ..