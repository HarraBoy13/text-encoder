# Text Compressor

Created by Harish M, CH25B038

## Overview

This project aims to understand the inner workings of a famous compression algorithm, the Huffman Encoding Algorithm. It uses file input and output to directly write into .txt files. This project uses a node object to define the Huffman Tree, which is the main graph that determines the codes for each letter. It uses this to create a binary sequence of 0s and 1s, which is then joined together and broken apart into bytes of 8, then converted into a raw binary file.

## Important Advisory Upon Usage

- Upon cloning this project, it is suggested to create the following in your current project working directory:
    1. A `file` folder containing:
        1. `in_file.txt` - This file contains your raw data: paragraphs, poems, etc.
    2. An `exe` folder - This will serve as the folder for your executable.

### Running the File
If you want to create the executable on a command terminal, use the following command:

```
mingw32-make
```

or use 
```
g++ -Iinclude src/*.cpp -o <RequiredInstallPath>
```
Replace `src/*.cpp` with all the files in the `src/` folder.

Then the file is saved as `Text_Encoder.exe` in the `exe` folder, which you can use to convert your files.

### VS Code Usage
- If the code is meant to be run in VS Code, the `.vscode` file is expected to be cloned as is, as it contains information that needs for this project to work.
- This project has been tested exclusively on **VS Code**. Else, stay tuned! A better version is coming soon... ;)

## Inner Workings

Huffman Encoding is one of the earliest theoretical encoding systems. It is born from the field of information theory, which concerns how information from systems is quantified. The basic working of this algorithm, and this implementation is as follows:
1. First, the text is scanned, and the frequencies of each letter is counted and stored in the `std::map` object.
2. The `std::map` object is then converted into a sequence of node objects, stored in an `std::priority_queue` min-heap.
3. Then, the graph is built, taking two elements out of the heap, and combining them into a new node, then pushed back.
4. Step 3 is repeated until there is only one element in the heap.
5. Using the depth-first search algorithm, each element is assigned their codes, stored in an `std::map` object, with being the first-child adding a 0, and being the second-child adding a 1 at the end.
6. The binary is then later appended to a string `bin_string`, filled with only 0s and 1s.
7. Using `bin_string`, every 8 characters are taken, and changed into a character using ASCII references.
8. This is then written as binary into a .bin file, created in the same folder.

## Concepts Learned

1. C++ file handling
    1. Using `ifstream`, `ofstream`, `fstream`
    2. Basic file handling
    3. `ios::trunc`, `ios::out`, `ios::app`, and uses of these.
2. Basic C++
    1. Pointers, `struct`s
    2. `.flush()` function and its use.
    3. Custom comparator functions in C++
3. Object Oriented Programming
    1. Classes, `class` keyword
    2. Constructor functions
    3. Destructor functions
    4. Custom functions
    5. `private` and `public` variables
4. Graphs in C++
    1. Nodes
    2. Child nodes
    3. Joining two nodes
5. Huffman Encoding
    1. `std::priority_queue` and `std::map` objects, and their uses.
6. File Structure
    1. `include`, `src`, and other standard file hierarchies.
7. Makefile
    1. `g++` compiler statements, compilation hierarchy, commands

## Version Log
1. v0.1 - Encoder object made more abstract, seperate folder, project encoding tested and works perfectly.
2. v0.1.1 (current) - Slight cleaning up in the Makefile