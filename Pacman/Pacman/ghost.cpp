#include "Globals.h"
#include "ghost.h"
#include<allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>

#include <iostream>
using namespace std;


ghost::ghost() {
	xCoordinate = 0;
	yCoordinate = 0;
	width = 0;
	height = 0;
	Dead = 0;
	direction = 0;

}

void ghost::initghost(int x, int y, int w, int h) {
	xCoordinate = x;
	yCoordinate = y;
	width = w;
	height = h;
	Dead = 0;
	direction = LEFT;

}

int ghost::ghostCollision(int bouncer_x, int bouncer_y) {
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

void ghost::draw() {

	al_draw_filled_rectangle(xCoordinate, yCoordinate, xCoordinate + width, yCoordinate + height, al_map_rgb(0, 150, 0));
}

//bool ghost::isDead() {
	//Dead = true;
//}

bool ghost::killpac(int pacman_x, int pacman_y) {
	if ((xCoordinate + PACSIZE > pacman_x) &&
		(xCoordinate < pacman_x + PACSIZE) &&
		(yCoordinate + PACSIZE > pacman_y) &&
		(yCoordinate < pacman_y + PACSIZE))

	{
		return 1;//no collision
	}
	else
		return 0; // collision
}
int ghost::wallCollide(int x, int y, int dir, int level[20][20]) {
	//cout << "collision function called" << endl;
	cout << "ghosts positions are " << xCoordinate << " , " << yCoordinate << endl;
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
		//	cout << "right collision" << endl;
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
		//	cout << "UP collision";
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

//chase function. x and y are pacman's position.
void ghost::chase(int x, int y, int field[20][20]) {


	/* Directions
	1 = left
	2 = up
	3 = right
	4 = down*/


	/*if (wallCollide(xCoordinate, yCoordinate, 1, field))
	cout << "there's a wall to the left of me" << endl;
	if (wallCollide(xCoordinate, yCoordinate, 2, field))
	cout << "there's a wall above me" << endl;
	if (wallCollide(xCoordinate, yCoordinate, 3, field))
	cout << "there's a wall to the right of me" << endl;
	if (wallCollide(xCoordinate, yCoordinate, 4, field))
	cout << "there's a wall below me" << endl; */

	/////////////////////////////////LEFT STATE (1)//////////////////////////////////////////////////////////////////

	//if we're moving left and there's an opening above and pacman is above, move up
	if ((direction == LEFT) && !wallCollide(xCoordinate, yCoordinate, UP, field) && y < yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 2, field)) {
			// cout << "trying to move through hole above!" << endl;
			direction = UP;
			yCoordinate -= 4;
			return;
		}

	//if we're moving left and there's an opening below and pacman is below, move down
	if ((direction == LEFT) && !wallCollide(xCoordinate, yCoordinate, DOWN, field) && y > yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 4, field)) {
			//  cout << "trying to move through hole below!" << endl;
			direction = DOWN;
			yCoordinate += 4;
			return;
		}


	if (direction == LEFT)//left
		while (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
			xCoordinate -= 4;
			return;
		}

	////////////////////////////////UP STATE (2)///////////////////////////////////////////////////////////////

	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == UP) && !wallCollide(xCoordinate, yCoordinate, LEFT, field) && x < xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
			//   cout << "trying to move through hole to left!" << endl;
			direction = LEFT;
			xCoordinate -= 4;
			return;
		}
	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xCoordinate, yCoordinate, RIGHT, field) && x > xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 3, field)) {
			// cout << "trying to move through hole to right!" << endl;
			direction = RIGHT;
			xCoordinate += 4;
			return;
		}
	if (direction == UP)//up
		while (!wallCollide(xCoordinate, yCoordinate, 2, field)) {
			yCoordinate -= UP;
			return;
		}

	/////////RIGHT CASE (3)/////////////////////////////////////////////////////////////////////////////////////////////////////
	//if we're moving right and there's an opening above and pacman is above, move up
	if ((direction == RIGHT) && !wallCollide(xCoordinate, yCoordinate, UP, field) && y < yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 2, field)) {
			//   cout << "trying to move through hole above!" << endl;
			direction = UP;
			yCoordinate -= 4;
			return;
		}

	//if we're moving right and there's an opening below and pacman is below, move down
	if ((direction == RIGHT) && !wallCollide(xCoordinate, yCoordinate, DOWN, field) && y > yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
			//  cout << "trying to move through hole below!" << endl;
			direction = DOWN;
			yCoordinate += 4;
			return;
		}


	if (direction == RIGHT)//right
		while (!wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
			xCoordinate += 4;
			return;
		}


	//////////////DOWN CASE (4)/////////////////////////////////////////////////////////////////////////////////////
	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == DOWN) && !wallCollide(xCoordinate, yCoordinate, LEFT, field) && x < xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
			// cout << "trying to move through hole to left!" << endl;
			direction = LEFT;
			xCoordinate -= 2;
			return;
		}
	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xCoordinate, yCoordinate, RIGHT, field) && x > xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
			//   cout << "trying to move through hole to right!" << endl;
			direction = RIGHT;
			xCoordinate += 2;
			return;
		}

	if (direction == DOWN)//down
		while (!wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
			yCoordinate += 2;
			return;
		}





	///////////////////////////////////////////////////////////////////////////////////////
	//if pacman is above and there's no wall there, move up
	if ((y < yCoordinate) && !wallCollide(xCoordinate, yCoordinate, UP, field)) {
		//  cout << "direction is up" << endl;
		direction = UP;
		return;
	}


	//if pacman is below and there's no wall there, move down
	if ((y > yCoordinate) && !wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
		direction = DOWN;
		//   cout << "direction is down" << endl;
		return;
	}

	//if pacman is right and there's no wall there, move right
	if ((x > xCoordinate) && !wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
		direction = RIGHT;
		//  cout << "direction is right" << endl;
		return;
	}

	//if pacman is left and there's no wall there, move left
	if ((x < xCoordinate) && !wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
		direction = LEFT;
		// cout << "direction is left" << endl;
		return;

	}

	//if pacman is above and there's no wall there, move up
	if (!wallCollide(xCoordinate, yCoordinate, UP, field)) {
		// cout << "direction is up" << endl;
		direction = UP;
		return;
	}


	//if pacman is below and there's no wall there, move down
	if (!wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
		direction = DOWN;
		//cout << "direction is down" << endl;
		return;
	}

	//if pacman is right and there's no wall there, move right
	if (!wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
		direction = RIGHT;
		//  cout << "direction is right" << endl;
		return;
	}

	//if pacman is left and there's no wall there, move left
	if (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
		direction = LEFT;
		// cout << "direction is left" << endl;
		return;

	}

}
////CHASE2
void ghost::chase2(int x, int y, int field[20][20]) {


	/* Directions
	1 = left
	2 = up
	3 = right
	4 = down*/


	/*if (wallCollide(xCoordinate, yCoordinate, 1, field))
	cout << "there's a wall to the left of me" << endl;
	if (wallCollide(xCoordinate, yCoordinate, 2, field))
	cout << "there's a wall above me" << endl;
	if (wallCollide(xCoordinate, yCoordinate, 3, field))
	cout << "there's a wall to the right of me" << endl;
	if (wallCollide(xCoordinate, yCoordinate, 4, field))
	cout << "there's a wall below me" << endl; */

	/////////////////////////////////LEFT STATE (1)//////////////////////////////////////////////////////////////////

	//if we're moving left and there's an opening above and pacman is above, move up
	if ((direction == LEFT) && !wallCollide(xCoordinate, yCoordinate, UP, field) && y < yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 2, field)) {
			// cout << "trying to move through hole above!" << endl;
			direction = UP;
			yCoordinate -= 4;
			return;
		}

	//if we're moving left and there's an opening below and pacman is below, move down
	if ((direction == LEFT) && !wallCollide(xCoordinate, yCoordinate, DOWN, field) && y > yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 4, field)) {
			//  cout << "trying to move through hole below!" << endl;
			direction = DOWN;
			yCoordinate += 4;
			return;
		}


	if (direction == LEFT)//left
		while (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
			xCoordinate -= 4;
			return;
		}

	////////////////////////////////UP STATE (2)///////////////////////////////////////////////////////////////

	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == UP) && !wallCollide(xCoordinate, yCoordinate, LEFT, field) && x < xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
			//   cout << "trying to move through hole to left!" << endl;
			direction = LEFT;
			xCoordinate -= 4;
			return;
		}
	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xCoordinate, yCoordinate, RIGHT, field) && x > xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 3, field)) {
			// cout << "trying to move through hole to right!" << endl;
			direction = RIGHT;
			xCoordinate += 4;
			return;
		}
	if (direction == UP)//up
		while (!wallCollide(xCoordinate, yCoordinate, 2, field)) {
			yCoordinate -= UP;
			return;
		}

	/////////RIGHT CASE (3)/////////////////////////////////////////////////////////////////////////////////////////////////////
	//if we're moving right and there's an opening above and pacman is above, move up
	if ((direction == RIGHT) && !wallCollide(xCoordinate, yCoordinate, UP, field) && y < yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 2, field)) {
			//   cout << "trying to move through hole above!" << endl;
			direction = UP;
			yCoordinate -= 2;
			return;
		}

	//if we're moving right and there's an opening below and pacman is below, move down
	if ((direction == RIGHT) && !wallCollide(xCoordinate, yCoordinate, DOWN, field) && y > yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
			//  cout << "trying to move through hole below!" << endl;
			direction = DOWN;
			yCoordinate += 4;
			return;
		}


	if (direction == RIGHT)//right
		while (!wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
			xCoordinate += 2;
			return;
		}


	//////////////DOWN CASE (4)/////////////////////////////////////////////////////////////////////////////////////
	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == DOWN) && !wallCollide(xCoordinate, yCoordinate, LEFT, field) && x < xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
			// cout << "trying to move through hole to left!" << endl;
			direction = LEFT;
			xCoordinate -= 4;
			return;
		}
	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xCoordinate, yCoordinate, RIGHT, field) && x > xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
			//   cout << "trying to move through hole to right!" << endl;
			direction = RIGHT;
			xCoordinate += 2;
			return;
		}

	if (direction == DOWN)//down
		while (!wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
			yCoordinate += 2;
			return;
		}





	///////////////////////////////////////////////////////////////////////////////////////
	//if pacman is above and there's no wall there, move up
	if ((y < yCoordinate) && !wallCollide(xCoordinate, yCoordinate, UP, field)) {
		//  cout << "direction is up" << endl;
		direction = UP;
		return;
	}


	//if pacman is below and there's no wall there, move down
	if ((y > yCoordinate) && !wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
		direction = DOWN;
		//   cout << "direction is down" << endl;
		return;
	}

	//if pacman is right and there's no wall there, move right
	if ((x > xCoordinate) && !wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
		direction = RIGHT;
		//  cout << "direction is right" << endl;
		return;
	}

	//if pacman is left and there's no wall there, move left
	if ((x < xCoordinate) && !wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
		direction = LEFT;
		// cout << "direction is left" << endl;
		return;

	}

	//if pacman is above and there's no wall there, move up
	if (!wallCollide(xCoordinate, yCoordinate, UP, field)) {
		// cout << "direction is up" << endl;
		direction = UP;
		return;
	}


	//if pacman is below and there's no wall there, move down
	if (!wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
		direction = DOWN;
		//cout << "direction is down" << endl;
		return;
	}

	//if pacman is right and there's no wall there, move right
	if (!wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
		direction = RIGHT;
		//  cout << "direction is right" << endl;
		return;
	}

	//if pacman is left and there's no wall there, move left
	if (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
		direction = LEFT;
		// cout << "direction is left" << endl;
		return;

	}

}
void ghost::chase3(int x, int y, int field[20][20]) {


	/* Directions
	1 = left
	2 = up
	3 = right
	4 = down*/


	/*if (wallCollide(xCoordinate, yCoordinate, 1, field))
	cout << "there's a wall to the left of me" << endl;
	if (wallCollide(xCoordinate, yCoordinate, 2, field))
	cout << "there's a wall above me" << endl;
	if (wallCollide(xCoordinate, yCoordinate, 3, field))
	cout << "there's a wall to the right of me" << endl;
	if (wallCollide(xCoordinate, yCoordinate, 4, field))
	cout << "there's a wall below me" << endl; */

	/////////////////////////////////LEFT STATE (1)//////////////////////////////////////////////////////////////////

	//if we're moving left and there's an opening above and pacman is above, move up
	if ((direction == LEFT) && !wallCollide(xCoordinate, yCoordinate, UP, field) && y < yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 2, field)) {
			// cout << "trying to move through hole above!" << endl;
			direction = UP;
			yCoordinate -= 2;
			return;
		}

	//if we're moving left and there's an opening below and pacman is below, move down
	if ((direction == LEFT) && !wallCollide(xCoordinate, yCoordinate, DOWN, field) && y > yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 4, field)) {
			//  cout << "trying to move through hole below!" << endl;
			direction = DOWN;
			yCoordinate += 2;
			return;
		}


	if (direction == LEFT)//left
		while (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
			xCoordinate -= 2;
			return;
		}

	////////////////////////////////UP STATE (2)///////////////////////////////////////////////////////////////

	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == UP) && !wallCollide(xCoordinate, yCoordinate, LEFT, field) && x < xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
			//   cout << "trying to move through hole to left!" << endl;
			direction = LEFT;
			xCoordinate -= 2;
			return;
		}
	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xCoordinate, yCoordinate, RIGHT, field) && x > xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 3, field)) {
			// cout << "trying to move through hole to right!" << endl;
			direction = RIGHT;
			xCoordinate += 2;
			return;
		}
	if (direction == UP)//up
		while (!wallCollide(xCoordinate, yCoordinate, 2, field)) {
			yCoordinate -= UP;
			return;
		}

	/////////RIGHT CASE (3)/////////////////////////////////////////////////////////////////////////////////////////////////////
	//if we're moving right and there's an opening above and pacman is above, move up
	if ((direction == RIGHT) && !wallCollide(xCoordinate, yCoordinate, UP, field) && y < yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 2, field)) {
			//   cout << "trying to move through hole above!" << endl;
			direction = UP;
			yCoordinate -= 2;
			return;
		}

	//if we're moving right and there's an opening below and pacman is below, move down
	if ((direction == RIGHT) && !wallCollide(xCoordinate, yCoordinate, DOWN, field) && y > yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
			//  cout << "trying to move through hole below!" << endl;
			direction = DOWN;
			yCoordinate += 2;
			return;
		}


	if (direction == RIGHT)//right
		while (!wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
			xCoordinate += 2;
			return;
		}


	//////////////DOWN CASE (4)/////////////////////////////////////////////////////////////////////////////////////
	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == DOWN) && !wallCollide(xCoordinate, yCoordinate, LEFT, field) && x < xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
			// cout << "trying to move through hole to left!" << endl;
			direction = LEFT;
			xCoordinate -= 2;
			return;
		}
	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xCoordinate, yCoordinate, RIGHT, field) && x > xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
			//   cout << "trying to move through hole to right!" << endl;
			direction = RIGHT;
			xCoordinate += 2;
			return;
		}

	if (direction == DOWN)//down
		while (!wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
			yCoordinate += 2;
			return;
		}





	///////////////////////////////////////////////////////////////////////////////////////
	//if pacman is above and there's no wall there, move up
	if ((y < yCoordinate) && !wallCollide(xCoordinate, yCoordinate, UP, field)) {
		//  cout << "direction is up" << endl;
		direction = UP;
		return;
	}


	//if pacman is below and there's no wall there, move down
	if ((y > yCoordinate) && !wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
		direction = DOWN;
		//   cout << "direction is down" << endl;
		return;
	}

	//if pacman is right and there's no wall there, move right
	if ((x > xCoordinate) && !wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
		direction = RIGHT;
		//  cout << "direction is right" << endl;
		return;
	}

	//if pacman is left and there's no wall there, move left
	if ((x < xCoordinate) && !wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
		direction = LEFT;
		// cout << "direction is left" << endl;
		return;

	}

	//if pacman is above and there's no wall there, move up
	if (!wallCollide(xCoordinate, yCoordinate, UP, field)) {
		// cout << "direction is up" << endl;
		direction = UP;
		return;
	}


	//if pacman is below and there's no wall there, move down
	if (!wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
		direction = DOWN;
		//cout << "direction is down" << endl;
		return;
	}

	//if pacman is right and there's no wall there, move right
	if (!wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
		direction = RIGHT;
		//  cout << "direction is right" << endl;
		return;
	}

	//if pacman is left and there's no wall there, move left
	if (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
		direction = LEFT;
		// cout << "direction is left" << endl;
		return;

	}

}
////CHASE4
void ghost::chase4(int x, int y, int field[20][20]) {


	/* Directions
	1 = left
	2 = up
	3 = right
	4 = down*/


	/*if (wallCollide(xCoordinate, yCoordinate, 1, field))
	cout << "there's a wall to the left of me" << endl;
	if (wallCollide(xCoordinate, yCoordinate, 2, field))
	cout << "there's a wall above me" << endl;
	if (wallCollide(xCoordinate, yCoordinate, 3, field))
	cout << "there's a wall to the right of me" << endl;
	if (wallCollide(xCoordinate, yCoordinate, 4, field))
	cout << "there's a wall below me" << endl; */

	/////////////////////////////////LEFT STATE (1)//////////////////////////////////////////////////////////////////

	//if we're moving left and there's an opening above and pacman is above, move up
	if ((direction == LEFT) && !wallCollide(xCoordinate, yCoordinate, UP, field) && y < yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 2, field)) {
			// cout << "trying to move through hole above!" << endl;
			direction = UP;
			yCoordinate -= 4;
			return;
		}

	//if we're moving left and there's an opening below and pacman is below, move down
	if ((direction == LEFT) && !wallCollide(xCoordinate, yCoordinate, DOWN, field) && y > yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 4, field)) {
			//  cout << "trying to move through hole below!" << endl;
			direction = DOWN;
			yCoordinate += 4;
			return;
		}


	if (direction == LEFT)//left
		while (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
			xCoordinate -= 4;
			return;
		}

	////////////////////////////////UP STATE (2)///////////////////////////////////////////////////////////////

	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == UP) && !wallCollide(xCoordinate, yCoordinate, LEFT, field) && x < xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
			//   cout << "trying to move through hole to left!" << endl;
			direction = LEFT;
			xCoordinate -= 4;
			return;
		}
	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xCoordinate, yCoordinate, RIGHT, field) && x > xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 3, field)) {
			// cout << "trying to move through hole to right!" << endl;
			direction = RIGHT;
			xCoordinate += 4;
			return;
		}
	if (direction == UP)//up
		while (!wallCollide(xCoordinate, yCoordinate, 2, field)) {
			yCoordinate -= UP;
			return;
		}

	/////////RIGHT CASE (3)/////////////////////////////////////////////////////////////////////////////////////////////////////
	//if we're moving right and there's an opening above and pacman is above, move up
	if ((direction == RIGHT) && !wallCollide(xCoordinate, yCoordinate, UP, field) && y < yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, 2, field)) {
			//   cout << "trying to move through hole above!" << endl;
			direction = UP;
			yCoordinate -= 7;
			return;
		}

	//if we're moving right and there's an opening below and pacman is below, move down
	if ((direction == RIGHT) && !wallCollide(xCoordinate, yCoordinate, DOWN, field) && y > yCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
			//  cout << "trying to move through hole below!" << endl;
			direction = DOWN;
			yCoordinate += 7;
			return;
		}


	if (direction == RIGHT)//right
		while (!wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
			xCoordinate += 7;
			return;
		}


	//////////////DOWN CASE (4)/////////////////////////////////////////////////////////////////////////////////////
	//if we're moving up and there's an opening left and pacman is left, move left
	if ((direction == DOWN) && !wallCollide(xCoordinate, yCoordinate, LEFT, field) && x < xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
			// cout << "trying to move through hole to left!" << endl;
			direction = LEFT;
			xCoordinate -= 2;
			return;
		}
	//if we're moving up and there's an opening right and pacman is right, move right
	if ((direction == UP) && !wallCollide(xCoordinate, yCoordinate, RIGHT, field) && x > xCoordinate)
		while (!wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
			//   cout << "trying to move through hole to right!" << endl;
			direction = RIGHT;
			xCoordinate += 2;
			return;
		}

	if (direction == DOWN)//down
		while (!wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
			yCoordinate += 2;
			return;
		}





	///////////////////////////////////////////////////////////////////////////////////////
	//if pacman is above and there's no wall there, move up
	if ((y < yCoordinate) && !wallCollide(xCoordinate, yCoordinate, UP, field)) {
		//  cout << "direction is up" << endl;
		direction = UP;
		return;
	}


	//if pacman is below and there's no wall there, move down
	if ((y > yCoordinate) && !wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
		direction = DOWN;
		//   cout << "direction is down" << endl;
		return;
	}

	//if pacman is right and there's no wall there, move right
	if ((x > xCoordinate) && !wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
		direction = RIGHT;
		//  cout << "direction is right" << endl;
		return;
	}

	//if pacman is left and there's no wall there, move left
	if ((x < xCoordinate) && !wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
		direction = LEFT;
		// cout << "direction is left" << endl;
		return;

	}

	//if pacman is above and there's no wall there, move up
	if (!wallCollide(xCoordinate, yCoordinate, UP, field)) {
		// cout << "direction is up" << endl;
		direction = UP;
		return;
	}


	//if pacman is below and there's no wall there, move down
	if (!wallCollide(xCoordinate, yCoordinate, DOWN, field)) {
		direction = DOWN;
		//cout << "direction is down" << endl;
		return;
	}

	//if pacman is right and there's no wall there, move right
	if (!wallCollide(xCoordinate, yCoordinate, RIGHT, field)) {
		direction = RIGHT;
		//  cout << "direction is right" << endl;
		return;
	}

	//if pacman is left and there's no wall there, move left
	if (!wallCollide(xCoordinate, yCoordinate, LEFT, field)) {
		direction = LEFT;
		// cout << "direction is left" << endl;
		return;

	}

}