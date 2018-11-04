#ifndef LEAGUEOFGEMS_GEM_H
#define LEAGUEOFGEMS_GEM_H
#include <allegro5/allegro.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>
#include <iostream>

class Gem {
private:
    ALLEGRO_BITMAP *gemImage;
    int x;
    int y;
    int pivot;
    int maxPivot;
    int index;
    int animationTimer;
public:
    bool isAcquired;

    Gem(int x, int y, int max, int index, std::string path);
    void draw();
    int getPosx();
    int getPosy();
};

#endif //LEAGUEOFGEMS_GEM_H

