#include "Bullet.h"


Bullet :: Bullet(int x, int y, bool isEnemy) 
       : GameObject(
            (isEnemy) ? x + 15 : x + 20, // x for player & enemy
            (isEnemy) ? y + 40 : y - 10, // y for player & enemy
            10, 20, // width & height
            (isEnemy) ? ENEMY_BULLET_COLOR : PLAYER_BULLET_COLOR), // color for player & enemy
        isEnemyBullet(isEnemy) {} 
    
void Bullet :: setIsEnemyBullet(bool value){
    isEnemyBullet = value; 
}

bool Bullet :: getIsEnemyBullet() const {
    return isEnemyBullet;
}

void Bullet :: update() {
    if (isEnemyBullet) {
        y += BULLET_SPEED; // enemy bullet move downward
    }
    else {
        y -= BULLET_SPEED; // Bullet moves upward
    }
}
    
void Bullet :: draw() {
    setcolor(color);
    setfillstyle(SOLID_FILL, color);
    bar(x, y, x + width, y + height);
}
    
bool Bullet :: isOutOfBounds() const {
   return isEnemyBullet ? (y > HEIGHT) : (y < -height); // if player bullet : y + height < 0
}
    