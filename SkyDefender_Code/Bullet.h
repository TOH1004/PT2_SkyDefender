#ifndef BULLET_H
#define BULLET_H

#include <winbgim.h>
#include "GameObject.h"
#include "Constants.h"

class Bullet : public GameObject {
private:
    bool isEnemyBullet;
public:
    Bullet(int x, int y, bool isEnemy = false);
    void setIsEnemyBullet(bool);
    bool getIsEnemyBullet() const;
    void update();
    void draw();
    bool isOutOfBounds() const;
};

#endif
