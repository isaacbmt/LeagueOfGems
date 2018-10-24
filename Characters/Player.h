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
public:
    Player(std::string);
    Player(int, int, std::string);
    void draw(int, int);
};


#endif //LEAGUEOFGEMS_PLAYER_H
