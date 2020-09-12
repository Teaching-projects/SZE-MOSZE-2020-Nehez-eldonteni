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
After that the program creates the two objects and starts a loop where the two characters fight each other 
until one of them dies (hp goes down to 0).
