mkdir temp
mkdir bin

copy src/*.cpp temp

make fraction

bin/main.exe

make clean