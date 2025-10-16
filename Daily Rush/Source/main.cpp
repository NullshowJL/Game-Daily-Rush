#include <string>
#include "Game.h"
#include "Collision.h"
#include "Constants.h"
#include "HighScoreTable.h"

bool CompareScores(const Score& a, const Score& b);
void SaveScores(const HighScoreTable& table);
void AddHighScore(HighScoreTable& table, int score, const string& name);

int main(void)
{
    Game game = {};
    Collision collision = {};

    InitWindow(windowWidth, windowHeight, "Running Game's Window!");

    InitAudioDevice();

    int currentScene = MENU;

    bool isInAir{}; // Is hero in the air
    int velocity{};

    // Variables of collision detection
    Rectangle movingRec{ 0, windowHeight - recHeight, recWidth, recHeight };

    // Load resources
    game.LoadResource();

    PlayMusicStream(game.bgMusic);

    game.InitGame();

    // For the name input at the start 
    char name[MAX_INPUT_CHARS + 1] = "\0";
    int letterCount = 0;

    Rectangle textBox = { windowWidth / 2.0f - 100, 180, 225, 50 };
    bool mouseOnText = false;

    int framesCounter = 0;

    // Finish line
    float finishLineOfSnail{ game.snails[sizeOfSnail - 1].pos.x };
    float finishLineOfBoar{ game.boars[sizeOfBoar - 1].pos.x };
    float finishLineOfBee{ game.bees[sizeOfBee - 1].pos.x };

    game.LoadScores(game.table);

    collision.InitGraphics();

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())    
    {
        const float dT{ GetFrameTime() };

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        switch (currentScene)
        {
        case MENU:
        {
            if (IsKeyDown(KEY_G))
            {
                currentScene = NAMEENTRY;
            }

            game.DrawMenu();
            break;
        }
        case NAMEENTRY:
        {
            game.HandleNameTyping(textBox, mouseOnText, name, letterCount, framesCounter);
            DrawTextureEx(game.startMenu, Vector2{}, 0.f, 1.7f, WHITE);
            if (IsKeyDown(KEY_ENTER))
            {
                currentScene = GAME;
            }

            // Input player's name
            game.UpdateNameEntryScene(textBox, mouseOnText, name, letterCount, framesCounter);
            break;
        }

        case GAME:
        {
            // Play background music
            UpdateMusicStream(game.bgMusic);

            // ------ draw -------
            game.DrawGame();
            // Draw hero's HP
            game.DrawHeroHP();
            // Draw player's score and the highest score
            game.DrawScoreOnScreen();

            // Game logic when game isn't over
            if (!game.gameOver)
            {
                // Update game
                if (IsKeyPressed(KEY_P))
                {
                    game.pause = !game.pause;
                }

                // Game running state
                if (!game.pause)
                {
                    // Game update                 
                    game.GameUpdate(dT, velocity);
                    game.HeroMove(velocity, isInAir, dT);

                    // Update finish line
                    finishLineOfSnail += snailVel * dT;
                    finishLineOfBoar += boarVel * dT;
                    finishLineOfBee += beeVel * dT;

                    // Winning/ lose condition
                    if (game.heroData.pos.x > (finishLineOfSnail + finishLineOffset) && 
                        game.heroData.pos.x > (finishLineOfBoar + finishLineOffset) &&
                        game.heroData.pos.x  > (finishLineOfBee + finishLineOffset))
                    {
                        if (IsKeyPressed(KEY_ENTER))
                        {
                            game.InitGame();
                            PlayMusicStream(game.bgMusic);
                            game.gameOver = false;
                        }

                        if (IsKeyPressed(KEY_B))
                        {
                            currentScene = SHOWSCOREBOARD;
                        }

                        game.gameOver = true;
                        AddHighScore(game.table, game.scoreData.score, name);
                    }

                    // Lose the game
                    if (game.heroHP <= 0)
                    {
                        game.heroHP = 0;
                        game.gameOver = true;
                        AddHighScore(game.table, game.scoreData.score, name);
                    }
                }              
            }
            else
            {
                StopMusicStream(game.bgMusic);
                
                if (IsKeyPressed(KEY_ENTER))
                {
                    game.InitGame();
                    PlayMusicStream(game.bgMusic);
                    game.gameOver = false;
                }

                if (IsKeyPressed(KEY_B))
                {
                    currentScene = SHOWSCOREBOARD;
                }
                if (game.heroHP <= 0)
                {
                    game.DrawLoseScreen();
                }
                else
                {
                    game.DrawWinScreen();
                }
            }

            if (game.pause)
            {
                DrawText("Pause", windowWidth / 3, windowHeight / 3, 40, RED);
            }
            break;
        }  

        case SHOWSCOREBOARD:
        {            
            game.DrawScoreBoard();
            break;            
        }
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    game.UnloadResource();
    
    CloseAudioDevice();

    CloseWindow();      
    //--------------------------------------------------------------------------------------
    return 0;
}

bool CompareScores(const Score& a, const Score& b)
{
    return a.score > b.score;
}

void SaveScores(const HighScoreTable& table)
{
    ofstream outFile;
    Score highScore;
    outFile.open("Scores.txt");
    if (outFile.is_open())
    {  
        if (table.scores.size() == 0)
        {
            return;
        }
        else
        {
            for (int i = 0; i < table.scores.size(); i++)
            {
                outFile << table.scores[i].name << " " << table.scores[i].score << endl;
            }
        }
        
        outFile.close();
    }
}

void AddHighScore(HighScoreTable& table, int score, const string& name)
{
    Score highScore;
    highScore.score = score;
    highScore.name = name;
    table.scores.push_back(highScore);

    sort(table.scores.begin(), table.scores.end(), CompareScores);

    SaveScores(table);
}


