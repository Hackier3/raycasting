﻿#include <raylib.h>
#include "Defines.h"
#include "Player.h"
#include "Map.h"

int main() {

    InitWindow(screenWidth, screenHeight, "Raylib map");

    Player player("images/rsz_circle.png");
    SetTargetFPS(60);
 
    while (!WindowShouldClose())
    {
        player.movement();
        player.calculateRaysCoords();
        calculateWallHeight(&player, "images/cobblestone.png");

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            drawMiniMap();
            player.drawVisionRays();
            player.drawPlayer();
            // draw3DMap();
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}