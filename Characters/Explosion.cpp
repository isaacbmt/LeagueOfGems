#include <allegro5/allegro.h>
#include "Explosion.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

Explosion::Explosion(int x, int y) {
    boom = al_load_bitmap("../resources/boom.png");
    ALLEGRO_SAMPLE *ExplosionSound = al_load_sample("../resources/Boom.wav");
    al_reserve_samples(1);
    this->posx = x;
    this->posy = y;
    this->pivotX = 0;
    this->pivotY = 0;
}

Explosion::~Explosion() {
    al_destroy_bitmap(boom);
    ALLEGRO_SAMPLE *ExplosionSound = al_load_sample("../resources/Explosion.wav");
    al_reserve_samples(1);
    al_play_sample(ExplosionSound,6.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE,0 );

}

void Explosion::draw() {

    if (pivotY != 2){
        ALLEGRO_SAMPLE *ExplosionSound = al_load_sample("../resources/Explosion.wav");
        al_reserve_samples(1);

        al_draw_bitmap_region(boom, 50 * pivotX, 50 * pivotY, 50, 50, posx * 50, posy * 50, 0);
        al_play_sample(ExplosionSound,1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE,0 );

        if (animationTimer % 5 == 0) {
            pivotX++;
            if (pivotX == 4){
                pivotX = 0;
                pivotY++;
            }
        }
    }
    animationTimer++;
}

int Explosion::getPivotY() {
    return pivotY;
}
