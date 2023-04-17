mkdir temp
mkdir bin

copy src/*.cpp temp
copy src/*.hpp temp

make fraction

bin/main.exe

make clean