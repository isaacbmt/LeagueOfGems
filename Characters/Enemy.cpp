#include <allegro5/bitmap_io.h>
#include <allegro5/bitmap_draw.h>
#include "Enemy.h"

Enemy::Enemy(std::string path) {
    image = al_load_bitmap(path.c_str());
}

Enemy::Enemy(int x, int y, std::string path) {
    image = al_load_bitmap(path.c_str());
    this->x = x;
    this->y = y;
}

void Enemy::update(int dx, int dy) {
    x = dx;
    y = dy;
}

void Enemy::draw() {
    al_draw_bitmap_region(image, 50 * 0, 50 * 0, 50, 50, x, y, 0);
}

Enemy::~Enemy() {
    al_destroy_bitmap(image);
}
