mkdir temp
mkdir bin
mkdir obj

copy src temp

make main

bin\main.exe

del temp\*.cpp
del temp\*.hpp
del obj\*.o