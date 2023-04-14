mkdir temp
mkdir bin

copy src\\main.cpp temp\\main.cpp
copy src\\base.hpp temp\\base.hpp
copy src\\base.cpp temp\\base.cpp
copy src\\pdadd\\pdadd.hpp temp\\pdadd.hpp
copy src\\pdadd\\pdadd.cpp temp\\pdadd.cpp
copy src\\pdlist\\pdlist.hpp temp\\pdlist.hpp
copy src\\pdlist\\pdlist.cpp temp\\pdlist.cpp
copy src\\pdshow\\pdshow.hpp temp\\pdshow.hpp
copy src\\pdshow\\pdshow.cpp temp\\pdshow.cpp
copy src\\pdremove\\pdremove.hpp temp\\pdremove.hpp
copy src\\pdremove\\pdremove.cpp temp\\pdremove.cpp

cd temp
g++ main.cpp^
    base.hpp base.cpp^
    pdadd.hpp pdadd.cpp^
    pdlist.hpp pdlist.cpp^
    pdshow.hpp pdshow.cpp^
    pdremove.hpp pdremove.cpp^
    -O3^
    -o ..\\bin\\assignment4.exe
cd ..

bin\assignment4.exe