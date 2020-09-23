# nehez_donteni
Team project for MOSZE
This project contains an RPG game made for a SZE university class.

About the program:
The character class contains all information about the fighting opponents such as name, hp and attack value.
The initialization of the object is done through the constructor where the name, hp and attack value must be given. One
character can attack another by calling the "attackEnemy" method and passing the opponent as parameter. This
mehtod is a shortcut to the "takeDamage" method which decreases the hp of the character by the attack value
of the character given as parameter. The ostream operator(<<) has been overwritten to ease the output of the
information about the character.

Both character's information is given through  commmand line arguments.
After that, the program creates the two objects and starts a loop where the two characters fight each other
until one of them dies (hp goes down to 0).

Every character's information is stored in json files inside the "units" folder. The program reads the json files given as command line arguments with a static method in character.h (if anything is wrong with the files it throws a custom exception). It reads out all the information and feeds it to the constructor which creates the new characters. After this, the created characters start fighting. The outcome of the fight is shown on the command line output.

We have a shell script that outputs all the scenarios into a single file and compares it to the manually calculated results to make sure the program works properly.

We also have a Git Actions pipeline that tests the program on every push with the help of our shell script.
