#include "Player.h"

#include <allegro5/allegro_image.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro.h>

Player::Player(std::string image) {
    this->image = al_load_bitmap(image.c_str());
    this->movement = 0;
    this->animationTimer = 0;
    this->life = 3;
    attack = false;
}

Player::Player(int x, int y, std::string image) {
    this->image = al_load_bitmap(image.c_str());
    this->x = x;
    this->y = y;
    this->movement = 0;
    this->animationTimer = 0;
    this->life = 3;
    attack = false;
}

void Player::update(int dx, int dy)
{
    if (dx - x < 0)
        direction = 1;
    else if (dx - x > 0)
        direction = 2;
    else if (dy- y < 0)
        direction = 3;
    else if (dy - y > 0)
        direction = 0;

    x = dx;
    y = dy;
}

void Player::draw() {
    al_draw_bitmap_region(image, 50 * movement, 50 * direction, 50, 50, x, y, 0);
    timer();
}

void Player::timer(){
    animationTimer += 1;

    if (animationTimer % 14 == 0){
        movement += 1;
        if (movement == 3){
            movement = 0;
        }
    }

    if (animationTimer % 28 == 0) {
        if (attackX % 2 == 0 ){
            attack = false;
        }
        attackX--;
    }
}

void Player::attacking() {
    attackX = 3;
    attack = true;
}

int Player::getDirection() const {
    return direction;
}

int Player::getPosx() {
    return x / 50;
}

int Player::getPosy() {
    return y / 50;
}

bool Player::isAttacking() {
    return attack;
}

Player::~Player() {
    al_destroy_bitmap(image);
}

Dijkstra *Player::getDij() {
    return dij;
}

void Player::setDij(int map[21][27]) {
    dij = new Dijkstra(map);
}
