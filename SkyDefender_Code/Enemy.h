#ifndef ENEMY_H
#define ENEMY_H

#include <winbgim.h>
#include "GameObject.h"
#include "Bullet.h"
#include "Constants.h"

class Enemy : public GameObject {
private:
    int speed;
    int shootCooldown;
    Bullet *bullets[MAX_ENEMY_BULLETS];
    int bulletCount;
public:
    Enemy(int x, int y);
    void setSpeed();
    void setshootCooldown(int);
    void setBulletCount(int);
    int getSpeed () const;
    int getshootCooldown () const;
    int getBulletCount () const;
    Bullet** getBullets();
    Bullet* tryShoot();
    void removeBullet(int);
    void update();
    void draw();
    bool isOutOfBounds() const;
};

#endif