#include "Player.h"
#include "../GreedyAlgorithms/AstarDirectory/execAStar.h"

#include <allegro5/allegro_image.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro.h>

Player::Player(std::string image) {
    this->image = al_load_bitmap(image.c_str());
    this->healImg = al_load_bitmap("../resources/heal.png");
    this->movement = 0;
    this->animationTimer = 0;
    this->life = 2;
    this->aIndex = 0;
    this->aLength = 0;
    attack = false;
    healing = false;
}

Player::Player(int x, int y, std::string image) {
    this->image = al_load_bitmap(image.c_str());
    this->healImg = al_load_bitmap("../resources/heal.png");
    this->x = x;
    this->y = y;
    this->movement = 0;
    this->animationTimer = 0;
    this->life = 2;
    this->aIndex = 0;
    this->aLength = 0;
    attack = false;
    healing = false;
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
    al_draw_rectangle(getPosx() * 50 , getPosy() * 50 - 7, getPosx() * 50 + 45, getPosy() * 50 - 2, al_map_rgb(0, 0, 255), 1.0);
    al_draw_filled_rectangle(getPosx() * 50 , getPosy() * 50 - 7, getPosx() * 50 + life, getPosy() * 50 - 2, al_map_rgb(0, 0, 255));

    al_draw_bitmap_region(image, 50 * movement, 50 * direction, 50, 50, x, y, 0);

    if (healing)
        al_draw_bitmap_region(healImg, 50 * healX, 0, 50, 50, x, y, 0);

    timer();
}

void Player::timer() {
    animationTimer += 1;

    if (animationTimer % 14 == 0){
        movement += 1;
        if (movement == 3){
            movement = 0;
        }
    }

    if (animationTimer % 7 == 0){
        healX++;
        if (healX == 10)
            healX = 0;
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

int Player::getLife() {
    return life;
}

void Player::heal() {
    if (life < 45) {
        life += 2;
        healing = true;
    } else {
        healing = false;
    }
}

void Player::stopHeal() {
    healing = false;
}

void Player::setAstar(int map[21][27], MapSearchNode nodoEnd) {
    MapSearchNode nodoStart;
    nodoStart.x = getPosx();
    nodoStart.y = getPosy();

    aStar = ejecutable.obtenerCoordenadas(map, nodoStart, nodoEnd);
}

vector<coordinate> Player::getAstar() {
    return aStar;
}

Dijkstra *Player::getDij() {
    return dij;
}

void Player::setDij(int map[21][27]) {
    dij = new Dijkstra(map);
}

Player::~Player() {
    al_destroy_bitmap(image);
}

int Player::getALength() const {
    return aLength;
}
