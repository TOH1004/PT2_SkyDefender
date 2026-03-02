#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "Bullet.h"
#include "Constants.h"
class Player : public GameObject {
private:
    int lives;
    int score;
    int shootCooldown;
    Bullet* bullets[MAX_PLAYER_BULLETS];
    int bulletCount;
public:
    Player(int x, int y);
    ~Player();
    
    //Movement methods
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    
    //Game state management
	void addScore(int points);
	void loseLife();
	void gainLife();
	
	//Bullet management
	void shoot();
    void decreaseBulletCount();
    void updateBullets();
    
	//Acessors
	int getLives() const;
    int getScore() const;
    int getShootCooldown() const;
    
    //Mutators
    void setLives(int newLives);
	void setScore(int newScore); 
	void setShootCooldown(int cooldown);
    
    //Bullet access
    Bullet** getBullets();
    const Bullet** getBullets() const;
    int getBulletCount() const;

    //Game loop methods
    void update();
    void draw();
};

#endif