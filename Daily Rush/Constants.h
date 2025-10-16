#pragma once

#define MAX_INPUT_CHARS 3

// Window parameters
const int windowWidth{ 1012 };
const int windowHeight{ 396 };

// Hero parameters
const float heroScale{ 4.f };
const int groundOffset{ 30 };
const float collisionHeroOffset{ 58 };
const int gravity{ 1000 }; // Acceleration due to gravity: (pixels/s)/s
const int jumpVel{ -650 }; //pixels/s

// Obstacle parameters
const float obstacleScale{ 2.5f };
const float collisionObstacleOffset{ 20 };
const int sizeOfSnail{ 8 };
const int sizeOfBoar{ 6 };
const int sizeOfBee{ 3 };
// Boar X velocity (pixels/s)
const int boarVel{ -400 };
// Bee X velocity (pixels/s)
const int beeVel{ -600 };
// Snail X velocity (pixels/s)
const int snailVel{ -200 };

// Menu related
enum GameScene
{
	MENU,
	COLLISION,
	NAMEENTRY,
	GAME,
	SHOWSCOREBOARD
};

const int heightOffset{ 40 };
const int showScoreNum = 5;
const float finishLineOffset{ 300.f };

// Collision detection task related
const float circleRadius{ 40.f };

const int recWidth{ 100 };
const int recHeight{ 80 };

const float lineThickness{ 5.f };






