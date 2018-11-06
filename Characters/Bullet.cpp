#include <allegro5/allegro.h>
#include <cmath>
#include "Bullet.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

Bullet::Bullet(Player *player, int lastX, int lastY) {
    ALLEGRO_SAMPLE *bowSound = al_load_sample("../resources/Arrow.wav");
    al_reserve_samples(1);
    al_play_sample(bowSound,6.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE,0 );

    this->arrow = al_load_bitmap("../resources/bowsprite.png");
    this->player = player;
    this->xi = player->getPosx() * 50;
    this->yi = player->getPosy() * 50;
    this->x = lastX;
    this->y = lastY;
    this->timer = 0;

    if (x - xi > 0)
        direction = 2;
    else if (x - xi < 0)
        direction = 1;
    else if (y - yi < 0)
        direction = 3;
    else if (y - yi > 0)
        direction = 4;
    else
        direction = 0;
}

void Bullet::draw() {
    int exp = 5 * int(pow((-1), direction));

    if (timer == 0)
        al_draw_bitmap_region(arrow, 0, 0, 50, 50, player->getPosx() * 50, player->getPosy() * 50, 0);
    if (direction > 2)
        yi = yi + exp;
    else if (direction < 3)
        xi = xi + exp;
    al_draw_bitmap_region(arrow, 0, 50 * direction, 50, 50, xi, yi, 0);

    if (x - xi == 0 && y - yi == 0)
        timer = 1;

}

int Bullet::getX() {
    return int(ceil(xi));
}

int Bullet::getY() {
    return int(ceil(yi));
}


int Bullet::getTimer() {
    return timer;
}

Bullet::~Bullet() {
    al_destroy_bitmap(arrow);
}
