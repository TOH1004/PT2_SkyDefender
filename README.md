# Sky Defender
---

**Sky Defender** is a fast-paced 2D aerial shooter inspired by the classic arcade game *1945 Air Force*. Players control a fighter plane from a top-down perspective, surviving waves of enemy aircraft through strategic movement and precise combat. In this project, I collaborated with **Evelyn Ang, Angela Ngu Xin Yi and Tan Xin Tian** under the guidance of Dr Shamini A/P Raja Kumaran.

---
🚀 **Features**

- **Auto-Shooting System:** Automatically fires bullets at controlled intervals, allowing players to focus on movement and strategy.  
- **Dynamic Enemy Behavior:** Enemies move at randomized speeds, requiring constant tactical adjustments.  
- **Immersive Environment:** Continuously scrolling starfield background simulates high-speed flight and depth.  
- **Nostalgic Gameplay:** Combines classic arcade mechanics with updated graphics and enhanced missions.  
---
🎮 **Gameplay & Controls**

- **Movement:** Use arrow keys (← → ↑ ↓) to navigate the aircraft.  
- **Combat:** Aircraft fires automatically; players must position to hit enemies while dodging incoming fire.  
- **Scoring:** Earn 10 points per enemy aircraft destroyed.  
- **Life System:** Start with 3 lives; a life is lost upon collision with an enemy or enemy bullet. Game ends when all lives are lost.  
---
🛠 **Technical Architecture**

The game is built using Object-Oriented Programming (OOP) principles for modularity and scalability.

---
**Core Classes**

- **GameObject (Abstract Base Class):** Defines position (x, y), dimensions, and collision detection (AABB).  
- **Player:** Manages lives, scoring, and movement logic for the user-controlled jet.  
- **Enemy:** Hostile aircraft with randomized speeds and firing patterns.  
- **Bullet:** Handles projectiles fired by both player (upward) and enemies (downward).  
- **Game:** Central system managing the game loop, input processing, collision handling, and rendering.  

---

**OOP Concepts Applied**

- **Inheritance:** Player, Enemy, and Bullet inherit from GameObject.  
- **Polymorphism:** Implemented via pure virtual functions `update()` and `draw()` in GameObject.  
- **Composition/Association:** Game class manages Player and collections of Enemy and Bullet objects.  
