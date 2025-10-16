#pragma once
#include "raylib.h"
#include "Constants.h"
#include <vector>
using namespace std;

class Collision
{
public:
	void InitGraphics();
	void Select();
	void Draw();
	void RecsCollCheck();
	void CirclesCollCheck();
	void RecCircleCollCheck();
	void LineCircleCollCheck();

	vector<Rectangle> recs;
	vector<Vector2> circlesPos;
	Vector2 linePosStart{ 700,200 };
	Vector2 linePosEnd{ 800,300 };
	// Set colors
	Color colors[2] = { YELLOW,RED };
	bool isCollided = false;
};
