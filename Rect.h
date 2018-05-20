#ifndef Rect_h
#define Rect_h

#include <stdlib.h> //rand()
#include <time.h> //time()

class Rect {
	float x, y, width, height, red, green, blue;
	unsigned id;
public:
	Rect() {
		x = 0.0f;
		y = 0.0f;
		width = 1.0f;
		height = 1.0f;
		red = 0.5f;
		green = 0.5f;
		blue = 0.5f;
		id = 999;
	}
	Rect(float x, float y, float width, float height) {
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		red = (float)(rand() % 100) / 100;
		green = (float)(rand() % 100) / 100;
		blue = (float)(rand() % 100) / 100;
		id = 998;
		
	}
	Rect(unsigned id, float x, float y, float width, float height, float red, float green, float blue) {
		this->id = id;
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		this->red = red;
		this->green = green;
		this->blue = blue;
	}
	Rect( const Rect &rec ) {
		this->id = rec.getID();
		this->x = rec.getX();
		this->y = rec.getY();
		this->width = rec.getWidth();
		this->height = rec.getHeight();
		this->red = rec.getRed();
		this->green = rec.getGreen();
		this->blue = rec.getBlue();
	}
	~Rect() {}
	
	void setX(float xx) {
		x = xx;
	}
	void setY(float yy) {
		y = yy;
	}
	void setWidth(float w) {
		width = w;
	}
	void setHeight(float h) {
		height = h;
	}
	void setRed(float r) {
		red = r;
	}
	void setGreen(float g) {
		green = g;
	}
	void setBlue(float b) {
		blue = b;
	}
	void randomizeCol() {
		red = (float)(rand() % 100) / 100;
		green = (float)(rand() % 100) / 100;
		blue = (float)(rand() % 100) / 100;
	}
	float getX() const {
		return x;
	}
	float getY() const {
		return y;
	}
	float getWidth() const {
		return width;
	}
	float getHeight() const {
		return height;
	}
	float getRed() const {
		return red;
	}
	float getGreen() const {
		return green;
	}
	float getBlue() const {
		return blue;
	}
	unsigned getID() const {
		return id;
	}
	
	bool contains(float xx, float yy) {
		if (xx > x && xx < x + width) {
			if (yy < y && yy > y - height)
				return true;
		}
		return false;
	}
};

#endif