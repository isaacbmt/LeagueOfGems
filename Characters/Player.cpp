#include "Player.h"

#include <allegro5/allegro_image.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro.h>

Player::Player(std::string image) {
    this->image = al_load_bitmap(image.c_str());
    this->imgAttack = al_load_bitmap("../resources/swordsheet.png");
    this->down = 0;
    this->animationTimer = 0;
    this->life = 3;
    attack = false;
}

Player::Player(int x, int y, std::string image) {
    this->image = al_load_bitmap(image.c_str());
    this->imgAttack = al_load_bitmap("../resources/swordsheet.png");
    this->x = x;
    this->y = y;
    this->down = 0;
    this->animationTimer = 0;
    this->life = 3;
    attack = false;
}

void Player::update(int dx, int dy) {
    x = dx;
    y = dy;
}

void Player::draw() {
    if (attack)
    {
        if (attackX > 1 && attackY == 0){
            al_draw_bitmap_region(imgAttack, 50 * attackX, 50 * attackY, 50, 50, x - 40,
                    y, 0);
        }
        else if (attackX < 2 && attackY == 0){
            al_draw_bitmap_region(imgAttack, 50 * attackX, 50 * attackY, 50, 50, x + 40,
                                  y, 0);
        }
        else if (attackX > 1 && attackY == 1){
            al_draw_bitmap_region(imgAttack, 50 * attackX, 50 * attackY, 50, 50, x,
                                  y - 40, 0);
        }
        else if (attackX < 2 && attackY == 1){
            al_draw_bitmap_region(imgAttack, 50 * attackX, 50 * attackY, 50, 50, x,
                                  y + 40, 0);
        }
    }

    al_draw_bitmap_region(image, 50 * down, 50 * 1, 50, 50, x, y, 0);

    timer();
}

void Player::timer(){
    animationTimer += 1;

    if (animationTimer % 20 == 0)
    {
        if (attackX % 2 == 0){
            attack = false;
        }
        attackX --;

        down += 1;
        if (down == 3){
            down = 0;
        }
    }
}

void Player::attacking(Enemy *enemy, int xdir, int ydir) {
    enemy->getDamage();

    if (xdir != -1){
        attackX = xdir;
        attackY = ydir;
    }
    attack = true;
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
    al_destroy_bitmap(imgAttack);
}
