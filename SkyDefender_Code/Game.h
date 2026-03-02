#ifndef GAME_H
#define GAME_H

// System includes
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

// Game component includes
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Constants.h"  // Contains game constants

/**
 * @class Game
 * @brief Main game controller class that manages the game loop and all game objects
 */
class Game {
private:
    // ===== Core Game Attributes =====
    Player* player;                          // Player character
    Bullet* enemyBullets[MAX_ENEMY_BULLETS]; // Array of enemy bullets
    Enemy* enemies[MAX_ENEMIES];             // Array of active enemies
    int enemyBulletCount = 0;        // Current number of active enemy bullets
    int enemyCount = 0;              // Current number of active enemies
    bool gameOver = false;           // Game over flag
    int enemySpawnTimer = 0;         // Timer for enemy spawning
    int backgroundY = 0;             // Background scroll position

    // ===== Private Methods =====
    void processInput();             // Handles player input
    void update();                   // Updates game state
    void draw();                     // Renders game objects
    void cleanup();                  // Cleans up resources

public:
    // ===== Constructor/Destructor =====
    Game();
    ~Game();

    // ===== Main Game Loop =====
    void run();

    // ===== Accessors =====
    // Player access
    Player* getPlayer() const;
    
    // Bullet access
    int getEnemyBulletCount() const;
    Bullet** getEnemyBullets();
    const Bullet* const* getEnemyBullets() const;
    
    // Enemy access
    int getEnemyCount() const;
    Enemy** getEnemies();
    const Enemy* const* getEnemies() const;
    
    // Game state access
    bool isGameOver() const;
    int getEnemySpawnTimer() const;
    int getBackgroundY() const;

    // ===== Mutators =====
    void setGameOver(bool over);
    void setEnemySpawnTimer(int timer);
    void setBackgroundY(int y);
};

#endif // GAME_H