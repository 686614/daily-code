#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h> 
#include <iostream>
using namespace std;
const int RIGHT = 3;
const int LEFT = 1;
const int UP = 2;
const int DOWN = 4;
/* Directions
1 = left
2 = up
3 = right
4 = down*/
int wallCollide(int x, int y, int dir, int map[21][20]);
bool Collision(int b1x, int b1y, int b2x, int b2y);

class Ghost {
private:
	int r;
	int g;
	int b;
	
	int width, height;

	int dir;
	bool dead;
	int direction;
public:
	void set_value(int x, int y, int w, int h);
	void drawGhost(int r, int g, int b);
	void killpacman();
	bool isDead();
	void chase(int x, int y, int field[20][20]);
	int xpos, ypos;
	char color;
};

int main() {
	ALLEGRO_DISPLAY*display = NULL;
	ALLEGRO_BITMAP*pacman = NULL;
	ALLEGRO_BITMAP*wall = NULL;
	ALLEGRO_BITMAP*dot = NULL;
	ALLEGRO_EVENT_QUEUE*event_queue = NULL;
	ALLEGRO_TIMER*timer = NULL;
	int pacman_x = 384;
	int pacman_y = 364;
	bool doexit = false;
	bool key[4]{ false, false, false, false };
	bool redraw = true;
	al_init();
	al_init_primitives_addon();
	int map[21][20]{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 1, 1, 1, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1,
		0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
		1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1,
		1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1,
	};
	al_install_keyboard();
	timer = al_create_timer(.02);
	event_queue = al_create_event_queue();
	display = al_create_display(800, 840);
	pacman = al_create_bitmap(32, 32);
	wall = al_create_bitmap(40, 40);
	dot = al_create_bitmap(4, 4);
	al_set_target_bitmap(pacman);
	al_clear_to_color(al_map_rgb(255, 255, 0));
	al_set_target_bitmap(wall);
	al_clear_to_color(al_map_rgb(127, 0, 255));
	al_set_target_bitmap(dot);
	al_clear_to_color(al_map_rgb(255, 255, 0));
	al_set_target_bitmap(al_get_backbuffer(display));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));


	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);

	//create ghosts
	Ghost inky;
	inky.set_value(200, 200, 30, 30);

	Ghost blinky;
	blinky.set_value(250, 100, 30, 30);

	Ghost pinky;
	pinky.set_value(120, 140, 30, 30);

	Ghost clyde;
	clyde.set_value(200, 100, 30, 30);

	while (!doexit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		//cout << "flag1" << endl;

		if (ev.type == ALLEGRO_EVENT_TIMER) {

			if (Collision(pacman_x, pacman_y, inky.xpos, inky.ypos) == 1) {
				//play sad sound effect
				//wipe screen
				//write insulting message
				//flip display
				//al_rest02
				return 0;
				if (Collision(pacman_x, pacman_y, pinky.xpos, pinky.ypos) == 1) {
					//play sad sound effect
					//wipe screen
					//write insulting message
					//flip display
					//al_rest
					return 0;
					if (Collision(pacman_x, pacman_y, blinky.xpos, blinky.ypos) == 1) {
						//play sad sound effect
						//wipe screen
						//write insulting message
						//flip display
						//al_rest
						//return 0;
						if (Collision(pacman_x, pacman_y, clyde.xpos, clyde.ypos) == 1) {
				//play sad sound effect
				//wipe screen
				//write insulting message
				//flip display
				//al_rest
				return 0;


			}
			//pacman move up
			if (key[0] && wallCollide(pacman_x, pacman_y, UP, map) == 0) {
				pacman_y -= 4.0;
			}

			//down
			if (key[1] && wallCollide(pacman_x, pacman_y, DOWN, map) == 0) {
				pacman_y += 4.0;
			}
			//left
			if (key[2] && wallCollide(pacman_x, pacman_y, LEFT, map) == 0) {
		
				pacman_x -= 4.0;

			}

			//right
			if (key[3] && wallCollide(pacman_x, pacman_y, RIGHT, map) == 0) {
				pacman_x += 4.0;
			}


			if (map[(pacman_y + 16) / 40][(pacman_x + 16) / 40] == 0) {
				map[(pacman_y + 16) / 40][(pacman_x + 16) / 40] = 2;

			}
			//chase pacman

			inky.chase(pacman_x, pacman_y,map);

			blinky.chase(pacman_x, pacman_y, map);


			pinky.chase(pacman_x, pacman_y, map);

			clyde.chase(pacman_x, pacman_y, map);
			//it's simple, we kill the pacman.
			//if(inky.killpac() == 1)
			//end game or reduce lives or something.

			redraw = true;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}



		//////////////////////////////////////////////////////////////////////////////////////////////////////


		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {


			switch (ev.keyboard.keycode) {


			case ALLEGRO_KEY_UP:
				key[0] = true;
				break;


			case ALLEGRO_KEY_DOWN:
				key[1] = true;
				break;


			case ALLEGRO_KEY_LEFT:
				
				key[2] = true;
				break;


			case ALLEGRO_KEY_RIGHT:
				key[3] = true;
				break;
			}
		}

		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[0] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[1] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				
				key[2] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[3] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}

		//RENDER SECTION............................................................
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;


			al_clear_to_color(al_map_rgb(0, 0, 0));


			for (int i = 0; i < 20; i++)
				for (int j = 0; j < 21; j++)
					if (map[j][i] == 1)
						al_draw_bitmap(wall, i * 40, j * 40, 0);
					else if (map[j][i] == 0)
						al_draw_bitmap(dot, i * 40 + 18, j * 40 + 18, 0);


			al_draw_bitmap(pacman, pacman_x, pacman_y, 0);

			//draw ghosts
			inky.drawGhost(0,255,255);
			blinky.drawGhost(255,0,0);
			pinky.drawGhost(255,51,255); 
			clyde.drawGhost(255,128,0);

			al_flip_display();


		}
	}
	
	al_destroy_bitmap(pacman);
	al_destroy_bitmap(wall);
	al_destroy_bitmap(dot);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}


int wallCollide(int x, int y, int dir, int map[21][20]) {
	
	int new_x1;
	int new_x2;
	int new_x3;
	int new_y1;
	int new_y2;
	int new_y3;
	if (dir == RIGHT) {
		new_x1 = x + 6 + 32;
		new_x2 = x + 6 + 32;
		new_x3 = x + 6 + 32;
		new_y1 = y;
		new_y2 = y + 32 / 2;
		new_y3 = y + 32;
	}
	else if (dir == LEFT) {
		cout << "direction is left" << endl;
		new_x1 = x - 6;
		new_x2 = x - 6;
		new_x3 = x - 6;
		new_y1 = y;
		new_y2 = y + 32 / 2;
		new_y3 = y + 32;
	}
	else if (dir == UP) {
		new_x1 = x;
		new_x2 = x + 32 / 2;
		new_x3 = x + 32;
		new_y1 = y - 3;
		new_y2 = y - 3;
		new_y3 = y - 3;
	}
	else if (dir == DOWN) {
		new_x1 = x;
		new_x2 = x + 32 / 2;
		new_x3 = x + 32;
		new_y1 = y + 32 + 6;
		new_y2 = y + 32 + 6;
		new_y3 = y + 32 + 6;
	}

	
	if ((map[new_y1 / 40][new_x1 / 40] == 1) || (map[new_y2 / 40][new_x2 / 40] == 1) || (map[new_y3 / 40][new_x3 / 40] == 1)) {
		
		return 1;

	}



	else {
		
		return 0;//no collision

	}
	return 0;
}
 
void Ghost::set_value(int x, int y, int w, int h) {
	xpos = x;
	ypos = y;
	width = w;
	height = h;
	dead = false;
	direction = LEFT;
}

void Ghost::drawGhost(int r, int g, int b) {

	//cout << "ghost info is" << xpos << " , " << ypos << " , " << width << " , " << height << endl;
	al_draw_filled_rectangle(xpos, ypos, xpos + width, ypos + height, al_map_rgb(r, g, b));

}

bool Ghost::isDead() {
	return dead;
}
//chase function. x and y are pacman's position.
void Ghost::chase(int x, int y, int field[20][20]) {


	/* Directions
	1 = left
	2 = up
	3 = right
	4 = down*/

	//this is just for testing
	/*  cout << "state is " << direction << endl;
	if (wallCollide(xpos, ypos, 1, field))
	cout << "there's a wall to the left of me" << endl;
	if (wallCollide(xpos, ypos, 2, field))
	cout << "there's a wall above me" << endl;
	if (wallCollide(xpos, ypos, 3, field))
	cout << "there's a wall to the right of me" << endl;
	if (wallCollide(xpos, ypos, 4, field))
	cout << "there's a wall below me" << endl;*/

	/////////////////////////////////LEFT STATE (1)//////////////////////////////////////////////////////////////////

	//if we're moving left and there's an opening above and pacman is above, move up
	if ((direction == LEFT) && !wallCollide(xpos, ypos, UP, field) && y<ypos)
		while (!wallCollide(xpos, ypos, 2, field)) {
			// cout << "trying to move through hole above!" << endl;
			direction = UP;
			ypos -= 4;
			return;
		}

	//if we're moving left and there's an opening below and pacman is below, move down
	if ((direction == LEFT) && !wallCollide(xpos, ypos, DOWN, field) && y>ypos)
		while (!wallCollide(xpos, ypos, 4, field)) {
			//  cout << "trying to move through hole below!" << endl;
			direction = DOWN;
			ypos += 4;
			return;
		}


	if (direction == LEFT)//left
		while (!wallCollide(xpos, ypos, LEFT, field)) {
			xpos -= 4;
			return;
		}

	////////////////////////////////UP STATE (2)///////////////////////////////////////////////////////////////

	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == UP) && !wallCollide(xpos, ypos, LEFT, field) && x<xpos)
		while (!wallCollide(xpos, ypos, LEFT, field)) {
			//   cout << "trying to move through hole to left!" << endl;
			direction = LEFT;
			xpos -= 4;
			return;
		}
	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xpos, ypos, RIGHT, field) && x>xpos)
		while (!wallCollide(xpos, ypos, 3, field)) {
			// cout << "trying to move through hole to right!" << endl;
			direction = RIGHT;
			xpos += 4;
			return;
		}
	if (direction == UP)//up
		while (!wallCollide(xpos, ypos, 2, field)) {
			ypos -= UP;
			return;
		}

	/////////RIGHT CASE (3)/////////////////////////////////////////////////////////////////////////////////////////////////////
	//if we're moving right and there's an opening above and pacman is above, move up
	if ((direction == RIGHT) && !wallCollide(xpos, ypos, UP, field) && y<ypos)
		while (!wallCollide(xpos, ypos, 2, field)) {
			//   cout << "trying to move through hole above!" << endl;
			direction = UP;
			ypos -= 2;
			return;
		}

	//if we're moving right and there's an opening below and pacman is below, move down
	if ((direction == RIGHT) && !wallCollide(xpos, ypos, DOWN, field) && y>ypos)
		while (!wallCollide(xpos, ypos, DOWN, field)) {
			//  cout << "trying to move through hole below!" << endl;
			direction = DOWN;
			ypos += 2;
			return;
		}


	if (direction == RIGHT)//right
		while (!wallCollide(xpos, ypos, RIGHT, field)) {
			xpos += 2;
			return;
		}


	//////////////DOWN CASE (4)/////////////////////////////////////////////////////////////////////////////////////
	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == DOWN) && !wallCollide(xpos, ypos, LEFT, field) && x<xpos)
		while (!wallCollide(xpos, ypos, LEFT, field)) {
			// cout << "trying to move through hole to left!" << endl;
			direction = LEFT;
			xpos -= 2;
			return;
		}
	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xpos, ypos, RIGHT, field) && x>xpos)
		while (!wallCollide(xpos, ypos, RIGHT, field)) {
			//   cout << "trying to move through hole to right!" << endl;
			direction = RIGHT;
			xpos += 2;
			return;
		}

	if (direction == DOWN)//down
		while (!wallCollide(xpos, ypos, DOWN, field)) {
			ypos += 2;
			return;
		}





	///////////////////////////////////////////////////////////////////////////////////////
	//if pacman is above and there's no wall there, move up
	if ((y<ypos) && !wallCollide(xpos, ypos, UP, field)) {
		//  cout << "direction is up" << endl;
		direction = UP;
		return;
	}


	//if pacman is below and there's no wall there, move down
	if ((y>ypos) && !wallCollide(xpos, ypos, DOWN, field)) {
		direction = DOWN;
		//   cout << "direction is down" << endl;
		return;
	}

	//if pacman is right and there's no wall there, move right
	if ((x>xpos) && !wallCollide(xpos, ypos, RIGHT, field)) {
		direction = RIGHT;
		//  cout << "direction is right" << endl;
		return;
	}

	//if pacman is left and there's no wall there, move left
	if ((x<xpos) && !wallCollide(xpos, ypos, LEFT, field)) {
		direction = LEFT;
		// cout << "direction is left" << endl;
		return;

	}

	//if pacman is above and there's no wall there, move up
	if (!wallCollide(xpos, ypos, UP, field)) {
		// cout << "direction is up" << endl;
		direction = UP;
		return;
	}


	//if pacman is below and there's no wall there, move down
	if (!wallCollide(xpos, ypos, DOWN, field)) {
		direction = DOWN;
		//cout << "direction is down" << endl;
		return;
	}

	//if pacman is right and there's no wall there, move right
	if (!wallCollide(xpos, ypos, RIGHT, field)) {
		direction = RIGHT;
		//  cout << "direction is right" << endl;
		return;

	}

	//if pacman is left and there's no wall there, move left
	if (!wallCollide(xpos, ypos, LEFT, field)) {
		direction = LEFT;
		// cout << "direction is left" << endl;
		return;


	}

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
