#include "Gem.h"

Gem::Gem(int x, int y, std::string path) {
    this->gemImage = al_load_bitmap(path.c_str());
    this->x = x * 50;
    this->y = y * 50;
    this->pivot = 0;
    this->animationTimer = 0;
    this->isAcquired = false;
}

void Gem::draw() {
    al_draw_bitmap_region(gemImage, 50 * pivot, 0, 50, 50, x, y, 0);

    animationTimer++;
    if (animationTimer % 10 == 0) {
        pivot++;
        if (pivot == 6)
            pivot = 0;
        if (isAcquired) {
            x = 100;
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
