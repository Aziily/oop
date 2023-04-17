# Student II

## Meaning of dir and file

* **src**
  source code, only main.cpp this time
* **data**
  the test data of this assignment
* **[build]**
  the directory of cmake cache
* **[bin]**
  the dirctory of executable binary file
* CMakeLists.txt
  the file for cmake
* go.bat
  the script for windows users

## How to use

For a basic test, you can just run go.bat and see the result in command line, it will show the three cases -- basic, special and random.

If you want to make some changes, you can first run go.bat to generate a executable file (or compile by yourself), then you can change the records in **./data/*.txt** to give different records.

You can also give a customed records data by giving the relative/absolute path for the executable file like `./Assignment1.exe ../data/records.txt `

But, remember the records should be given as the format below

> name/name1:score1/name2:score2/.../nameX:scoreX

one example is

> K.Weng/a:5/b:5/c:5

Because I think the assignment is similar to a database, so I am in favour of using txt file as input, so I only offer such function and you cannot insert by using shell or something. Maybe latter I will add it.

> P.S.
>
> In order to test whether the program do well under random case, I offer one python file to randomly generate records. It is in the **./src/randomGenerator.py**, you can use it with `python randomGenerator.py`.
>
> Remember that because the program are all built under relative paths, when using the python file or the exe file, you should first enter the fold by using `cd src` or `cd bin` from current fold.
