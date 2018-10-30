#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <iostream>
#include "GameLevels/Game.h"

int main(int argc, char **argv){
    ALLEGRO_DISPLAY *display;
    bool running = false;

    if(!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    display = al_create_display(1350, 1050);

    if(!display) {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }

    al_set_window_position(display, 600, 500);

    al_init_image_addon();
    al_init_primitives_addon();

    al_install_audio();
    al_init_acodec_addon();

    al_install_mouse();
    al_install_keyboard();

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60);
    ALLEGRO_TIMER *drawTimer = al_create_timer(1.0 / 60);
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(drawTimer));

    al_start_timer(timer);
    al_start_timer(drawTimer);

    Game *game = new Game;
    int x = 1150, y = 850;

    ALLEGRO_BITMAP *horse = al_load_bitmap("../resources/horse.png");

    while (!running){
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);

        if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            running = true;
        }
        else if(events.type == ALLEGRO_EVENT_TIMER)
        {
            if (events.timer.source == timer)
            {
                // Update
                game->update();

                ALLEGRO_MOUSE_STATE state;
                al_get_mouse_state(&state);

                if (state.buttons & 1) {
                    x = state.x;
                    y = state.y;
                }
                else if (state.buttons & 2) {
                    // GreedyAlgorithms
                    x = state.x;
                    y = state.y;

                    cout << "Pathfindeo" << endl;

                    int posx = x / 50;
                    int posy = y / 50;

                    cout << "Mover hacia: " << "[" << posx << ", " << posy << "]" << endl;
                    game->updateCenter(posx,posy);//Aqui se recalcula el nodo al que tiene q llegar el personaje
                }

                if (events.type == ALLEGRO_EVENT_MOUSE_AXES ){
                    x = events.mouse.x;
                    y = events.mouse.y;
                }
            }

            else if (events.timer.source == drawTimer)
            {
                // Draw
                al_clear_to_color(al_map_rgb(62, 240, 98));
                game->draw();
                //al_draw_bitmap(horse, (1350 / 2) - 105, (1050 / 2) - 130, 0);
                al_flip_display();
            }
        }
    }

    delete game;
    al_destroy_display(display);
    al_uninstall_mouse();
    al_uninstall_keyboard();
    al_destroy_event_queue(event_queue);
    return 0;
}