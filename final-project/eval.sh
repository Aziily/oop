# make directory
mkdir bin
mkdir output
mkdir record
mkdir temp

# copy file
cp src/*.cpp temp
cp src/*.hpp temp

# compile
cd temp
g++ -std=c++2a -o ../bin/eval eval.cpp
cd ..

# run
cd bin
./eval
cd ..

pip install matplotlib
python3 eval/eval.py

# clear
rm -rf bin
rm -rf temp
rm -rf output