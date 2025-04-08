## Tree &middot; [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT) [![Build Status](https://www.travis-ci.org/mateuszstompor/tree.svg?branch=master)](https://www.travis-ci.org/mateuszstompor/tree)


### Purpose
In order to create animations hierarchy of bones and parts of a model needs to be preserved.
It can be achived using directed acyclic graphs, but trees have many advantages, one of which is their simplicity.
Class enables user to create hierarchical tree, modify its structure and provide iterator which can notify whenever it changes level during iteration. Why is it important? This feature provides a convenient way to concatenate tranformations.

### Examples

#### Creating a Tree
```cpp
ms::tree<int> myTree;
```

#### Inserting Elements
```cpp
auto it = myTree.begin();
myTree.insert_s(it, 10);
```

#### Iterating Over the Tree
```cpp
for (auto it = myTree.begin(); it != myTree.end(); ++it) {
    std::cout << *it << " ";
}
```

#### Checking for Siblings
```cpp
auto sibling = myTree.has_sibling(it, ms::tree<int>::sibling::left);
if (sibling) {
    std::cout << "Left sibling exists.";
}
```

#### Clearing the Tree
```cpp
myTree.clear();
```

#### Using Iterators
```cpp
for (auto it = myTree.begin(); it != myTree.end(); ++it) {
    std::cout << *it << " ";
}
```

#### Using Reverse Iterators
```cpp
for (auto it = myTree.rbegin(); it != myTree.rend(); ++it) {
    std::cout << *it << " ";
}
```

#### Erasing Elements
```cpp
auto it = myTree.begin();
myTree.erase(it);
```

### Where can I find the main class?
In file named "tree.hpp"

### How many files I need to include?
Only one

### How to compile it?
There is no need of compilation. It is a header only, one class lib.

### Installation
If you would like to install the library once and for all I suggest using CMake and running the snippet placed below.
```c
$ git clone https://github.com/mateuszstompor/tree.git
$ cd tree
$ mkdir build && cd build
$ cmake ..
$ make install
```

### Can I trust it?
Yes, the entire project is tested and works correctly.

### Requirements
To use the class, you need one of the listed compilers to build your project.
If you wish to use the class on Windows, please compile with the `__WIN32__` flag.
<ul>
<li>GCC, version 8.1</li>
<li>clang, version 6.0</li>
</ul>

### Contributing
Contributions are welcome! Please fork the repository and submit a pull request. For major changes, please open an issue first to discuss what you would like to change.

### Contact
For support or inquiries, please open an issue on the [GitHub repository](https://github.com/mateuszstompor/tree/issues).