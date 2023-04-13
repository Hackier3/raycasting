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

void calculateWallHeight(Player* player, Texture2D texture) {

    const float halfScreenWidth = screenWidth / 2;
    const float wallHeightScale = 11;
    const float brightnessScale = 100;

    for (int i = 0; i < Player::numberOfRays; i++) {
        Vector2 rayEnd = player->raysEndCoords.at(i);
        float distance = sqrt(pow(rayEnd.x - player->x, 2) + pow(rayEnd.y - player->y, 2));

        // Wysokoœæ œciany
        float wallHeight = screenHeight * wallHeightScale / distance;

        // Tekstura œciany
        Rectangle sourceRec = { 0, 0, texture.width, texture.height };
        Rectangle destRec = { static_cast<float>(i * screenWidth / Player::numberOfRays), (screenHeight - wallHeight) / 2, screenWidth / Player::numberOfRays, wallHeight };
        Vector2 origin = { 0, 0 };

        // set min and max brithness
        float brightness = fmaxf(0.02, distance / brightnessScale);
              brightness = fminf(0.71, brightness);
        Color tint = ColorFromNormalized({ 255 - brightness, 255 - brightness, 255 - brightness, 1 });

        // Narysuj teksturê
        DrawTexturePro(texture, sourceRec, destRec, origin, 0, tint);
    }
}



void draw3DMap() {

    std::vector<float> wallHeight(Player::numberOfRays);
    for (int i = 0; i < Player::numberOfRays; i++) {
        //DrawRectangle(0, 0, i + screenWidth / mapWidth, wallHeight.at(i), PURPLE);
    }
}