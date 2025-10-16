#include "Game.h"

void Game::LoadResource()
{
	startMenu = LoadTexture("Assets/Background/Start.png");
	snail = LoadTexture("Assets/Obstacle/Snail-Sheet.png");
    boar = LoadTexture("Assets/Obstacle/Boar-Sheet.png");
    bee = LoadTexture("Assets/Obstacle/Bee-Sheet.png");
    hero = LoadTexture("Assets/Character/char_red_1.png");
    background = LoadTexture("Assets/Background/BG001.png");
    midground = LoadTexture("Assets/Background/BG002.png");
    foreground = LoadTexture("Assets/Background/BG003.png");
    collisionBG = LoadTexture("Assets/Background/purple.png");

    collisionSound = LoadSound("Assets/Audio/hit.mp3");
    bgMusic = LoadMusicStream("Assets/Audio/bg.mp3");
}

void Game::UnloadResource()
{
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    UnloadTexture(hero);
    UnloadTexture(snail);
    UnloadTexture(boar);
    UnloadTexture(bee);
    UnloadTexture(startMenu);
    UnloadTexture(collisionBG);

    UnloadSound(collisionSound);
    UnloadMusicStream(bgMusic);
}

void Game::InitGame()
{
    // Snail
    for (int i = 0; i < sizeOfSnail; i++)
    {
        snails[i].sourceRec.x = 0.f;
        snails[i].sourceRec.y = 0.f;
        snails[i].sourceRec.width = static_cast<float>(snail.width / 8);
        snails[i].sourceRec.height = static_cast<float>(snail.height);
        snails[i].pos.x = static_cast<float>(windowWidth + GetRandomValue(0, 2000) * i);
        snails[i].pos.y = static_cast<float>(windowHeight - snails[i].sourceRec.height * obstacleScale - groundOffset);
        snails[i].frame = 0;    // Start from frame 0
        snails[i].updateTime = 1.f / 12.f;
        snails[i].runningTime = 0.f;
        snails[i].hurtPower = 15;
        snails[i].isCollided = false;
        snails[i].isPassed = false;
    }

    // Boar
    for (int i = 0; i < sizeOfBoar; i++)
    {
        boars[i].sourceRec.x = 0.f;
        boars[i].sourceRec.y = 0.f;
        boars[i].sourceRec.width = static_cast<float>(boar.width / 6);
        boars[i].sourceRec.height = static_cast<float>(boar.height);
        boars[i].pos.x = static_cast<float>(windowWidth + GetRandomValue(4000, 8000) * i);
        boars[i].pos.y = static_cast<float>(windowHeight - boars[i].sourceRec.height * obstacleScale - groundOffset);
        boars[i].frame = 0;
        boars[i].updateTime = 1.f / 24.f;
        boars[i].runningTime = 0.f;
        boars[i].hurtPower = 30;
        boars[i].isCollided = false;
        boars[i].isPassed = false;
    }

    // Bee
    for (int i = 0; i < sizeOfBee; i++)
    {
        bees[i].sourceRec.x = 0.f;
        bees[i].sourceRec.y = 0.f;
        bees[i].sourceRec.width = static_cast<float>(bee.width / 4);
        bees[i].sourceRec.height = static_cast<float>(bee.height);
        bees[i].pos.x = static_cast<float>(windowWidth + GetRandomValue(8000, 10000) * i);
        bees[i].pos.y = static_cast<float>(windowHeight - bees[i].sourceRec.height * obstacleScale - 3 * groundOffset);
        bees[i].frame = 0;
        bees[i].updateTime = 1.f / 24.f;
        bees[i].runningTime = 0.f;
        bees[i].hurtPower = 50;
        bees[i].isCollided = false;
        bees[i].isPassed = false;
    }

    // Hero
    heroHP = 100;
    scoreData.score = 0;

    heroData.sourceRec.width = static_cast<float>(hero.width / 8);
    heroData.sourceRec.height = static_cast<float>(hero.height / 11);
    heroData.sourceRec.x = 0.f;
    heroData.sourceRec.y = static_cast<float>(hero.height * 2 / 11);
    heroData.pos.x = static_cast<float>(static_cast<float>(windowWidth / 2) - heroData.sourceRec.width / 2 * heroScale);
    heroData.pos.y = static_cast<float>(windowHeight - heroData.sourceRec.height * heroScale - groundOffset);
    heroData.frame = 0;
    heroData.updateTime = 1.f / 12.f;
    heroData.runningTime = 0.f;
}

void Game::DrawMenu()
{
    DrawTextureEx(startMenu, Vector2{}, 0.f, 1.7f, WHITE);
    DrawText("Individual Assignment", windowWidth / 4, windowHeight / 3, 40, GRAY);
    DrawText("Press G to Start Game", windowWidth / 4, windowHeight / 3 + 60, 30, BLACK);
}

void Game::DrawScoreBoard()
{
    DrawTextureEx(startMenu, Vector2{}, 0.f, 1.7f, WHITE);
    DrawText("High Score Table", windowWidth / 2 - MeasureText("High Score Table", 30) / 2, windowHeight / 8, 30, DARKGREEN);

    DrawText("POS", (int)(windowWidth * 0.75 - MeasureText("POS", 20) / 2), (int)windowHeight / 6 + heightOffset, 20, DARKGRAY);
    DrawText("NAME", (int)(windowWidth / 4 - MeasureText("NAME", 20) / 2), (int)windowHeight / 6 + heightOffset, 20, DARKGRAY);
    DrawText("SCORE", (int)(windowWidth / 2 - MeasureText("SCORE", 20) / 2), (int)windowHeight / 6 + heightOffset, 20, DARKGRAY);

    // Update scores 
    for (int i = 0; i < table.scores.size() && i < showScoreNum; i++)
    {
        string rank = "  ";
        rank.append(to_string(i + 1));
        DrawText(rank.c_str(), (int)(windowWidth * 0.75 - MeasureText("POS", 20) / 2), (int)windowHeight / 6 + 80 + heightOffset * i, 20, DARKGRAY);

        Score score = table.scores[i];
        DrawText(table.scores[i].name.c_str(), (int)(windowWidth / 4 - MeasureText(table.scores[i].name.c_str(), 20) / 2), (int)windowHeight / 6 + 80 + heightOffset * i, 20, DARKGRAY);
        DrawText((to_string(table.scores[i].score)).c_str(), (int)(windowWidth / 2 - MeasureText((to_string(table.scores[i].score)).c_str(), 20) / 2), (int)windowHeight / 6 + 80 + heightOffset * i, 20, DARKGRAY);
    }
}

bool Game::IsOnGround(const AnimData& data, int winHeight)
{
    return data.pos.y >= winHeight - data.screenRec.height - groundOffset;
}

void Game::ScrollBG()
{
    if (bgX <= -background.width)
    {
        bgX = 0;
    }

    if (mgX <= -background.width)
    {
        mgX = 0;
    }

    if (fgX <= -background.width)
    {
        fgX = 0;
    }
}

void Game::DrawBG()
{
    DrawTexture(background, bgX, 0, WHITE);
    DrawTexture(background, bgX + background.width, 0, WHITE);

    DrawTexture(midground, mgX, static_cast<int>(background.height / 1.8), WHITE);
    DrawTexture(midground, mgX + midground.width, static_cast<int>(background.height / 1.8), WHITE);

    DrawTexture(foreground, fgX, windowHeight - foreground.height, WHITE);
    DrawTexture(foreground, fgX + foreground.width, windowHeight - foreground.height, WHITE);
}

void Game::DrawGame()
{    
    DrawBG();
    DrawSnail();
    DrawBoar();
    DrawBee();
    DrawHero();
}

void Game::DrawSnail()
{
    for (int i = 0; i < sizeOfSnail; i++)
    {
        snails[i].screenRec.x = snails[i].pos.x;
        snails[i].screenRec.y = snails[i].pos.y;
        snails[i].screenRec.width = snails[i].sourceRec.width * obstacleScale;
        snails[i].screenRec.height = snails[i].sourceRec.height * obstacleScale;
    }

    for (int i = 0; i < sizeOfSnail; i++)
    {
        snails[i].sourceRec.x = static_cast<float>(snails[i].frame * snail.width / 8);
        DrawTexturePro(snail, snails[i].sourceRec, snails[i].screenRec, Vector2{}, 0.f, WHITE);
    }
}

void Game::DrawBoar()
{
    for (int i = 0; i < sizeOfBoar; i++)
    {
        boars[i].screenRec.x = boars[i].pos.x;
        boars[i].screenRec.y = boars[i].pos.y;
        boars[i].screenRec.width = boars[i].sourceRec.width * obstacleScale;
        boars[i].screenRec.height = boars[i].sourceRec.height * obstacleScale;
    }

    for (int i = 0; i < sizeOfBoar; i++)
    {
        boars[i].sourceRec.x = static_cast<float>(boars[i].frame * boar.width / 6);
        DrawTexturePro(boar, boars[i].sourceRec, boars[i].screenRec, Vector2{}, 0.f, WHITE);
    }
}

void Game::DrawBee()
{
    for (int i = 0; i < sizeOfBee; i++)
    {
        bees[i].screenRec.x = bees[i].pos.x;
        bees[i].screenRec.y = bees[i].pos.y;
        bees[i].screenRec.width = bees[i].sourceRec.width * obstacleScale;
        bees[i].screenRec.height = bees[i].sourceRec.height * obstacleScale;
    }

    for (int i = 0; i < sizeOfBee; i++)
    {
        bees[i].sourceRec.x = static_cast<float>(bees[i].frame * bee.width / 4);
        DrawTexturePro(bee, bees[i].sourceRec, bees[i].screenRec, Vector2{}, 0.f, WHITE);
    }
}

void Game::DrawHero()
{
    heroData.screenRec.width = heroData.sourceRec.width * heroScale;
    heroData.screenRec.height = heroData.sourceRec.height * heroScale;
    heroData.screenRec.x = heroData.pos.x;
    heroData.screenRec.y = heroData.pos.y;

    heroData.sourceRec.x = static_cast<float>(heroData.frame * hero.width / 8);
    DrawTexturePro(hero, heroData.sourceRec, heroData.screenRec, Vector2{}, 0.f, WHITE);
}

void Game::DrawHeroHP()
{
    string heroHealth = "Hero's current HP: ";
    heroHealth.append(to_string(heroHP));
    DrawText(heroHealth.c_str(), windowWidth / 10, windowHeight / 8, 20, BLACK);
}

void Game::DrawScoreOnScreen()
{
    string heroS = "Your score: ";
    string hScore = "Hi score: ";
    heroS.append(to_string(scoreData.score));
    DrawText(heroS.c_str(), windowWidth / 10, windowHeight / 8 + 30, 20, YELLOW);

    Score hiScore;
    if (table.scores.size() == 0)
    {
        hiScore.score = 0;
        hiScore.name = "";
    }
    else
    {
        hiScore = table.scores[0];
    }
    hScore.append(to_string(hiScore.score));
    DrawText(hScore.c_str(), windowWidth / 10, windowHeight / 8 + 60, 20, PURPLE);
}

void Game::DrawWinScreen()
{
    DrawText("You Win!", windowWidth / 3, windowHeight / 3, 60, YELLOW);
    DrawText("Press Enter to restart", windowWidth / 4, windowHeight / 3 + 80, 40, BLACK);
    DrawText("Press B to Show High Score Table", windowWidth / 4, windowHeight / 3 + 140, 20, BEIGE);
}

void Game::DrawLoseScreen()
{
    DrawText("Game over!", windowWidth / 3, windowHeight / 3, 60, RED);
    DrawText("Press Enter to Restart", windowWidth / 4, windowHeight / 3 + 80, 40, WHITE);
    DrawText("Press B to Show High Score Table", windowWidth / 4, windowHeight / 3 + 140, 20, BEIGE);
}

void Game::DrawScoreTable()
{
    DrawTextureEx(startMenu, Vector2{}, 0.f, 1.7f, WHITE);
    DrawText("High Score Table", (int)(windowWidth / 2 - MeasureText("High Score Table", 30) / 2), (int)windowHeight / 8, 30, DARKGREEN);
    DrawText("Press G To Restart Game", (int)(windowWidth / 2 - MeasureText("Press ENTER To Restart Game", 30) / 2), (int)windowHeight, 30, DARKBROWN);

    DrawText("POS", (int)(windowWidth * 0.75 - MeasureText("POS", 20) / 2), (int)windowHeight / 6 + heightOffset, 20, DARKGRAY);
    DrawText("NAME", (int)(windowWidth / 4 - MeasureText("NAME", 20) / 2), (int)windowHeight / 6 + heightOffset, 20, DARKGRAY);
    DrawText("SCORE", (int)(windowWidth / 2 - MeasureText("SCORE", 20) / 2), (int)windowHeight / 6 + heightOffset, 20, DARKGRAY);
}

void Game::SnailCollCheck()
{
    // Check collision with snail
    for (int i = 0; i < sizeOfSnail; i++)
    {
        if (!snails[i].isCollided)
        {
            Rectangle snailCollisionRec{
            snails[i].pos.x + collisionObstacleOffset,
            snails[i].pos.y + collisionObstacleOffset,
            snails[i].screenRec.width - 2 * collisionObstacleOffset,
            snails[i].screenRec.height - 2 * collisionObstacleOffset
            };
            Rectangle heroCollisionRec{
               heroData.pos.x + collisionHeroOffset,
               heroData.pos.y + collisionHeroOffset,
               heroData.screenRec.width - 2 * collisionHeroOffset,
               heroData.screenRec.height - 2 * collisionHeroOffset
            };

            if (CheckCollisionRecs(snailCollisionRec, heroCollisionRec))
            {
                heroHP -= snails[i].hurtPower;
                PlaySound(collisionSound);
                snails[i].isCollided = true;
            }
        }

        // Add score
        if (!snails[i].isPassed &&
            heroData.screenRec.x > snails[i].pos.x + snails[i].screenRec.width &&
            !snails[i].isCollided)
        {
            scoreData.score += 10;
            snails[i].isPassed = true;
        }
    }
}

void Game::BoarCollCheck()
{
    // Check collision with boar
    for (int i = 0; i < sizeOfBoar; i++)
    {
        if (!boars[i].isCollided)
        {
            Rectangle snailCollisionRec{
            boars[i].pos.x + collisionObstacleOffset,
            boars[i].pos.y + collisionObstacleOffset,
            boars[i].screenRec.width - 2 * collisionObstacleOffset,
            boars[i].screenRec.height - 2 * collisionObstacleOffset
            };
            Rectangle heroCollisionRec{
               heroData.pos.x + collisionHeroOffset,
               heroData.pos.y + collisionHeroOffset,
               heroData.screenRec.width - 2 * collisionHeroOffset,
               heroData.screenRec.height - 2 * collisionHeroOffset
            };

            if (CheckCollisionRecs(snailCollisionRec, heroCollisionRec))
            {
                heroHP -= boars[i].hurtPower;
                PlaySound(collisionSound);
                boars[i].isCollided = true;
            }
        }

        // Add score
        if (!boars[i].isPassed &&
            heroData.screenRec.x > boars[i].pos.x + boars[i].screenRec.width &&
            !boars[i].isCollided)
        {
            scoreData.score += 20;
            boars[i].isPassed = true;
        }
    }
}

void Game::BeeCollCheck()
{
    // Check collision with bee
    for (int i = 0; i < sizeOfBee; i++)
    {
        if (!bees[i].isCollided)
        {
            Rectangle snailCollisionRec{
            bees[i].pos.x + collisionObstacleOffset,
            bees[i].pos.y + collisionObstacleOffset,
            bees[i].screenRec.width - 2 * collisionObstacleOffset,
            bees[i].screenRec.height - 2 * collisionObstacleOffset
            };
            Rectangle heroCollisionRec{
               heroData.pos.x + collisionHeroOffset,
               heroData.pos.y + collisionHeroOffset,
               heroData.screenRec.width - 2 * collisionHeroOffset,
               heroData.screenRec.height - 2 * collisionHeroOffset
            };

            if (CheckCollisionRecs(snailCollisionRec, heroCollisionRec))
            {
                heroHP -= bees[i].hurtPower;
                PlaySound(collisionSound);
                bees[i].isCollided = true;
            }
        }

        // Add score
        if (!bees[i].isPassed &&
            heroData.screenRec.x > bees[i].pos.x + bees[i].screenRec.width &&
            !bees[i].isCollided)
        {
            scoreData.score += 30;
            bees[i].isPassed = true;
        }
    }
}

void Game::UpdateAnimData(AnimData& data, float deltaTime, int frameCount)
{
    //update running time
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.f;
        // Update animation frame
        data.sourceRec.x = data.frame * data.sourceRec.width;
        data.frame = (data.frame + 1) % frameCount;
    }
}

void Game::HandleNameTyping(Rectangle textBox, bool mouseOnText, char* name, int& letterCount, int framesCounter)
{
    if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
    else mouseOnText = false;

    if (mouseOnText)
    {
        // Set the window's cursor to the I-Beam
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        // Get char pressed (unicode character) on the queue
        int key = GetCharPressed();

        // Check if more characters have been pressed on the same frame
        while (key > 0)
        {
            // Only allow keys in range [65..122]
            if ((key >= 65) && (key <= 122) && (letterCount < MAX_INPUT_CHARS))
            {
                name[letterCount] = (char)key;
                name[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
                letterCount++;
            }

            key = GetCharPressed();  // Check next character in the queue
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            letterCount--;
            if (letterCount < 0) letterCount = 0;
            name[letterCount] = '\0';
        }
    }
    else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    if (mouseOnText) framesCounter++;
    else framesCounter = 0;
}

void Game::LoadScores(HighScoreTable& tb)
{
    tb.scores.clear();

    ifstream inFile("Scores.txt");
    if (!inFile) return;

    string name = "";
    int scoreVal = 0;

    while (inFile >> name >> scoreVal)
    {
        Score s;
        s.name = name;
        s.score = scoreVal;
        tb.scores.push_back(s);
    } 

    sort(tb.scores.begin(), tb.scores.end(),
        [](const Score& a, const Score& b)
        {
            if (a.score != b.score) return a.score > b.score;
            return a.name < b.name;
        });
}

void Game::UpdateNameEntryScene(Rectangle textBox, bool mouseOnText, char* name, int& letterCount, int framesCounter)
{
    DrawText("Please input your name:", 240, 140, 20, GRAY);

    DrawRectangleRec(textBox, BLACK);
    if (mouseOnText)
    {
        DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
    }
    else
    {
        DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);
    }

    DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, RAYWHITE);

    DrawText(TextFormat("Max letters: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);

    if (mouseOnText)
    {
        if (letterCount < MAX_INPUT_CHARS)
        {
            // Draw blinking underscore char
            if (((framesCounter / 20) % 2) == 0)
            {
                DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
            }
        }
        else
        {
            DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
        }
    }

    DrawText("Press Enter to Confirm", windowWidth / 4, windowHeight / 2 + 100, 20, BLACK);
}

void Game::GameUpdate(float deltaTime, int vel)
{
    // Update backgrounds
    bgX -= static_cast<int>(30 * deltaTime);
    mgX -= static_cast <int>(90 * deltaTime);
    fgX -= static_cast <int>(140 * deltaTime);
    ScrollBG();

    // Update snail position and animation
    for (int i = 0; i < sizeOfSnail; i++)
    {
        snails[i].pos.x += snailVel * deltaTime;
        UpdateAnimData(snails[i], deltaTime, 8);
        snails[i].screenRec = {
            snails[i].pos.x, snails[i].pos.y,
            snails[i].sourceRec.width * obstacleScale,
            snails[i].sourceRec.height * obstacleScale
        };
    }

    // Update boar position and animation
    for (int i = 0; i < sizeOfBoar; i++)
    {
        boars[i].pos.x += boarVel * deltaTime;
        UpdateAnimData(boars[i], deltaTime, 6);
        boars[i].screenRec = {
            boars[i].pos.x, boars[i].pos.y,
            boars[i].sourceRec.width * obstacleScale,
            boars[i].sourceRec.height * obstacleScale
        };
    }

    // Update bee position and animation
    for (int i = 0; i < sizeOfBee; i++)
    {
        bees[i].pos.x += beeVel * deltaTime;
        UpdateAnimData(bees[i], deltaTime, 4);
        bees[i].screenRec = {
            bees[i].pos.x, bees[i].pos.y,
            bees[i].sourceRec.width * obstacleScale,
            bees[i].sourceRec.height * obstacleScale
        };
    }

    // Update hero position and screen rectangle before physics/collision
    heroData.pos.y += vel * deltaTime;
    heroData.screenRec = {
            heroData.pos.x, heroData.pos.y,
            heroData.sourceRec.width * heroScale,
            heroData.sourceRec.height * heroScale
    };

    SnailCollCheck();
    BoarCollCheck();
    BeeCollCheck();
}

void Game::HeroMove(int& vel, bool& isInAir, float deltaTime)
{
    // Ensure hero screen rect is valid before ground check
    heroData.screenRec.width = heroData.sourceRec.width * heroScale;
    heroData.screenRec.height = heroData.sourceRec.height * heroScale;

    if (IsOnGround(heroData, windowHeight))
    {
        // On the ground
        vel = 0;
        isInAir = false;
    }
    else // In the air
    {
        // Apply gravity
        vel += static_cast<int>(gravity * deltaTime);
        isInAir = true;
    }

    // Jump check
    if (IsKeyPressed(KEY_SPACE) && !isInAir)
    {
        vel += jumpVel;
    }

    if (!isInAir)
    {
        UpdateAnimData(heroData, deltaTime, 8);
    }
}

