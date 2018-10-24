#include "Player.h"

#include <allegro5/allegro_image.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro.h>

Player::Player(std::string image) {
    this->image = al_load_bitmap(image.c_str());
}

Player::Player(int x, int y, std::string image) {
    this->image = al_load_bitmap(image.c_str());
    this->x = x;
    this->y = y;
}

void Player::draw(int dx, int dy) {
    x = dx;
    y = dy;

    al_draw_bitmap(image, x, y, 0);
}
