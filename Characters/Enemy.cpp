#include <iostream>
#include "Enemy.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

Enemy::Enemy(std::string path) {
    image = al_load_bitmap(path.c_str());
    this->posx = 0;
    this->posy = 0;
//    this->maxLife = 50;
//    this->life = 50;
    this->attacking = false;
}

Enemy::Enemy(int x, int y, std::string path) {
    image = al_load_bitmap(path.c_str());
    this->posx = x;
    this->posy = y;
//    this->maxLife = 50;
//    this->life = 50;
    this->attacking = false;
}

void Enemy::update(int dx, int dy) {
    posx = dx;
    posy = dy;
}

void Enemy::draw() {
    al_draw_rectangle(posx * 50 , posy * 50 - 7, posx * 50 + maxLife, posy * 50 - 2, al_map_rgb(255, 0, 0), 1.0);
    al_draw_filled_rectangle(posx * 50 , posy * 50 - 7, posx * 50 + life, posy * 50 - 2, al_map_rgb(255, 0, 0));

    al_draw_bitmap_region(image, 50 * 0, 50 * 0, 50, 50, posx * 50, posy * 50, 0);
}

void Enemy::getDamage() {
    life -= 4;
}

int Enemy::getPower() {
    return power;
}

void Enemy::setVida(int vida) {
    this->maxLife = vida;
    this->life = vida;
    std::cout << "Vida:  " << vida << "\n" << std::endl;
}

void Enemy::setPower(int newPower) {
    this->power = newPower;
    std::cout << "Power:  " << newPower << std::endl;
}

void Enemy::startAttack() {
    attacking = true;
}

void Enemy::endAttack() {
    attacking = false;
}

bool Enemy::isAttacking() {
    return attacking;
}

Enemy::~Enemy() {
    al_destroy_bitmap(image);
    attacking = false;
}

int Enemy::getLife() {
    return life;
}

int Enemy::getPosx() {
    return posx;
}

int Enemy::getPosy() {
    return posy;
}
