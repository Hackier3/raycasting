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
    const float wallHeightScale = 30;
    const float maxDistance = 20;

    for (int i = 0; i < Player::numberOfRays; i++) {
        Vector2 rayEnd = player->raysEndCoords.at(i);
        float distance = sqrt(pow(rayEnd.x - player->x, 2) + pow(rayEnd.y - player->y, 2));

        // Wysokoœæ œciany
        float wallHeight = screenHeight * wallHeightScale / distance;

        // Wspó³rzêdne œciany
        float wallTop = (screenHeight - wallHeight) / 2;
        float wallBottom = (screenHeight + wallHeight) / 2;

        // Kolor œciany
        Color wallColor = RED;
        if (distance > maxDistance) {
            wallColor = GRAY;
            distance = maxDistance;
        }

        // Pozycja œciany na ekranie
        float wallScreenX = i * (screenWidth / Player::numberOfRays);
        float wallScreenTop = wallTop;
        float wallScreenBottom = wallBottom;

        // Narysuj liniê
        DrawLine(wallScreenX, wallScreenTop, wallScreenX, wallScreenBottom, wallColor);
    }
}

void draw3DMap() {

    std::vector<float> wallHeight(Player::numberOfRays);
    for (int i = 0; i < Player::numberOfRays; i++) {
        //DrawRectangle(0, 0, i + screenWidth / mapWidth, wallHeight.at(i), PURPLE);
    }
}