#include <raylib.h>

void drawMap(int, int);

const int screenWidth = 800;
const int screenHeight = 800;
const int tileSize = 48;
const int mapWidth = 9;
const int mapHeight = 7;
const char map[] =
"#########"
"#.......#"
"#..##..##"
"#.......#"
"#....####"
"#.......#"
"#########";

int main() {
    InitWindow(screenWidth, screenHeight, "Raylib map");

    int playerX     = tileSize;
    int playerY     = tileSize;
    int playerSpeed = 4;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && map[(playerY / tileSize) * mapWidth + (playerX / tileSize) + 1] == '.' && map[((playerY + tileSize - 1) / tileSize) * mapWidth + (playerX / tileSize) + 1] == '.') {
            playerX += playerSpeed;
        }
        if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && map[(playerY / tileSize) * mapWidth + ((playerX - 1) / tileSize)] == '.' && map[((playerY + tileSize - 1) / tileSize) * mapWidth + ((playerX - 1) / tileSize)] == '.') {
            playerX -= playerSpeed;
        }
        if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && map[(playerY / tileSize) * mapWidth + (playerX / tileSize) + mapWidth] == '.' && map[(playerY / tileSize) * mapWidth + ((playerX + tileSize - 1) / tileSize) + mapWidth] == '.') {
            playerY += playerSpeed;
        }
        if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && map[((playerY - 1) / tileSize) * mapWidth + (playerX / tileSize)] == '.' && map[((playerY - 1) / tileSize) * mapWidth + ((playerX + tileSize - 1)/ tileSize)] == '.') {
            playerY -= playerSpeed;
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw map
        drawMap(playerX, playerY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void drawMap(int playerX, int playerY) {
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
    DrawRectangle(playerX, playerY, tileSize, tileSize, BLUE);
}