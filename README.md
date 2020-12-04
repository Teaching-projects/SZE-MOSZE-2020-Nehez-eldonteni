# nehez_donteni
## Team project for MOSZE
This project contains an RPG game made for a SZE university class.

### About the program:
The program is simulating a classic RPG game where a hero clears maps full of monsters. While the hero grinds through all the enemies he gains multiple powerups and stats so he can face stronger and stronger enemies on the way.

### Core functionallity:
The game is controlled by the `Game` or the `PreparedGame` class. The difference between them is that the `PreparedGame` class asks for a `.json` file which contains all the required information to start the game, such as the map, hero and monsters, meanwhile the `Game` class only asks for the map at the start and the hero and monsters are *imported* via *methods*.

The maps are `.txt` files. The normal map have `#` characters where the walls are and `' '(whitespace)` where the hero can walk. They can be imported by the `Map` class.
For the prepared games there is a different kind of map called a marked map. It's similar the normal map but it conatains more information: the starting position of the hero and a *layout of monsters*. Every monster is *identified by* it's character and these characters are *marked* on the map. The characters are *assigned* to the monsters in the preparedgame `.json` files.

The hero and monster *attributes* are stored in `.json` files. These *attributes* are pretty common in RPG games such as **Damage**, **Magical Damage**, **HP**, **Attack Cooldown**.

The details of games and prepared games are also stored in `.json` files. The game class can take a filename in it's *constructor*, but it can be added later via the `game.setMap()` *method*. The `PreparedGame` class on the other hand takes a `.json` file that contains a map, a hero and the monsters by their filenames.

Multiple renderers can be *assigned* to games and prepared games, which control how the games are being *displayed*.
The `Renderer` is an *absract class*. Multiple types of renderers have been *derived* from the `Renderer`:
- `HeroTextRenderer`: Provides *text based display* solution
- `ObserverTextRenderer`: Provides *text based display* solution that shows the whole map(normally it's limited by the hero's vision)
- `CharacterSVGRenderer`: Provides an *svg file based display* solution with the hero vision limit
- `ObserverSVGRenderer`: Provides an *svg file based display* solution for the *full* map

All the text renderers can take *outputstream objects*(with `std::cout` as *default value* if there is *no given parameter*), on the other hand svg renderers take filenames.

The `.json` files are all *processed* by the `JSON` class which *parses* the *files* and *reads* all the information needed for the program.

### Testing
We implemented multiple tests to make sure the program works as expected. We test the *classes, inputs, code outputs, syntax and memory usage.*
All the tests are *executed* in a `Docker` container witht the *latest Ubuntu* system. `Git workflows` *start and run* the tests **on every push**.

#### Testing workflows:
- `Output_test`: Checks the output of the program and compares it to the manually calculated results, checks the code for errors, warnings, memory leaks and the code's performance
- `code_test`:  Runs all the tests created for the program to test it's features and values
    

### Documentation
The [documentation](https://teaching-projects.github.io/SZE-MOSZE-2020-Nehez-eldonteni/index.html) for the project is pushed to github pages after every adjustment.
