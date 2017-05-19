#include <allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include<iostream>
using namespace std;

//class definition goes here
class Brick {
public:
	Brick();
	void initBrick(int x, int y, int w, int h);
	void draw();
	bool isDead();
	int BrickCollision(int bouncer_x, int bouncer_y);
	void killBrick();
private:
	int xCoordinate;
	int yCoordinate;
	int width;
	int height;
	bool Dead;
};

int collision(int PaddleL_x, int PaddleL_y, int bouncer_x, int bouncer_y);
int main() {
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *PaddleL = NULL;
	ALLEGRO_BITMAP *bouncer = NULL;
	ALLEGRO_BITMAP *ball = NULL;
	//Second Ball
	ALLEGRO_FONT *font = NULL;
	ALLEGRO_SAMPLE *sample = NULL;
	ALLEGRO_SAMPLE *sample2 = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instance = NULL;

	int lives = 3;
	int score = 0;

	float PaddleL_x = 250;
	float PaddleL_y = 450;

	float bouncer_x = 150;
	float bouncer_y = 150;

	float ball_x = 230;
	float ball_y = 150;
	//Second Ball

	float bouncer_dx = -5.0, bouncer_dy = 5.0;   
	float ball_dx = -5.0, ball_dy = 5.0;
	//Second Ball

	bool key[2] = { false, false };

	bool redraw = true;

	bool doexit = false;
	al_init();

	al_install_keyboard();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(2);
	sample = al_load_sample("Drop.wav");
	if (sample == NULL)
		cout << "didn't load yo" << endl;

	sample2 = al_load_sample("Cricket.wav");

	//instance = al_create_sample_instance(sample2);

	timer = al_create_timer(.02);

	display = al_create_display(640, 480);

	PaddleL = al_create_bitmap(100, 32);
	al_set_target_bitmap(PaddleL);
	al_clear_to_color(al_map_rgb(250, 251, 10));
	bouncer = al_create_bitmap(32, 32);
	al_set_target_bitmap(bouncer);
	al_clear_to_color(al_map_rgb(10, 160, 240));
	ball = al_create_bitmap(32, 32);
	al_set_target_bitmap(ball);
	al_clear_to_color(al_map_rgb(28, 100, 233));

	al_set_target_bitmap(al_get_backbuffer(display));

	al_clear_to_color(al_map_rgb(200, 51, 0));

	event_queue = al_create_event_queue();
	
	//Load Font
	font = al_load_ttf_font("Mermaid Swash Caps.ttf", 20, 0);

	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);


	//instantiate and initialize bricks
	Brick b1;
	b1.initBrick(0, 0, 70, 35);

	Brick b2;
	b2.initBrick(85, 0, 75, 35);

	Brick b3;
	b3.initBrick(180, 0, 75, 35);

	Brick b4;
	b4.initBrick(280, 0, 75, 35);

	Brick b5;
	b5.initBrick(380, 0, 75, 35);

	Brick b6;
	b6.initBrick(480, 0, 75, 35);

	Brick b7;
	b7.initBrick(580, 0, 55, 35);

	Brick b8;
	b8.initBrick(30, 36, 80, 35);

	Brick b9;
	b9.initBrick(130, 36, 80, 35);

	Brick b10;
	b10.initBrick(230, 36, 80, 35);

	Brick b11;
	b11.initBrick(330, 36, 80, 35);

	Brick b12;
	b12.initBrick(430, 36, 80, 35);

	Brick b13;
	b13.initBrick(530, 36, 80, 35);

	Brick b14;
	b14.initBrick(0, 80, 65, 35);

	Brick b15;
	b15.initBrick(85, 80, 70, 35);

	Brick b16;
	b16.initBrick(180, 80, 75, 35);

	Brick b17;
	b17.initBrick(280, 80, 75, 35);

	Brick b18;
	b18.initBrick(380, 80, 75, 35);

	Brick b19;
	b19.initBrick(480, 80, 75, 35);

	Brick b20;
	b20.initBrick(580, 80, 70, 35);


	al_play_sample(sample2, 1.0, 1.0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);
	//cout << "flag2" << endl;
	while (!doexit)

	{
		//cout << timer << endl;
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			
			//cout << "flag1";
			//if the box hits the left wall OR the right wall
			if (bouncer_x < 0 || bouncer_x > 640 - 32) {
				//flip the x direction
				bouncer_dx = -bouncer_dx;
				//Second Ball
			}
			
			//if the box hits the top wall OR the bottom wall
			if (bouncer_y < 0 || bouncer_y > 480 - 32) {
				//flip the y direction
				bouncer_dy = -bouncer_dy;
				//Second Ball
			}
			bouncer_x += bouncer_dx;
			bouncer_y += bouncer_dy;

			if (ball_x < 0 || ball_x > 640 - 32) {
				//flip the x direction
				ball_dx = -ball_dx;
				//Second Ball
			}

			//if the box hits the top wall OR the bottom wall
			if (ball_y < 0 || ball_y > 480 - 32) {
				//flip the y direction
				ball_dy = -ball_dy;
				//Second Ball
			}
			ball_x += ball_dx;
			ball_y += ball_dy;

			//move the box "up" by 4 pixels
			//if the left button is pressed AND we're still right of the left wall
			//move the box left by 4 pixels
			if (key[0] && PaddleL_x >= 0) {
				PaddleL_x -= 6.0;
			}

			//if the left button is pressed AND we're still left of the right wall
			//move the box right by 4 pixels
			if (key[1] && PaddleL_x <= 640 - 90) {
				PaddleL_x += 6.0;
			}



			if (collision(PaddleL_x, PaddleL_y, bouncer_x, bouncer_y)) {
				bouncer_dy = -bouncer_dy;
				al_play_sample(sample, 1.0, 1.0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				cout << "boing!";

			}
			if (collision(PaddleL_x, PaddleL_y, ball_x, ball_y)) {
				ball_dy = -ball_dy;
			}
			if (bouncer_x >- 0 && bouncer_x <= 640 && bouncer_y <= 460 && bouncer_y >= 450) {
				bouncer_x = 150;
				bouncer_y = 125;
				lives--;
		}


			if (b1.BrickCollision(bouncer_x, bouncer_y) && b1.isDead() == false) {
				b1.killBrick();
				bouncer_dy = -bouncer_dy;
				score = score + 10;
			}
			if (b2.BrickCollision(bouncer_x, bouncer_y ) && b2.isDead() == false) {
				b2.killBrick();
				bouncer_dy = -bouncer_dy;
				score = score + 10;
			}
			if (b3.BrickCollision(bouncer_x, bouncer_y ) && b3.isDead() == false) {
				b3.killBrick();
				bouncer_dy = -bouncer_dy;
				
				score = score + 10;
			}
			if (b4.BrickCollision(bouncer_x, bouncer_y ) && b4.isDead() == false) {
				b4.killBrick();
				bouncer_dy = -bouncer_dy;
				
				score = score + 10;
			}
			if (b5.BrickCollision(bouncer_x, bouncer_y ) && b5.isDead() == false) {
				b5.killBrick();
				bouncer_dy = -bouncer_dy;
				
				score = score + 10;
			}
			if (b6.BrickCollision(bouncer_x, bouncer_y) && b6.isDead() == false) {
				b6.killBrick();
				bouncer_dy = -bouncer_dy;
				
				score = score + 10;
			}
			if (b7.BrickCollision(bouncer_x, bouncer_y ) && b7.isDead() == false) {
				b7.killBrick();
				bouncer_dy = -bouncer_dy;
				
				score = score + 10;
			}
			if (b8.BrickCollision(bouncer_x, bouncer_y ) && b8.isDead() == false) {
				b8.killBrick();
				bouncer_dy = -bouncer_dy;
				
				score = score + 10;
			}
			if (b9.BrickCollision(bouncer_x, bouncer_y ) && b9.isDead() == false) {
				b9.killBrick();
				bouncer_dy = -bouncer_dy;
				
				score = score + 10;
			}
			if (b10.BrickCollision(bouncer_x, bouncer_y ) && b10.isDead() == false) {
				b10.killBrick();
				bouncer_dy = -bouncer_dy;
				
				score = score + 10;
			}
			if (b11.BrickCollision(bouncer_x, bouncer_y ) && b11.isDead() == false) {
				b11.killBrick();
				bouncer_dy = -bouncer_dy;
				score = score + 10;
			}
			if (b12.BrickCollision(bouncer_x, bouncer_y ) && b12.isDead() == false) {
				b12.killBrick();
				bouncer_dy = -bouncer_dy;
				
				score = score + 10;
			}
			if (b13.BrickCollision(bouncer_x, bouncer_y ) && b13.isDead() == false) {
				b13.killBrick();
				bouncer_dy = -bouncer_dy;
				
				score = score + 10;
			}
			if (b14.BrickCollision(bouncer_x, bouncer_y ) && b14.isDead() == false) {
				b14.killBrick();
				bouncer_dy = -bouncer_dy;
				
				score = score + 10;
			}
			if (b15.BrickCollision(bouncer_x, bouncer_y ) && b15.isDead() == false) {
				b15.killBrick();
				bouncer_dy = -bouncer_dy;
				
				score = score + 10;
			}
			if (b16.BrickCollision(bouncer_x, bouncer_y) && b16.isDead() == false) {
				b16.killBrick();
				bouncer_dy = -bouncer_dy;
				
				score = score + 10;
			}
			if (b17.BrickCollision(bouncer_x, bouncer_y ) && b17.isDead() == false) {
				b17.killBrick();
				bouncer_dy = -bouncer_dy;
				score = score + 10;
			}
			if (b18.BrickCollision(bouncer_x, bouncer_y) && b18.isDead() == false) {
				b18.killBrick();
				bouncer_dy = -bouncer_dy;
				
				score = score + 10;
			}
			if (b19.BrickCollision(bouncer_x, bouncer_y ) && b19.isDead() == false) {
				b19.killBrick();
				bouncer_dy = -bouncer_dy;
				
				score = score + 10;
			}
			if (b20.BrickCollision(bouncer_x, bouncer_y ) && b20.isDead() == false) {
				b20.killBrick();
				bouncer_dy = -bouncer_dy;
				
				score = score + 10;
			}

			if (b1.BrickCollision(ball_x, ball_y) && b1.isDead() == false) {
				b1.killBrick();
				ball_dy = -ball_dy;
				score = score + 10;
			}
			if (b2.BrickCollision(ball_x, ball_y) && b2.isDead() == false) {
				b2.killBrick();
				ball_dy = -ball_dy;
				score = score + 10;
			}
			if (b3.BrickCollision(ball_x, ball_y) && b3.isDead() == false) {
				b3.killBrick();
				ball_dy = -ball_dy;

				score = score + 10;
			}
			if (b4.BrickCollision(ball_x, ball_y) && b4.isDead() == false) {
				b4.killBrick();
				ball_dy = -ball_dy;

				score = score + 10;
			}
			if (b5.BrickCollision(ball_x, ball_y) && b5.isDead() == false) {
				b5.killBrick();
				ball_dy = -ball_dy;

				score = score + 10;
			}
			if (b6.BrickCollision(ball_x, ball_y) && b6.isDead() == false) {
				b6.killBrick();
				ball_dy = -ball_dy;

				score = score + 10;
			}
			if (b7.BrickCollision(ball_x, ball_y) && b7.isDead() == false) {
				b7.killBrick();
				ball_dy = -ball_dy;

				score = score + 10;
			}
			if (b8.BrickCollision(ball_x, ball_y) && b8.isDead() == false) {
				b8.killBrick();
				ball_dy = -ball_dy;

				score = score + 10;
			}
			if (b9.BrickCollision(ball_x, ball_y) && b9.isDead() == false) {
				b9.killBrick();
				ball_dy = -ball_dy;

				score = score + 10;
			}
			if (b10.BrickCollision(ball_x, ball_y) && b10.isDead() == false) {
				b10.killBrick();
				ball_dy = -ball_dy;

				score = score + 10;
			}
			if (b11.BrickCollision(ball_x, ball_y) && b11.isDead() == false) {
				b11.killBrick();
				ball_dy = -ball_dy;
				score = score + 10;
			}
			if (b12.BrickCollision(ball_x, ball_y) && b12.isDead() == false) {
				b12.killBrick();
				ball_dy = -ball_dy;

				score = score + 10;
			}
			if (b13.BrickCollision(ball_x, ball_y) && b13.isDead() == false) {
				b13.killBrick();
				ball_dy = -ball_dy;

				score = score + 10;
			}
			if (b14.BrickCollision(ball_x, ball_y) && b14.isDead() == false) {
				b14.killBrick();
				ball_dy = -ball_dy;

				score = score + 10;
			}
			if (b15.BrickCollision(ball_x, ball_y) && b15.isDead() == false) {
				b15.killBrick();
				ball_dy = -ball_dy;

				score = score + 10;
			}
			if (b16.BrickCollision(ball_x, ball_y) && b16.isDead() == false) {
				b16.killBrick();
				ball_dy = -ball_dy;

				score = score + 10;
			}
			if (b17.BrickCollision(ball_x, ball_y) && b17.isDead() == false) {
				b17.killBrick();
				ball_dy = -ball_dy;
				score = score + 10;
			}
			if (b18.BrickCollision(ball_x, ball_y) && b18.isDead() == false) {
				b18.killBrick();
				ball_dy = -ball_dy;

				score = score + 10;
			}
			if (b19.BrickCollision(ball_x, ball_y) && b19.isDead() == false) {
				b19.killBrick();
				ball_dy = -ball_dy;

				score = score + 10;
			}
			if (b20.BrickCollision(ball_x, ball_y) && b20.isDead() == false) {
				b20.killBrick();
				ball_dy = -ball_dy;

				score = score + 10;
			}


			redraw = true;
			
		}
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

			case ALLEGRO_KEY_A:
				key[0] = true;
				break;

			case ALLEGRO_KEY_D:
				key[1] = true;
				break;

			}
			
		}
		//has something been released on the keyboard?
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			
			switch (ev.keyboard.keycode) {


			case ALLEGRO_KEY_A:
				
				key[0] = false;
				break;

			case ALLEGRO_KEY_D:
				
				key[1] = false;
				break;

				//kill the program if someone presses escape
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
			

		}

		//RENDER SECTION
		//if the clock ticked but no other events happened, don't bother redrawing
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			
			//paint black over the old screen, so the old PaddleL dissapears
			al_clear_to_color(al_map_rgb(0, 0, 64));

			//the algorithm above just changes the x and y coordinates
			//here's where the bitmap is actually drawn somewhere else

			al_draw_bitmap(PaddleL, PaddleL_x, PaddleL_y, 0);
			al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
			al_draw_bitmap(ball, ball_x, ball_y, 0);



			//draw bricks
			if (b1.isDead() == false)
				b1.draw();
			if (b2.isDead() == false)
				b2.draw();
			if (b3.isDead() == false)
				b3.draw();
			if (b4.isDead() == false)
				b4.draw();
			if (b5.isDead() == false)
				b5.draw();
			if (b6.isDead() == false)
				b6.draw();
			if (b7.isDead() == false)
				b7.draw();
			if (b8.isDead() == false)
				b8.draw();
			if (b9.isDead() == false)
				b9.draw();
			if (b10.isDead() == false)
				b10.draw();
			if (b11.isDead() == false)
				b11.draw();
			if (b12.isDead() == false)
				b12.draw();
			if (b13.isDead() == false)
				b13.draw();
			if (b14.isDead() == false)
				b14.draw();
			if (b15.isDead() == false)
				b15.draw();
			if (b16.isDead() == false)
				b16.draw();
			if (b17.isDead() == false)
				b17.draw();
			if (b18.isDead() == false)
				b18.draw();
			if (b19.isDead() == false)
				b19.draw();
			if (b20.isDead() == false)
				b20.draw();

			al_draw_textf(font, al_map_rgb(255, 255, 255), 90, 420, ALLEGRO_ALIGN_LEFT, "Lives :%i", lives);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 150, 150, ALLEGRO_ALIGN_CENTER, "Score :%i", score);
			if (lives == 0 || score == 200)
				break;
			
			al_flip_display();

			

		}//end render section
	
		
		
		
	}//end game loop
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_textf(font, al_map_rgb(255, 255, 255), 540, 40, ALLEGRO_ALIGN_RIGHT, "GAME OVER");
	if (score == 200) {
		al_draw_textf(font, al_map_rgb(255, 255, 255), 240, 60, ALLEGRO_ALIGN_LEFT, "You Win");
	}

	al_draw_textf(font, al_map_rgb(255, 255, 255), 540, 70, ALLEGRO_ALIGN_RIGHT, "Score: %i",score );

	al_flip_display();
	al_rest(5);

	al_destroy_bitmap(PaddleL);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_bitmap(bouncer);
	al_destroy_bitmap(ball);
	


	return 0;

}//end main
int collision(int PaddleL_x, int PaddleL_y, int bouncer_x, int bouncer_y) {
	if ((PaddleL_x + 70 < bouncer_x) || //ball is to the right
		(PaddleL_x  > bouncer_x + 32) || //ball is to the left
		(PaddleL_y > bouncer_y + 32) || //ball is above
		(PaddleL_y + 32 < bouncer_y)) //ball is below
	{
		return 0;//no collision
	}
	else
		return 1; // collision
}


Brick::Brick() {
	xCoordinate = 0;
	yCoordinate = 0;
	width = 0;
	height = 0;
	Dead = 0;

}

void Brick::initBrick(int x, int y, int w, int h) {
	xCoordinate = x;
	yCoordinate = y;
	width = w;
	height = h;
	Dead = 0;

}
int Brick::BrickCollision(int bouncer_x, int bouncer_y) {
	if ((xCoordinate > bouncer_x + height) ||
		(xCoordinate + width < bouncer_x) ||
		(yCoordinate > bouncer_y + height) ||
		(yCoordinate + height < bouncer_y))
	{
		return 0;//no collision
	}
	else
		return 1; // collision
}

void Brick::draw() {
	al_draw_filled_rectangle(xCoordinate, yCoordinate, xCoordinate + width, yCoordinate + height, al_map_rgb(0, 150, 0));
}

bool Brick::isDead() {
	return Dead;
}

void Brick::killBrick() {
	Dead = true;
}
