#include <stdio.h>
#include <allegro5/allegro.h>
#include <iostream>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
using namespace std;
bool Collision(int b1x, int b1y, int b2x, int b2y);

int main()
{
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *padle = NULL;
	ALLEGRO_BITMAP *padle2 = NULL;
	ALLEGRO_BITMAP *ball = NULL;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_BITMAP *image = NULL;

	//here's the bouncer's x and y coordinates on the screen
	float padle_x = 30;
	float padle_y = 30;
	float padle2_x = 400;
	float padle2_y = 400;
	float ball_x = 90;
	float ball_y = 90;
	float ball_dx = -4.0, ball_dy = 4.0;

	al_init();

	al_init_image_addon();

	al_init_primitives_addon();

	timer = al_create_timer(.02);

	display = al_create_display(640, 480);

	al_clear_to_color(al_map_rgb(0, 0, 0));

	//here's our key states. they're all starting as "false" because nothing has been pressed yet.
	//the first slot represents "up", then "down", "left" and "right"
	//key2 represents"w","a","s","d"
	bool key[2] = { false, false, };

	bool key2[2] = { false, false, };
	bool redraw = true;

	//this controls our game loop
	bool doexit = false;

	al_init();

	//get the keyboard ready to use
	al_install_keyboard();

	timer = al_create_timer(.02);

	/////
	display = al_create_display(640, 480);
	////////ball
	ball = al_load_bitmap("IronShell.jpg");
	al_convert_mask_to_alpha(ball, al_map_rgb(0, 0, 0));
	if (ball == NULL)
		cout << "WTF" << endl;

	image = al_load_bitmap("potatoes.jpg");

	al_clear_to_color(al_map_rgb(255, 255, 255));
	////
	padle = al_create_bitmap(180, 32);

	al_set_target_bitmap(padle);

	al_clear_to_color(al_map_rgb(255, 255, 255));
	////padle 2
	padle2 = al_create_bitmap(180, 32);

	al_set_target_bitmap(padle2);

	al_clear_to_color(al_map_rgb(0, 100, 100));

	al_set_target_bitmap(al_get_backbuffer(display));

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	//tell the event queue that it should take keyboard events, too 
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);

	//so the game loop is set to act on "ticks" of the timer OR keyboard presses 
	//OR the mouse closing the display
	while (!doexit)
	{
		cout << "flag1" << endl;
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//////////////////////////////////////////////////////////////////////////////////////////////////
		//here's the movement algorithm

		if (ev.type == ALLEGRO_EVENT_TIMER) {

			//if the left button is pressed AND we're still right of the left wall
			//move the box left by 4 pixels
			if (key[0] && padle_x >= 0) {
				padle_x -= 9.0;
			}

			//if the right button is pressed AND we're still left of the right wall
			//move the box right by 4 pixels
			if (key[1] && padle_x <= 640 - 32) {
				padle_x += 9.0;
				
			}

			if (ball_x < 0 || ball_x > 640 - 32) {
				//flip the x direction
				ball_dx = -ball_dx;
			}

			//redraw at every tick of the timer
			redraw = true;

			if (key2[0] && padle2_x >= 0) {
				padle2_x -= 9.0;
			}

			if (key2[1] && padle2_x <= 640 - 32) {
				padle2_x += 9.0;
			}
			//if the box hits the top wall OR the bottom wall
			if (ball_y < 0 || ball_y > 480 - 32) {
				//flip the y direction
				ball_dy = -ball_dy;
			}
			if (padle2_x <= ball_x)
				padle2_x += 10;
			if (padle2_x >= ball_x)
				padle2_x -= 10;
			//really important code!
			//move the box in a diagonal
			ball_x += ball_dx;
			ball_y += ball_dy;

			if (Collision( padle_x, padle_y, ball_x, ball_y) == 1)
				ball_dy = -ball_dy;

			if (Collision(padle2_x, padle2_y, ball_x, ball_y) == 1)
				ball_dy = -ball_dy;


			redraw = true;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////
		//here's the algorithm that turns key presses into events
		//a "key down" event is when a key is pushed
		//while a "key up" event is when a key is released

		//has something been pressed on the keyboard?
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {

			//"keycode" holds all the different keys on the keyboard
			switch (ev.keyboard.keycode) {

				//if the left key has been pressed
			case ALLEGRO_KEY_LEFT:
				key[0] = true;
				break;

				//if the right key has been pressed
			case ALLEGRO_KEY_RIGHT:
				key[1] = true;
				break;

			case ALLEGRO_KEY_A:
				key2[0] = true;
				break;

			case ALLEGRO_KEY_D:
				key2[1] = true;
				break;
			}
		}
		//has something been released on the keyboard?
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {

			case ALLEGRO_KEY_LEFT:
				key[0] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[1] = false;
				break;

			case ALLEGRO_KEY_A:
				key2[0] = false;
				break;

			case ALLEGRO_KEY_D:
				key2[1] = false;
				break;

				//kill the program if someone presses escape
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;

			}

		}

		al_clear_to_color(al_map_rgb(0, 0, 0));
		//if the clock ticked but no other events happened, don't bother redrawing
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			//paint black over the old screen, so the old square dissapears
			al_clear_to_color(al_map_rgb(0, 0, 0));

			//the algorithm above just changes the x and y coordinates
			//here's where the bitmap is actually drawn somewhere else
			al_draw_bitmap(image, 0, 0, 0);
			al_draw_bitmap(padle, padle_x, padle_y, 0);

			al_draw_bitmap(padle2, padle2_x, padle2_y, 0);
			cout << "flag 2" << endl;
			al_draw_bitmap(ball, ball_x, ball_y, 0);
			cout << "flag 3";
			
			cout << "flag 4";
			al_flip_display();

		}
	}//end game loop

	al_destroy_bitmap(padle);
	al_destroy_bitmap(padle2);
	al_destroy_bitmap(ball);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;

}
bool Collision(int b1x, int b1y, int b2x, int b2y) {

	if ((b1x + 180 < b2x) ||
		(b1x > b2x + 25) ||
		(b1y > b2y + 25) ||
		(b1y + 32 < b2y)

		)

		return 0;
	else {
		printf("collision!");
		return 1;
	}
}