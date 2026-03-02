#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <winbgim.h>
#include "Constants.h"

//base game object class
class GameObject {
	protected:
		int x, y;			//coordinates of objects
		int width, height;  // object's width & height for colliding checking
		COLORREF color;		
	
	public:
		GameObject (int x, int y, int w, int h, COLORREF c); //constructor
		~GameObject();  //destructor
		
		//accessor
		int getX() const;
		int getY() const;
		int getWidth() const;
		int getHeight() const;
		COLORREF getColor() const;
		
		//mutator
		void setX(int _x);
	    void setY(int y);
	    void setWidth(int w); 
	    void setHeight(int h);
	    void setColor(COLORREF c);
    
		// pure virtual
		virtual void update() = 0; //update object status like movement
		virtual void draw() = 0;   //display plane and bullent on screen
	
		//check collision use method AABB - check ovrelap
		bool isColliding(const GameObject*) const; 
};

#endif