#ifndef LEAGUEOFGEMS_PLAYER_H
#define LEAGUEOFGEMS_PLAYER_H

#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>
#include <string>

class Player {
private:
    ALLEGRO_BITMAP *image;
    int x;
    int y;
    int down;
    int times;

public:
    Player(std::string);
    Player(int, int, std::string);
    void update(int, int);
    void draw();
    int getX(); //Añadi estos dos metodos
    int getY();
    ~Player();
};


#endif //LEAGUEOFGEMS_PLAYER_H
