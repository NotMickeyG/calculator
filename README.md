# calculator

This is a simple terminal calculator and parser made using string and regex handling as an introduction to C++ for myself.

Created as a Visual Studio C++ project so may be difficult to compile as is without Visual Studio.

## TODO

* Try implementing some custom CommandNodes and Assigners:

  * "help" prints help info to console

  * "exit" exits the program which would allow parse errors to be handled without exiting in main()

  * empty value handling, eg some calculators would detect "* 5" and multiply the last answer by 5 (probably quite complex in this calculator implementation, could do some cheese, like, "" gets assigned LastAnswer CommandNode)

* subTrees_ should probably go in BracketChecker and BracketAssigner should get passed a reference to BracketChecker to access the trees. This is because BracketChecker is doing the most work with the tree, BracketAssigner just uses the tree to get a return value (see BracketChecker and BracketAssigner in CalculatorAssigners.cpp)
