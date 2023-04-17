mkdir temp
mkdir bin

copy src temp

make fraction

bin\main.exe

del temp\*.cpp
del temp\*.hpp
del temp\*.o