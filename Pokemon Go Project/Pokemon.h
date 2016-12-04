#ifndef POKEMON_H_INCLUDED
#define POKEMON_H_INCLUDED

#include "SDL_Plotter.h"
#include "Trainer.h"
#include "Background.h"

#include <string>
#include <ctime>
#include <vector>

using namespace std;

//Partially Provided by Dr. Booth
class Pokemon{
    private:
        Point loc;
        Point oldLoc;
        Point menuLocations[6];
        Color pic[256][256];

        int index;
        int rows, cols;
        int count = 0;
        double points = 0;

        vector<string> pokemonList;
        string pokemonName;

    public:
       /*
        * description: default constructor for the Pokemon
        * return: default Pokemon
        * precondition: none
        * postcondition: default Pokemon is constructed
        */
        Pokemon();

       /*
        * description: provides a more centered location for the Pokemon
        * return: int
        * precondition: must be a location.x
        * postcondition: returns int that better centers the Pokemon
        */
        int getCenteredLocX();

       /*
        * description: provides a more centered location for the Pokemon
        * return: int
        * precondition: must be a location.y
        * postcondition: returns int that better centers the Pokemon
        */
        int getCenteredLocY();

       /*
        * description: chooses a Pokemon from a list
        * return: string
        * precondition: must be a Pokemon list
        * postcondition: returns a random Pokemon
        */
        string choosePokemon(vector<string>&);

       /*
        * description: draws a Pokemon the screen
        * return: none
        * precondition: must pass in a plotter and must have a Pokemon to draw and pass in a plotter
        * postcondition: returns int that better centers the Pokemon
        */
        void draw(SDL_Plotter&);

       /*
        * description: picks a random location to spawn a Pokemon.
        * return: none
        * precondition: must have a loc.x and loc.y
        * postcondition: gives loc.x and loc.y a new location
        */
        void selectRandomSpawn();

       /*
        * description: spawns a new Pokemon when the previous one is caught
        * return: none
        * precondition: trainer must have the same location as Pokemon and pass in a plotter
        * postcondition: a new Pokemon is spawned in a new location
        */
        void caught(SDL_Plotter&);

       /*
        * description: erases the Pokemon
        * return: none
        * precondition: must have a Pokemon to erase and pass in a plotter
        * postcondition: Pokemon gets erased
        */
        void erase(SDL_Plotter&);

       /*
        * description: moves the Pokemon to the menu
        * return: none
        * precondition: the Pokemon must be caught for it to be moved
        * postcondition: Pokemon is drawn in the new location on the menu
        */
        void moveToMenu(SDL_Plotter&, int);
};

//Partially provided by Dr. Booth
Pokemon::Pokemon(){

    int xPos = 232;
    for(int i = 0; i < 6; i++){
        menuLocations[i].x = xPos;
        menuLocations[i].y = 1050;
        xPos+= 31;
    }
    pokemonName = choosePokemon(pokemonList);

    ifstream input(pokemonName.c_str());

    input >> rows >> cols;
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            input >> pic[r][c].R;
            input >> pic[r][c].G;
            input >> pic[r][c].B;
        }
    }
    input.close();
    selectRandomSpawn();
}

//Selects new (random) spawn location
void Pokemon::selectRandomSpawn(){
    double newX, newY;
    srand(time(0));

    do{
        newX = (rand() * rand())%850+1;
    }while(newX <= 120 || newX >= 850);

    do{
        newY = (rand() * rand())%390+1;
    }while(newY <= 60 || newY >= 390);

    loc.y = newY;
    loc.x = newX;
}

//Moves to the Phone Screen (Menu)
void Pokemon::moveToMenu(int a){
    loc.x = menuLocations[a].x;
    loc.y = menuLocations[a].y;
}

//Chooses random Pokemon from list
string Pokemon::choosePokemon(vector<string>& pokemonList){
    string currentIndex;
    ifstream getList("Pokemon List");
    while(getList >> currentIndex)
        pokemonList.push_back(currentIndex);

    srand(time(0));
    int index = (rand() * rand())%150;

    return pokemonList[index];
}

//Returns a more centered X coordinate of Pokemon
int Pokemon::getCenteredLocX(){
    return loc.x + 5;
}

//Returns a more centered Y coordinate of Pokemon
int Pokemon::getCenteredLocY(){
    return loc.y - 5;
}

//Draws Pokemon (Cuts out white corners)
//Partially provided by Dr. Booth
void Pokemon::draw(SDL_Plotter& g){
    erase(g);
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            if(loc.x + c >= 0  &&
               loc.y + r >= 0  &&
               loc.x + c < 960 &&
               loc.y + r < 512)
            {
                //If pixel is white
                if(pic[r][c].R < 255 &&
                   pic[r][c].G < 255 &&
                   pic[r][c].B < 255)
                {
                    //Draw pixel of background instead
                    g.plotPixel(loc.x + c, loc.y + r,
                    pic[r][c].R,
                    pic[r][c].G,
                    pic[r][c].B);
                }
                //If pixel is not white
                else if(pic[r][c].R == 255 &&
                        pic[r][c].G == 255 &&
                        pic[r][c].B == 255)
                {
                    g.plotPixel(loc.x + c, loc.y + r,
                    current.getR(r, c),
                    current.getG(r, c),
                    current.getB(r, c));
                }
            }
        }
    }
}

//Spawns a new Pokemon when current Pokemon is caught
void Pokemon::caught(SDL_Plotter& g){
    pokemonName = choosePokemon(pokemonList);

    ifstream input(pokemonName.c_str());
    input >> rows >> cols;
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            input >> pic[r][c].R;
            input >> pic[r][c].G;
            input >> pic[r][c].B;
        }
    }
    input.close();
    erase(g);
    selectRandomSpawn();
    points += 100;
}

//Erases Pokemon
//Provided by Dr. Booth
void Pokemon::erase(SDL_Plotter& g){
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            if(loc.x + c >= 0  &&
               loc.y + r >= 0  &&
               loc.x + c < 960 &&
               loc.y + r < 512)
            {
                g.plotPixel(loc.x + c, loc.y + r,
                current.getR(r, c),
                current.getG(r, c),
                current.getB(r, c));
            }
        }
    }
}

#endif // POKEMON_H_INCLUDED
