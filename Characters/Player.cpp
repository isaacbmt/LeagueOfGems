#include "Player.h"

#include <allegro5/allegro_image.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro.h>

Player::Player(std::string image) {
    this->image = al_load_bitmap(image.c_str());
    this->down = 0;
    this->times = 0;
}

Player::Player(int x, int y, std::string image) {
    this->image = al_load_bitmap(image.c_str());
    this->x = x;
    this->y = y;
    this->down = 0;
    this->times = 0;
}

void Player::update(int dx, int dy) {
    x = dx;
    y = dy;
}

void Player::draw() {
    al_draw_bitmap_region(image, 50 * down, 50 * 0, 50, 50, x, y, 0);

    times += 1;
    if (times % 7 == 0){
        down += 1;

        if (down == 3){
            down = 0;
        }
    }
}

Player::~Player() {
    al_destroy_bitmap(image);
}
