#include "Player.h"
#include "Constants.h"

Player::Player(int x, int y):
	GameObject(x, y, 50, 50, PLAYER_COLOR), 
    lives(3), score(0), shootCooldown(0), bulletCount(0) {
    for (int i = 0; i < MAX_PLAYER_BULLETS; i++) {
        bullets[i] = nullptr;
    }
}

Player::~Player() {
    for (int i = 0; i < bulletCount; i++) {
        if (bullets[i] != nullptr) {
            delete bullets[i];
        }
    }
}
    //Movement methods
    void Player::moveLeft() { if (x > 0) x -= PLAYER_SPEED; }
	void Player::moveRight() { if (x < WIDTH - width) x += PLAYER_SPEED; }
	void Player::moveUp() { if (y > 0) y -= PLAYER_SPEED; }
	void Player::moveDown() { if (y < HEIGHT - height) y += PLAYER_SPEED; }
    
    //Game state management
	void Player::addScore(int points) { score += points; }
	void Player::loseLife() { lives--; }
	void Player::gainLife() { lives++; }
	
	//Bullet management
	void Player::shoot() {
    if (shootCooldown <= 0 && bulletCount < MAX_PLAYER_BULLETS) {
        bullets[bulletCount++] = new Bullet(x, y);
        shootCooldown = 10;
    }
}
    void Player::decreaseBulletCount() { if (bulletCount > 0) bulletCount--; }
    void Player::updateBullets() {
    for (int i = 0; i < bulletCount; ) {
        if (bullets[i] != nullptr) {
            bullets[i]->update();
            
            if (bullets[i]->isOutOfBounds()) {
                delete bullets[i];
                for (int j = i; j < bulletCount - 1; j++) {
                    bullets[j] = bullets[j + 1];
                }
                bulletCount--;
                bullets[bulletCount] = nullptr;
            } else {
                i++;
            }
        }
    }
    
    if (shootCooldown > 0) {
        shootCooldown--;
    }
}
    
	//Acessors
	int Player::getLives()const {return lives;}
	int Player::getScore()const {return score;}
	int Player::getShootCooldown()const {return shootCooldown;}
	
	//Mutators
	void Player::setLives(int newLives) { lives = newLives; }
	void Player::setScore(int newScore) { score = newScore; }
	void Player::setShootCooldown(int cooldown) { shootCooldown = cooldown; }
    
    //Bullet access
    Bullet** Player::getBullets() { return bullets; }
    const Bullet** Player::getBullets() const { return const_cast<const Bullet**>(bullets); }
    int Player::getBulletCount() const { return bulletCount; }
  
    //Game loop methods
    void Player::update() {
    updateBullets();
}
   void Player::draw() {
    setcolor(color);
    setfillstyle(SOLID_FILL, color);
    int points[8] = {
        x + width/2, y,        
        x + width, y + height, 
        x, y + height,        
        x + width/2, y        
    };
    fillpoly(4, points);
    
    for (int i = 0; i < bulletCount; i++) {
        if (bullets[i] != nullptr) {
            bullets[i]->draw();
        }
    }
}

