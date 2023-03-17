@REM cmake build
cmake -B build
cmake --build build

@REM run
cd src
python .\randomGenerator.py
cd ../
cd bin
Assignment2.exe
Assignment2.exe ../data/special_records.txt
Assignment2.exe ../data/random_records.txt
cd ../