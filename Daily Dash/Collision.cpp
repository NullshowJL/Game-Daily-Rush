#include "Collision.h"
#include "cmath"

void Collision::InitGraphics()
{
    // Set each rec's position
    for (int i = 0; i < 2; i++)
    {
        Rectangle rec{};
        rec.width = 80;
        rec.height = 50;
        rec.x = static_cast<float>(400 + 100 * (i % 2));
        rec.y = static_cast<float>(150 + 100 * (i / 2));
        recs.push_back(rec);
    }

    // Set each circle's position
    for (int i = 0; i < 2; i++)
    {
        Vector2 circlePos{};
        circlePos.x = static_cast<float>(300 + 200 * (i % 2));
        circlePos.y = static_cast<float>(300 + 200 * (i / 2));
        circlesPos.push_back(circlePos);
    }
}

void Collision::RecsCollCheck()
{
    // Show recs' collision
    for (int i = 0; i < recs.size() - 1; i++)
    {      
        isCollided = (recs[i].x < recs[i + 1].x + recs[i + 1].width &&
            recs[i].x + recs[i].width > recs[i + 1].x &&
            recs[i].y < recs[i + 1].y + recs[i + 1].height &&
            recs[i].y + recs[i].height > recs[i + 1].y);
           
        if (isCollided)
        {
            DrawText("Collided!", static_cast<int>(windowWidth * 0.85), static_cast<int>(windowHeight * 0.1), 30, WHITE);
            break;
        }
    }
}

void Collision::CirclesCollCheck()
{
    // Show circles' collision
    for (int i = 0; i < circlesPos.size() - 1; i++)
    {       
        isCollided= sqrt(pow(circlesPos[i].x - circlesPos[i+1].x, 2) + pow(circlesPos[i].y - circlesPos[i + 1].y, 2)) <= circleRadius * 2 ? true : false;
        
        if (isCollided)
        {
            DrawText("Collided!", static_cast<int>(windowWidth * 0.85), static_cast<int>(windowHeight * 0.1), 30, WHITE);
            break;
        }
    }
}

void Collision::RecCircleCollCheck()
{
    // Show circle's collision with rectangles
    for (int i = 0; i < circlesPos.size(); i++)
    {
        for (int j = 0; j < recs.size(); j++)
        {
            isCollided = (recs[j].y - circlesPos[i].y < circleRadius &&
                circlesPos[i].y - (recs[j].y+recs[j].height) < circleRadius &&
                recs[j].x - circlesPos[i].x < circleRadius &&
                circlesPos[i].x - (recs[j].x + recs[j].width) < circleRadius);

            if (isCollided)
            {
                DrawText("Collided!", static_cast<int>(windowWidth * 0.85), static_cast<int>(windowHeight * 0.1), 30, WHITE);
                break;
            }
        }
    }
}

void Collision::LineCircleCollCheck()
{
    for (int i = 0; i < circlesPos.size(); i++)
    {
        double disToSeg = fabs(((linePosStart.y - linePosEnd.y) * circlesPos[i].x - (linePosStart.x - linePosEnd.x) * circlesPos[i].y + (linePosStart.x * linePosEnd.y - linePosEnd.x * linePosStart.y)) / sqrt(pow(linePosStart.y - linePosEnd.y, 2) + pow(linePosStart.x - linePosEnd.x, 2)));
        double disToSegStartPoint = sqrt((circlesPos[i].x - linePosStart.x) * (circlesPos[i].x - linePosStart.x) + (circlesPos[i].y - linePosStart.y) * (circlesPos[i].y - linePosStart.y));
        double disToSegEndPoint = sqrt((circlesPos[i].x - linePosEnd.x) * (circlesPos[i].x - linePosEnd.x) + (circlesPos[i].y - linePosEnd.y) * (circlesPos[i].y - linePosEnd.y));

        isCollided = (disToSeg <= circleRadius && circlesPos[i].x >= linePosStart.x && circlesPos[i].x <= linePosEnd.x && circlesPos[i].y >= linePosStart.y && circlesPos[i].y <= linePosEnd.y )||
            disToSegStartPoint <= circleRadius ||
            disToSegEndPoint <= circleRadius;

        if (isCollided)
        {
            DrawText("Collided!", static_cast<int>(windowWidth * 0.85), static_cast<int>(windowHeight * 0.1), 30, WHITE);
            break;
        }
    }
}



void Collision::Select()
{
    // Pick a rec with mouse
    for (int i = 0; i < recs.size(); i++)
    {
        if (IsKeyDown(KEY_ONE))
        {
            recs[0].x = GetMousePosition().x - recs[0].width / 2;
            recs[0].y = GetMousePosition().y - recs[0].height / 2;
        }
        if (IsKeyDown(KEY_TWO))
        {
            recs[1].x = GetMousePosition().x - recs[1].width / 2;
            recs[1].y = GetMousePosition().y - recs[1].height / 2;
        }
    }

    // Pick a circle with mouse
    for (int i = 0; i < circlesPos.size(); i++)
    {
        if (IsKeyDown(KEY_THREE))
        {
            circlesPos[0].x = GetMousePosition().x;
            circlesPos[0].y = GetMousePosition().y;
        }
        if (IsKeyDown(KEY_FOUR))
        {
            circlesPos[1].x = GetMousePosition().x;
            circlesPos[1].y = GetMousePosition().y;
        }
    }
}

void Collision::Draw()
{
    // Recs
    for (int i = 0; i < recs.size(); i++)
    {
        DrawRectangleRec(recs[i], colors[i]);
    }

    // Circles
    for (int i = 0; i < circlesPos.size(); i++)
    {
        DrawCircle(static_cast<int>(circlesPos[i].x), static_cast<int>(circlesPos[i].y), circleRadius, colors[i]);
    }

    // Line
    DrawLineEx(linePosStart, linePosEnd, lineThickness, YELLOW);
}


