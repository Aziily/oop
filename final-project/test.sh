# make directory
mkdir bin
mkdir output
mkdir temp

# copy file
cp src/*.cpp temp
cp src/*.hpp temp

# compile
cd temp
g++ -std=c++2a -o ../bin/test test.cpp
cd ..

# run
cd bin
./test
cd ..

# clear
rm -rf bin
rm -rf temp
rm -rf output