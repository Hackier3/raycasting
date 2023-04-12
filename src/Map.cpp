#include "Map.h"
#include "Player.h"
#include "Defines.h"

void drawMiniMap(){

    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            if (map[y * mapWidth + x] == '#') {
                DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize, BLACK);
            }
            else if (map[y * mapWidth + x] == '.') {
                DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize, WHITE);
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

void calculateWallHeight(Player *player) {

    const float FOV = Player::numberOfRays / Player::rayDestributtionDestiny * (PI / 180); // k¹t widzenia w radianach

    const float halfScreenWidth = screenWidth / 2;
    const float wallHeightScale = 11;

    for (int i = 0; i < Player::numberOfRays; i++) {
        Vector2 rayEnd = player->raysEndCoords.at(i);
        float distance = sqrt(pow(rayEnd.x - player->x, 2) + pow(rayEnd.y - player->y, 2));

        // Wysokoœæ œciany
        float wallHeight = screenHeight * wallHeightScale / distance;

        // Kolor œciany
        if (distance < 25) {
            distance = 25;
        }
        Color wallColor { distance+50, distance+50, distance+50, 255 };

        // Pozycja œciany na ekranie
        float wallX = i * screenWidth / Player::numberOfRays;
        float wallTop = (screenHeight - wallHeight) / 2;
        float wallBot = (screenHeight + wallHeight) / 2;

        // Narysuj liniê
        DrawLine(wallX, wallTop, wallX, wallBot, wallColor);
        DrawLine(wallX, screenHeight, wallX, wallBot, GREEN);
    }
}

void draw3DMap() {

    std::vector<float> wallHeight(Player::numberOfRays);
    for (int i = 0; i < Player::numberOfRays; i++) {
        //DrawRectangle(0, 0, i + screenWidth / mapWidth, wallHeight.at(i), PURPLE);
    }
}