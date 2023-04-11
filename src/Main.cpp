#include <raylib.h>
#include <cmath>
#include <vector>
#include "Player.h"

void drawMap();
std::vector<Vector2> drawVisionRays(Player player);

Player player("images/ircle.png");

int main() {
    InitWindow(screenWidth, screenHeight, "Raylib map");
    std::vector<Vector2> map3D;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dx = sin(player.rotationAngle * PI / 180.0);
        float dy = cos(player.rotationAngle * PI / 180.0) * (-1);

        if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))) {
            player.rotationAngle += 1.5;
        }
        if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))) {
            player.rotationAngle -= 1.5;
        }
        if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)))
        {
            player.x += dx * player.speed;
            player.y += dy * player.speed;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            player.x -= dx * player.speed;
            player.y -= dy * player.speed;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw map
        drawMap();
        map3D = drawVisionRays(player);
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

void drawMap() {

    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            if (map[y * mapWidth + x] == '#') {
                DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize, BLACK);
            }

            // Draw horizontal lines
            DrawLine(x * tileSize, y * tileSize + tileSize, x * tileSize + tileSize, y * tileSize + tileSize, GRAY);
            DrawLine(x * tileSize, y * tileSize + 1, x * tileSize + tileSize, y * tileSize + 1, GRAY);

            // Draw vertical lines
            DrawLine(x * tileSize + tileSize, y * tileSize, x * tileSize + tileSize, y * tileSize + tileSize, GRAY);
            DrawLine(x * tileSize + 1, y * tileSize, x * tileSize + 1, y * tileSize + tileSize, GRAY);
        }
    }
}

std::vector<Vector2> drawVisionRays(Player player) {

    std::vector<float> lineNewPositionX(NUMBER_OF_RAYS, player.x);
    std::vector<float> lineNewPositionY(NUMBER_OF_RAYS, player.y);
    std::vector<Vector2> raysEndCoordds;

    for (float i = 0; i < NUMBER_OF_RAYS; i++)
    {
        float dx = sin((player.rotationAngle + i / RAY_DESTRIBUTION_DESTINY - NUMBER_OF_RAYS / (2 * RAY_DESTRIBUTION_DESTINY) - 1) * PI / 180.0);
        float dy = cos((player.rotationAngle + i / RAY_DESTRIBUTION_DESTINY - NUMBER_OF_RAYS / (2 * RAY_DESTRIBUTION_DESTINY) - 1) * PI / 180.0) * (-1);

        lineNewPositionX.at(i) += dx * player.speed;
        lineNewPositionY.at(i) += dy * player.speed;

        while ((int)lineNewPositionX.at(i) % tileSize != 0 || (int)lineNewPositionY.at(i) % tileSize != 0)
        {
            lineNewPositionX.at(i) += dx;
            lineNewPositionY.at(i) += dy;

            if (map[(int)lineNewPositionX.at(i) / tileSize + (int)(lineNewPositionY.at(i) / tileSize) * mapWidth] != '.')
            {
                break;
            }
        }

        raysEndCoordds.push_back({ lineNewPositionX.at(i), lineNewPositionY.at(i) });
        DrawLine(player.x, player.y, lineNewPositionX.at(i), lineNewPositionY.at(i), DARKBLUE);
    }

    return raysEndCoordds;
}