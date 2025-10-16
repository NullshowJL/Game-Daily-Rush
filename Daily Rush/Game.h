#pragma once
#include "raylib.h"
#include "AnimData.h"
#include "Constants.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Score.h"
#include "HighScoreTable.h"
using namespace std;

class Game
{
public:
	void LoadResource();
	void UnloadResource();
	void InitGame();
	void DrawMenu();
	void DrawScoreBoard();
	bool IsOnGround(const AnimData& data, int windowHeight);
	void ScrollBG();
	void DrawBG();
	void DrawGame();
	void DrawSnail();
	void DrawBoar();
	void DrawBee();
	void DrawHero();
	void DrawHeroHP();
	void DrawScoreOnScreen();
	void DrawWinScreen();
	void DrawLoseScreen();
	void DrawScoreTable();
	void SnailCollCheck();
	void BoarCollCheck();
	void BeeCollCheck();
	void UpdateAnimData(AnimData& data, float deltaTime, int maxFrame);
	void HandleNameTyping(Rectangle textBox, bool mouseOnText, char* name, int& letterCount, int framesCounter);
	void LoadScores(HighScoreTable& table);
	void UpdateNameEntryScene(Rectangle textBox, bool mouseOnText, char* name, int& letterCount, int framesCounter);
	void GameUpdate(float deltaTime, int vel);
	void HeroMove(int& vel, bool& isInAir, float deltaTime);

	Texture2D startMenu;
	Texture2D snail;
	Texture2D boar;
	Texture2D bee;
	Texture2D hero;
	Texture2D background;
	Texture2D midground;
	Texture2D foreground;
	Texture2D collisionBG;

	AnimData snails[sizeOfSnail];
	AnimData boars[sizeOfBoar];
	AnimData bees[sizeOfBee];
	AnimData heroData;

	Score scoreData;
	HighScoreTable table;

	Sound collisionSound;
	Music bgMusic;

	int heroHP;
	//int heroScore;

	bool gameOver{};
	bool pause{};

	// Background parameter
	int bgX{};
	int mgX{};
	int fgX{};
};