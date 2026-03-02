#include "GameObject.h"

//constructor
GameObject::GameObject(int x, int y, int w, int h, COLORREF c)
			: x(x), y(y), width(w), height(h), color(c) {}
		
//destructor
GameObject::~GameObject() {}

//accessor
int GameObject::getX()const { return x; }
int GameObject::getY() const { return y; }
int GameObject::getWidth() const { return width; }
int GameObject::getHeight() const { return height; }
COLORREF GameObject::getColor() const { return color;}

//mutator
void GameObject::setX(int _x) { x = _x; }
void GameObject::setY(int _y) { y = _y; }
void GameObject::setWidth(int w) { width = w; }
void GameObject::setHeight(int h) { height = h; }
void GameObject::setColor(COLORREF c) { color = c; }

//Collision detection
bool GameObject::isColliding(const GameObject *other) const
{
	return x < (other->x+ other->width) &&		//left boundary < right boundary
		   (x + width) > (other->x) &&			// right > left other object
		   y < (other->y + other->height) &&	// top < bottom other object
           (y + height) > (other->y); 			// bottom > top other object
}
