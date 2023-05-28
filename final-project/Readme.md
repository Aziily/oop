# Object Serialization

## Organization

* `src` - source code
* `eval` - the code help show evaluation result
* `bin` - the executable file
* `record` - the files of the performance of evaluation
* `output` - the files of data serialized
* `test.sh` - the script to run the test
* `eval.sh` - the script to run the evaluation and show

## Quick Start

If you want to **test the correctness**, you can just run the `test.sh` by `sh test.sh `. However the default code delete all sub-process outputs, if you want to see sub-process outputs, you should first *delete the clear part* of the script in `test.sh `and *change* `#define DEBUG true `in `src/xml.hpp `to see the files without base64 encoded, which end with `*.debug`.

If you want to **eval the performance**, you can just run the `eval.sh` by `sh eval.sh`.

## TEST & EVAL

**All designed cases are passed**, if covers all kinds of type, some complex composed struct and user-defined struct.


The eval result can be seen in `record/type.png` and `record/size.png` which separately test **different type's performance** and **different size's performance** of `string, vector, list, set, map`. Each evaluation is designed to deal with the same number of bytes to control variables.

By watching the result of type, we can see that the small the size of the type is, the more time it costs. That's because in order to control the same number of bytes, the smaller the size is, more time it runs. By analyze this, we can see the main time cost is from the initialization of serialization and deserialization, instead of types difference or size difference when the size is small, which means my program reach **a good result about dealing with data it self**, **no matter the data type**.

By watching the result of size, except the tendency of small sizes is out of expectation because of the long initialization time and small dealing time, the tendency of big sizes are correct. The consuming time is mainly linear to the size, which means **I deal with items of containers well**, and don't make extra cost.

Also, we can see xml is slower than binary, the reason may be **extra bytes required to keep the struct or the decode and encode part's time consuming**.

## Experience

1. **The use of template**
   This is about how to use template to match the function needed. For example, if we have a recursive function of 3 realizing `func(T data)` `func(list<T> data)` and `func(set<T> data)` and we pass `func(set<list<int>>)`, wanting to get `func(set<T>)` -> `func(list<T>)` -> `func(T)`. Then we must define the realizing of `list<T>` before `set<T>` or it will just match the `T`. So we'd better first define all and then realize.
2. **Correct usage of std::string**
   Though `string` has many characteristics like `int,float,double` and so on, it is a dynamic class and cannot be just used as basic types. Or it may cause a destroy to the program stack and lead to unexpected errors.
3. **Macro defination**
   The example can be seen in `bin.hpp` or `xml.hpp` and `test.cpp`. By using macro, we can easily realize a specail defination of an unknown type.
