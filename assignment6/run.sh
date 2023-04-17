mkdir temp
mkdir bin
mkdir obj

cp src/*.cpp temp
cp src/*.hpp temp

make main

bin/main

make clean
