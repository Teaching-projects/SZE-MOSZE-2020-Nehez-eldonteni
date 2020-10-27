# nehez_donteni
Team project for MOSZE
This project contains an RPG game made for a SZE university class.

About the program:
The character class contains all information about the fighting opponents such as name, hp, attack value and cooldown. The initialization of the object is done through the constructor where the name, hp and attack value must be given. One character can attack another by calling the "attackEnemy" method and passing the opponent as parameter. This method calls the "takeDamage" method which decreases the hp of the character by the attack value of the character given as parameter. It also sets the characters attack cooldown for the next attack. The ostream operator(<<) has been overwritten to ease the output of the information about the character.

The adventurer class is inherited from the character class. It adds an xp system for the character. It works by giving the character the ammount of xp it inflicted on the enemy. For every 100 xp the adventurer levels up increases its maximum hp and attack by 10%, regenerates its hp to full and decreases the attack cooldown by 10%.

Both character's information is given through commmand line arguments. After that, the program creates the two objects and starts a loop where the two characters fight each other until one of them dies (hp goes down to 0). This logic is inside of the character class and it can be started by calling one of the characters fight method and give the other character as parameter.

Every character's information is stored in json files inside the "testing/units" folder. The program reads the json files given as command line arguments with a static method in character.h (if anything is wrong with the files it throws a custom exception). This function uses the JSONParser class which can read data from file, iostream and string. It reads out all the information and feeds it to the constructor which creates the new characters. After this, the created characters start fighting. The outcome of the fight is shown on the command line output.

We have a shell script that outputs all the scenarios into a single file and compares it to the manually calculated results to make sure the program works properly.

We also have some Git Actions pipelines that tests the program in multiple ways:
    - Output_test: check for memory leaks, errors and warnings
    - JSONParse_tests: checks all possible ways to read json via JSONParse class

The documentation for the project is pushed to github pages after every adjustment.