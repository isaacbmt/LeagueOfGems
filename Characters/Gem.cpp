#include "Gem.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

Gem::Gem(int x, int y, int max, int index, std::string path) {
    this->gemImage = al_load_bitmap(path.c_str());
    this->x = x * 50;
    this->y = y * 50;
    this->index = index;
    this->maxPivot = max;
    this->pivot = 0;
    this->animationTimer = 0;
    this->isAcquired = false;
}

void Gem::draw() {
    al_draw_bitmap_region(gemImage, 50 * pivot, 0, 50, 50, x, y, 0);

    animationTimer++;
    if (animationTimer % 10 == 0) {
        pivot++;
        if (pivot == maxPivot)
            pivot = 0;
        if (isAcquired) {
            x = 50 + index * 50;
            y = 1075;
        }
    }
}

int Gem::getPosx() {
    return x / 50;
}

int Gem::getPosy() {
    return y / 50;
}
