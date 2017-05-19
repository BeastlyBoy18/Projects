#include <iostream>
using namespace std;
#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>
#include<allegro5\allegro_primitives.h>
#include"ghost.h"
#include "Globals.h"

int wallCollide(int x, int y, int dir, int level[20][20]);




int main()
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *pacman = NULL;
	ALLEGRO_BITMAP *wall = NULL;
	ALLEGRO_BITMAP *dots = NULL;
	ALLEGRO_FONT *font = NULL;

	//these two variables hold the x and y positions of the pacman
	//initalize these variables to where you want your pacman to start
	int pacman_x = 360;
	int pacman_y = 50;
	int pacscore = 0;
	int lives = 3;
	int dir = 0;

	//sprite variables!///////////////////////
	//Max Frames
	const int maxFrame = 4;
	//Start Frame
	int curFrame = 0;
	//Frame Counter
	int frameCount = 0;
	//Frame Delay
	int frameDelay = 6;
	//Sizing Sprites
	int frameWidth = 30;
	int frameHeight = 40;
	//here's our key states. they're all starting as "false" because nothing has been pressed yet.
	//the first slot represents "up", then "down", "left" and "right"
	bool key[4] = { false, false, false, false };

	//don't redraw until an event happens
	bool redraw = true;

	//this controls our game loop
	bool doexit = false;

	al_init();

	//get the keyboard ready to use
	al_install_keyboard();
	al_init_ttf_addon();
	al_init_font_addon();
	al_init_image_addon();
	al_init_primitives_addon();

	timer = al_create_timer(.02);

	display = al_create_display(800, 800);
	//Load Sheet
	pacman = al_load_bitmap("PacSprite.png");
	//Set Target
	//pacman = al_create_bitmap(30, 30);

	//al_set_target_bitmap(pacman);

	//al_clear_to_color(al_map_rgb(70, 70, 240));

	al_set_target_bitmap(al_get_backbuffer(display));

	wall = al_create_bitmap(39, 39);

	al_set_target_bitmap(wall);

	al_clear_to_color(al_map_rgb(235, 140, 140));

	al_set_target_bitmap(al_get_backbuffer(display));

	dots = al_create_bitmap(15, 15);

	al_set_target_bitmap(dots);

	al_clear_to_color(al_map_rgb(35, 140, 140));

	al_set_target_bitmap(al_get_backbuffer(display));


	event_queue = al_create_event_queue();
	font = al_load_ttf_font("Mermaid Swash Caps.ttf", 20, 0);

	//these lines tell teh event source what to look for
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	//Given Color Transparent 
	al_convert_mask_to_alpha(pacman, al_map_rgb(255, 255, 255));
	//new! tell the event queue that it should take keyboard events, too
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);

	//Matrix
	int map[20][20] = {
		1,1,0,0,1,1,0,0,1,1,0,1,0,0,1,1,0,0,1,1,
		0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,
		0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,
		1,1,2,1,1,1,1,2,1,2,2,1,1,1,1,1,1,2,1,1,
		1,1,2,1,2,2,2,2,1,2,2,1,2,2,2,2,1,2,1,1,
		0,1,2,1,2,1,1,1,1,2,2,1,2,1,1,2,1,2,1,0,
		0,1,2,1,2,2,2,2,2,2,2,2,2,2,1,2,1,2,1,0,
		1,1,2,1,2,1,2,1,1,2,2,1,1,2,1,2,2,2,1,1,
		1,1,2,1,2,1,2,2,1,2,2,1,2,2,1,1,1,2,1,1,
		0,2,2,2,2,2,2,2,1,1,1,1,2,2,2,2,2,2,2,0,
		0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,
		1,1,2,1,2,1,2,1,2,2,2,2,1,2,1,2,1,2,1,1,
		1,1,2,1,2,1,2,1,2,2,2,1,1,2,1,2,1,2,1,1,
		0,1,2,2,2,1,2,2,2,2,2,1,2,2,1,2,2,2,1,0,
		0,1,2,1,2,1,2,1,1,2,2,2,2,1,1,2,1,2,1,0,
		1,1,2,1,2,2,2,2,1,2,2,1,2,2,2,2,1,2,1,1,
		1,1,2,1,1,1,2,1,1,2,2,1,2,1,1,1,1,2,1,1,
		0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 };
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++)
			cout << map[i][j];
		cout << endl;
	}

	//initalize gosts
	ghost wendell;
	wendell.initghost(90, 90, 30, 30);
	ghost marty;
	marty.initghost(170, 170, 30, 30);
	ghost felipe;
	felipe.initghost(260, 350, 30, 30);
	ghost choxtor;
	choxtor.initghost(270, 260, 30, 30);
	//so the game loop is set to act on "ticks" of the timer OR keyboard presses
	//OR the mouse closing the display
	while (!doexit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//////////////////////////////////////////////////////////////////////////////////////////////////
		//here's the movement algorithm

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			//if the up button is pressed AND we're still below the top wall,
			//move the box "up" by 4 pixels
			if (key[0] && wallCollide(pacman_x, pacman_y, UP, map) == 0) {
				pacman_y -= 4.0;
				if (++frameCount >= frameDelay)
				{
					if (++curFrame >= maxFrame) //if you've walked off the end, go back to the beginning
						curFrame = 0;

					frameCount = 0; //reset frame timer
				}
			}

			//if the down button is pressed AND we're still above the bottom wall
			//move the box "down" by 4 pixels
			if (key[1] && wallCollide(pacman_x, pacman_y, DOWN, map) == 0) {
				pacman_y += 4.0;
				if (++frameCount >= frameDelay)
				{
					if (++curFrame >= maxFrame) //if you've walked off the end, go back to the beginning
						curFrame = 0;

					frameCount = 0; //reset frame timer
				}

			}
			//if the left button is pressed AND we're still right of the left wall
			//move the box left by 4 pixels
			if (key[2] && wallCollide(pacman_x, pacman_y, LEFT, map) == 0) {
				pacman_x -= 4.0;
				dir = LEFT;
				if (++frameCount >= frameDelay)
				{
					if (++curFrame >= maxFrame) //if you've walked off the end, go back to the beginning
						curFrame = 0;

					frameCount = 0; //reset frame timer
				}

			}


			//if the right button is pressed 
			//move the box right by 4 pixels
			if (key[3] && wallCollide(pacman_x, pacman_y, RIGHT, map) == 0) {
				pacman_x += 4.0;
				dir = RIGHT;
				//move sprite////////////////////////////////////////////////
				if (++frameCount >= frameDelay)
				{
					if (++curFrame >= maxFrame) //if you've walked off the end, go back to the beginning
						curFrame = 0;

					frameCount = 0; //reset frame timer
				}


				///////////////////////////////////////////////////////////////

			}




			if (map[(pacman_y + 20) / 40][(pacman_x + 20) / 40] == 2) {
				map[(pacman_y + 20) / 40][(pacman_x + 20) / 40] = 4; //4s 
				pacscore = pacscore + 5;
			}

			if (pacman_x > -40 && pacman_x < 0 && pacman_y > 0 && pacman_y < 800) {
				pacman_x = 760;
				pacman_y = 400;
			}
			if (pacman_x > 765 && pacman_x < 840 && pacman_y > 0 && pacman_y < 830) {
				pacman_x = 5;
				pacman_y = 400;
			}
			//Sprite Stuff


			//Kill Pac
			if (wendell.killpac(pacman_x, pacman_y) == 1) {
				pacman_y = 50;
				pacman_x = 360;
				lives -= 1;
				wendell.setPosition(90, 90);
			}
			if (marty.killpac(pacman_x, pacman_y) == 1) {
				pacman_y = 50;
				pacman_x = 360;
				lives -= 1;
				marty.setPosition(170, 170);
			}
			if (felipe.killpac(pacman_x, pacman_y) == 1) {
				pacman_y = 50;
				pacman_x = 360;
				lives -= 1;
				felipe.setPosition(260, 350);
			}
			if (choxtor.killpac(pacman_x, pacman_y) == 1) {
				pacman_y = 50;
				pacman_x = 360;
				lives -= 1;
				choxtor.setPosition(270, 260);
			}
			//chase stuff
			wendell.chase(pacman_x, pacman_y, map);
			marty.chase2(pacman_x, pacman_y, map);
			felipe.chase3(pacman_x, pacman_y, map);
			choxtor.chase(pacman_x, pacman_y, map);
			//redraw at every tick of the timer
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

				//if the up key has been pressed
			case ALLEGRO_KEY_UP:
				key[0] = true;
				break;

				//if the down key has been pressed
			case ALLEGRO_KEY_DOWN:
				key[1] = true;
				break;

				//if the left key has been pressed
			case ALLEGRO_KEY_LEFT:
				key[2] = true;
				break;

				//if the right key has been pressed
			case ALLEGRO_KEY_RIGHT:
				key[3] = true;
				break;
			}
		}
		//has something been released on the keyboard?
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

				//kill the program if someone presses escape
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}


		//RENDER SECTION

		//Draw bitmap region	

		//////////////////////////////////////////////////////////////////////////////////////////
		//if the clock ticked but no other events happened, don't bother redrawing
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			//paint black over the old screen, so the old pacman dissapears
			al_clear_to_color(al_map_rgb(40, 40, 40));
			//al_draw_bitmap(pacman, pacman_x, pacman_y, 0);

			//lives
			if (lives == 0) {
				break;
			}

			//al_draw_bitmap_region(pacman, curFrame * frameWidth, 0, frameWidth, frameHeight, pacman_x, pacman_y, 0);


			//al_draw_bitmap_region(WalkForward, curFrame * frameWidth, 0, frameWidth, frameHeight, x, y, 0);
			cout << "frameWidth is " << frameWidth << endl;

			if (dir == RIGHT) {
				al_draw_bitmap_region(pacman, curFrame * frameWidth, 0, frameWidth, frameHeight, pacman_x, pacman_y, 0);
				cout << "right Flag" << endl;
			}
			else if (dir == LEFT) {
				al_draw_bitmap_region(pacman, curFrame * frameWidth, 0, frameWidth, frameHeight, pacman_x, pacman_y, 1);
				cout << "LEft Flag" << endl;
			}

			//the algorithm above just changes the x and y coordinates
			//here's where the bitmap is actually drawn somewhere else
			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 20; j++)
					if (map[i][j] == 1)
						al_draw_bitmap(wall, j * 40, i * 40, NULL);
					else if (map[i][j] == 2)
						al_draw_bitmap(dots, j * 40 + 10, i * 40 + 15, NULL);
			}
			al_draw_textf(font, al_map_rgb(255, 255, 255), 600, 763, ALLEGRO_ALIGN_RIGHT, "Lives: %i", lives);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 100, 763, ALLEGRO_ALIGN_LEFT, "Score: %i", pacscore);
			if (pacscore == 890) {
				break;
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_textf(font, al_map_rgb(255, 255, 255), 540, 40, ALLEGRO_ALIGN_RIGHT, "GAME OVER");
			}

			//draw gosts
			wendell.draw();
			marty.draw();
			felipe.draw();
			choxtor.draw();
			al_flip_display();
		}

	}
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_rest(2);

	al_destroy_bitmap(pacman);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;

}
int ghost::setPosition(int x, int y) {

	xCoordinate = x;
	yCoordinate = y;

	return 0;
}
int wallCollide(int x, int y, int dir, int level[20][20]) {
	//cout << "collision function called" << endl;
	int new_x1, new_x2, new_x3, new_y1, new_y2, new_y3;
	/////////////////////////////////////////////////////////////////////////////////
	//RIGHT
	if (dir == RIGHT) {         // Moving Right
	//	cout << "right branch" << endl;			// Check along the far right side of the sprite, plus 3 (the amount we’re moving)
		new_x1 = x + 3 + PACSIZE;
		new_x2 = x + 3 + PACSIZE;
		new_x3 = x + 3 + PACSIZE;
		// Check at three point along that edge
		new_y1 = y;
		new_y2 = y + PACSIZE / 2;
		new_y3 = y + PACSIZE;

		//cout << "checking " << new_x1 / 40 << " , " << new_y1 / 40 << "which holds a " << level[new_x1 / 20][new_y1 / 20] << endl;
		if ((level[new_y1 / 40][new_x1 / 40] == 1) ||
			(level[new_y2 / 40][new_x2 / 40] == 1) ||//add the other two points here
			(level[new_y3 / 40][new_x3 / 40] == 1)) {
			//cout << "right collision" << endl;
			return 1;
		}
	}
	////////////////////////////////////////////////////////////////////////////////
	//LEFT
	if (dir == LEFT) {
		//	cout << "left branch" << endl;
		new_x1 = x - 3;
		new_x2 = x - 3;
		new_x3 = x - 3;

		new_y1 = y;
		new_y2 = y + PACSIZE / 2;
		new_y3 = y + PACSIZE;

		if ((level[new_y1 / 40][new_x1 / 40] == 1) ||
			(level[new_y2 / 40][new_x2 / 40] == 1) ||//add the other two points here
			(level[new_y3 / 40][new_x3 / 40] == 1)) {
			//cout << "left collision";
			return 1;
		}
	}
	if (dir == UP) {
		//	cout << "up branch" << endl;
		new_x1 = x;
		new_x2 = x + PACSIZE / 2;
		new_x3 = x + PACSIZE;

		new_y1 = y - 3;
		new_y2 = y - 3;
		new_y3 = y - 3;

		if ((level[new_y1 / 40][new_x1 / 40] == 1) ||
			(level[new_y2 / 40][new_x2 / 40] == 1) ||//add the other two points here
			(level[new_y3 / 40][new_x3 / 40] == 1)) {
			//cout << "UP collision";
			return 1;
		}
	}

	if (dir == DOWN) {
		//cout << "DOWN branch" << endl;
		new_x1 = x;
		new_x2 = x + PACSIZE / 2;
		new_x3 = x + PACSIZE;

		new_y1 = y + PACSIZE + 4;
		new_y2 = y + PACSIZE + 4;
		new_y3 = y + PACSIZE + 4;


		if ((level[new_y1 / 40][new_x1 / 40] == 1) ||
			(level[new_y2 / 40][new_x2 / 40] == 1) ||//add the other two points here
			(level[new_y3 / 40][new_x3 / 40] == 1)) {
			//cout << "DOWN collision";
			return 1;
		}
	}

	//return 0 when no collision occurs!
	return 0;
}
