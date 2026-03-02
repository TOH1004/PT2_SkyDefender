// Game.cpp
#include "Game.h"
#include <graphics.h>
#include <conio.h>

// Accessors
Player* Game::getPlayer() const { return player; }
int Game::getEnemyBulletCount() const { return enemyBulletCount; }
Bullet** Game::getEnemyBullets() { return enemyBullets; }
const Bullet* const* Game::getEnemyBullets() const { return enemyBullets; }

int Game::getEnemyCount() const { return enemyCount; }
Enemy** Game::getEnemies() { return enemies; }
const Enemy* const* Game::getEnemies() const { return enemies; }

bool Game::isGameOver() const { return gameOver; }
int Game::getEnemySpawnTimer() const { return enemySpawnTimer; }
int Game::getBackgroundY() const { return backgroundY; }

// Mutators
void Game::setGameOver(bool over) { gameOver = over; }
void Game::setEnemySpawnTimer(int timer) { enemySpawnTimer = timer; }
void Game::setBackgroundY(int y) { backgroundY = y; }

void Game::processInput() {
	//GetAsyncKeyState( ) calls a Windows API function to check the key state
	//0x8000 (key is press down)
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) player->moveLeft();
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) player->moveRight();
    if (GetAsyncKeyState(VK_UP) & 0x8000) player->moveUp();
    if (GetAsyncKeyState(VK_DOWN) & 0x8000) player->moveDown();
    //esc to quit
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) gameOver = true;
    //allow continuous shooting
    player->shoot();
}

void Game::update() {
	//update player status
   player->update();
        
        // Spawn new enemies
        if (enemySpawnTimer <= 0 && enemyCount < MAX_ENEMIES) {
        	//random (x,-40) 
            int x = rand() % (WIDTH - 40);
            enemies[enemyCount++] = new Enemy(x, -40);
            //30fps no have enemy
            enemySpawnTimer = ENEMY_SPAWN_RATE;
        } else {
            enemySpawnTimer--;
        }
        
        // Enemy shooting
        for (int i = 0; i < enemyCount; i++) {
        	//now enemyBulletCount=0
            if (enemies[i] != nullptr && enemyBulletCount < MAX_ENEMY_BULLETS) {
            Bullet* bullet = enemies[i]->tryShoot();
            //if can shoot
            if (bullet != nullptr) {
                enemyBullets[enemyBulletCount++] = bullet;
            }
        }
        }
        
        // Update enemy bullets
        for (int i = 0; i < enemyBulletCount; ) {
            if (enemyBullets[i] != nullptr) {
            	//bullet class's update()
                enemyBullets[i]->update();
                
                if (enemyBullets[i]->isOutOfBounds()) {
                    delete enemyBullets[i];
                    // Shift remaining bullets down
                    for (int j = i; j < enemyBulletCount - 1; j++) {
                    	//enemyBullets[2] = enemyBullets[3] go front
                        enemyBullets[j] = enemyBullets[j + 1];
                    }
                    //sum--
                    enemyBulletCount--;
                    //last clear
                    enemyBullets[enemyBulletCount] = nullptr;
                } 
				else {
                    i++;
                }
            }
        }
        
        // Update enemies
        for (int i = 0; i < enemyCount; ) {
            if (enemies[i] != nullptr) {
                enemies[i]->update();
                
                if (enemies[i]->isOutOfBounds()) {
                    delete enemies[i];
                    // Shift remaining enemies down
                    for (int j = i; j < enemyCount - 1; j++) {
                        enemies[j] = enemies[j + 1];
                    }
                    enemyCount--;
                    enemies[enemyCount] = nullptr;
                } 
				else {
                    i++;
                }
            }
        }
        
        
        // Collision detection: player bullets vs enemies
        //getBulletCount() return bullet count 
        //getBullets() return bullet
        for (int bulletIdx = 0; bulletIdx < player->getBulletCount(); ) {
            bool bulletHit = false;
            Bullet* bullet = player->getBullets()[bulletIdx];
            
            for (int enemyIdx = 0; enemyIdx < enemyCount; ) {
                Enemy* enemy = enemies[enemyIdx];
                if (bullet != nullptr && enemy != nullptr && bullet->isColliding(enemy)) {
                    // Bullet hit enemy
                    player->addScore(10);
                    
                    delete bullet;
                    // Remove bullet by shifting array
                    for (int j = bulletIdx; j < player->getBulletCount() - 1; j++) {
                        player->getBullets()[j] = player->getBullets()[j + 1];
                    }
                    player->decreaseBulletCount();
                    bulletHit = true;
                    
                    delete enemy;
                    // Remove enemy by shifting array
                    for (int j = enemyIdx; j < enemyCount - 1; j++) {
                        enemies[j] = enemies[j + 1];
                    }
                    enemyCount--;
                    
                    break;
                } else {
                    enemyIdx++;
                }
            }
            
            if (!bulletHit) {
            	//detect next bullet
                bulletIdx++;
            }
        }
        
        // Collision detection: enemy bullets vs player
        for (int i = 0; i < enemyBulletCount; ) {
            Bullet* bullet = enemyBullets[i];
            if (bullet != nullptr && player->isColliding(bullet)) {
                player->loseLife();
                delete bullet;
                // Remove bullet by shifting array
                for (int j = i; j < enemyBulletCount - 1; j++) {
                    enemyBullets[j] = enemyBullets[j + 1];
                }
                enemyBulletCount--;
                
                if (player->getLives() <= 0) {
                    gameOver = true;
                }
            } 
			else {
                i++;
            }
        }
        
        // Collision detection: player vs enemies
        for (int i = 0; i < enemyCount; ) {
            Enemy* enemy = enemies[i];
            if (enemy != nullptr && player->isColliding(enemy)) {
                player->loseLife();
                delete enemy;
                // Remove enemy by shifting array
                for (int j = i; j < enemyCount - 1; j++) {
                    enemies[j] = enemies[j + 1];
                }
                enemyCount--;
                
                if (player->getLives() <= 0) {
                    gameOver = true;
                }
            } else {
                i++;
            }
        }
        
        // Update scrolling background
        backgroundY += 2;//downward
        if (backgroundY >= HEIGHT) {//outside screen
            backgroundY = 0;//will repeat and repeat
        }
}

void Game::draw() {
    cleardevice();
        
        // Draw starry background
        setcolor(COLOR(100, 100, 100));
        for (int i = 0; i < 100; i++) {
        	//random (x,y)
            int starX = rand() % WIDTH;
            int starY = (rand() % HEIGHT + backgroundY) % HEIGHT;//with scorlling background
            putpixel(starX, starY, COLOR(255, 255, 255));//white
        }
        
        // Draw enemy bullet
        for (int i = 0; i < enemyBulletCount; i++) {
            if (enemyBullets[i] != nullptr) {
                enemyBullets[i]->draw();
            }
        }
        
        //Draw enemy
        for (int i = 0; i < enemyCount; i++) {
            if (enemies[i] != nullptr) {
                enemies[i]->draw();
            }
        }
        
        //Draw player
        player->draw();
        
        // Draw UI
        char scoreText[50];
        settextstyle(GOTHIC_FONT, HORIZ_DIR, 2); //font,direction,size
        sprintf(scoreText, "Score: %d", player->getScore());
        outtextxy(10, 10, scoreText);
        
        char livesText[50];
        sprintf(livesText, "Lives: %d", player->getLives());
        outtextxy(10, 30, livesText);
        
        if (gameOver) {
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
            setcolor(COLOR(255, 0, 0));//red
            outtextxy(WIDTH/2 - 160, HEIGHT/2 - 30, "GAME OVER");
            
            char finalScore[50];
            sprintf(finalScore, "Final Score: %d", player->getScore());
            outtextxy(WIDTH/2 - 240, HEIGHT/2 + 10, finalScore);
            
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            outtextxy(WIDTH/2 - 200, HEIGHT/2 + 50, "Press ENTER key to exit");
        }
}

void Game::cleanup() {
		// Deallocate player object
        delete player;
        
        // Deallocate all enemy bullets
        for (int i = 0; i < enemyBulletCount; i++) {
            if (enemyBullets[i] != nullptr) {
                delete enemyBullets[i];
            }
        }
        
        // Deallocate all enemies
        for (int i = 0; i < enemyCount; i++) {
            if (enemies[i] != nullptr) {
                delete enemies[i];
            }
        }
}

Game::Game() {//constructor
	// Initialize random number generator
    srand(static_cast<unsigned>(time(nullptr)));
    // Create player object (centered at bottom)
    player = new Player(WIDTH / 2 - 25, HEIGHT - 100);
    // Initialize game state
    gameOver = false;
    enemySpawnTimer = ENEMY_SPAWN_RATE;
    backgroundY = 0;
    enemyBulletCount = 0;
    enemyCount = 0;
    // Initialize bullet array (set all to nullptr)
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++) {
        enemyBullets[i] = nullptr;
    }
    // Initialize enemy array (set all to nullptr)
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i] = nullptr;
    }
}

Game::~Game() {//destructor
    cleanup();
}

void Game::run() {
	// double buffering - solve flickering when draw the screen
    // setactivepage() -> set current drawing page (back buffer)
   	// setvisualpage() -> set current display page (front buffer)
	setactivepage(0); 
	setvisualpage(0); 
    int currentPage = 0;
        
    while (!gameOver) {
        setactivepage(1 - currentPage); // back buffer
        	
		cleardevice();
        processInput();
        update();
        draw();
            
        setvisualpage(1 - currentPage); //display front buffer
        currentPage = 1 - currentPage; // change 
            
        delay(30);//delay 30ms to control frame rate
    }

    while (true) {
    setactivepage(1 - currentPage);
    cleardevice();
            
    draw();
            
    setvisualpage(1 - currentPage);
    currentPage = 1 - currentPage;
        	
    if (GetAsyncKeyState(VK_RETURN) & 0x8000) 
		break;
    delay(100);
    }
}
