#include <raylib.h>
#include <cmath>
#include "Defines.h"
#include "Player.h"
#include "Map.h"

int main() {

    InitWindow(screenWidth, screenHeight, "Raylib map");

    Player player("images/circle.png");
    // std::vector<Vector2> map3D;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        player.movement();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        drawMap();
        player.calculateRaysCoords();
        player.drawVisionRays();
        player.drawPlayer();

        //// Narysuj mape 3D
        //for (int i = 0; i < map3D.size(); i++)
        //{
        //    float c = sqrt(pow(map3D.at(i).x - playerX, 2) + pow(map3D.at(i).y - playerY, 2));
        //    DrawRectangle(i, screenHeight/2 - 800/c, i + screenWidth / map3D.size(), 1600/c, PURPLE);
        //}

        EndDrawing();
    }

    CloseWindow();
    return 0;
}