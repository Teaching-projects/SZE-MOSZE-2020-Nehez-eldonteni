# nehez_donteni
## Team project for MOSZE
### This project contains an RPG game made for a SZE university class.

### About the program:

The program works by giving it a scenario throug command line argument. This scenario is a .json file and contains 2 keys which are "hero" and "monsters". The values are filenames pointing to the .json files containing the characters' data. The program reads all the files and stores the hero in a Hero object and the monsters in a list of Monster objects. After that the hero fights all the monsters. The hero is able to levelup after dealing enough damage to its opponents gaining more HP, damage and lower attack cooldown.

With the help of cmake we created a Makefile which is able to test the program in different ways:
- compiles the program
- checks for errors and warnings in the code
- checks for memory leaks
- tests the output of the program after predetermined input
- tests the different methods in the classes
- also creates the documentation

These checks are run automatically on every push to github with the help of github workflows. 

### Documentation: https://teaching-projects.github.io/SZE-MOSZE-2020-Nehez-eldonteni