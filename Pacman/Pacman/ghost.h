#pragma once
class ghost {
public:
	ghost();
	void initghost(int x, int y, int w, int h);
	void draw();
	//bool isDead();
	int ghostCollision(int bouncer_x, int bouncer_y);
	bool killpac(int pacman_x, int pacman_y);
	void chase(int x, int y, int field[20][20]);
	void chase2(int x, int y, int field[20][20]);
	void chase3(int x, int y, int field[20][20]);
	void chase4(int x, int y, int field[20][20]);
	int setPosition(int x, int y);
private:
	int xCoordinate;
	int yCoordinate;
	int width;
	int height;
	bool Dead;
	int direction;
	int wallCollide(int x, int y, int dir, int level[20][20]);
};

