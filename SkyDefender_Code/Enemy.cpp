#include "Enemy.h"
#include "Constants.h"
#include <cstdlib>

Enemy :: Enemy(int x, int y) 
       : GameObject(x, y, 40, 40, ENEMY_COLOR), 
         speed(ENEMY_SPEED + rand() % 3), shootCooldown(0), bulletCount(0){
            for (int i = 0; i < 100; ++i) 
                bullets[i] = nullptr;
          }

void Enemy :: setSpeed(){
    speed = ENEMY_SPEED;
}

void Enemy :: setshootCooldown(int s){
    shootCooldown = s;
}

void Enemy :: setBulletCount(int b){
    bulletCount = b;
}

int Enemy :: getSpeed() const{
    return speed;
}

int Enemy :: getshootCooldown() const{
    return shootCooldown;
}

int Enemy :: getBulletCount() const {
        return bulletCount;
}

Bullet** Enemy :: getBullets() {
    return bullets;
}

Bullet* Enemy :: tryShoot() {
    if (shootCooldown == 0 && bulletCount < MAX_ENEMY_BULLETS) {
        shootCooldown = 55;
        Bullet* b = new Bullet(x, y, true); 
        bullets[bulletCount++] = b; 
        return b;
    }
    shootCooldown--;
    return nullptr;
}

void Enemy :: removeBullet(int index) {
    if (index < 0 || index >= bulletCount) return;
    // Remove bullet without deleting (Game owns the lifetime)
    for (int i = index; i < bulletCount - 1; ++i) {
        bullets[i] = bullets[i + 1];
    }
    bullets[--bulletCount] = nullptr;
}
    
 
void Enemy :: update(){
    y += speed; // Enemy moves downward
}
    
void Enemy :: draw(){
    setcolor(color);
    setfillstyle(SOLID_FILL, color);
    // Draw simple inverted triangle enemy
    int points[8] = {
        x, y,
        x + width, y,
        x + width/2, y + height,
        x, y
    };
    fillpoly(4, points);
}
    
bool Enemy :: isOutOfBounds() const { 
	return y > HEIGHT;
}