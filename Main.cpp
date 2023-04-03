#define PI 3.14159
#define ORIGIN { (float)playerTexture.width / 2, (float)playerTexture.height / 2 }

#include <raylib.h>
#include <math.h>

void drawMap(int, int, Texture2D);

const int screenWidth = 800;
const int screenHeight = 800;
const int tileSize = 48;
const int mapWidth = 9;
const int mapHeight = 7;
double playerRotationAngle = 0;
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

    float playerX = tileSize;
    float playerY = tileSize;
    float playerSpeed = 1.5;
    Texture2D playerTexture = LoadTexture("images/circle.png");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))) {
            playerRotationAngle += 1.5;
        }
        if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))) {
            playerRotationAngle -= 1.5;
        }
        if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))) {
            float dx = cos(playerRotationAngle * PI / 180.0);
            float dy = sin(playerRotationAngle * PI / 180.0);

            float finalPlayerX = playerX + dx;
            float finalPlayerY = playerY + dy;
            
            playerX = playerX + (finalPlayerX - playerX) * playerSpeed;
            playerY = playerY + (finalPlayerY - playerY) * playerSpeed;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw map
        drawMap(playerX, playerY, playerTexture);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void drawMap(int playerX, int playerY, Texture2D playerTexture) {

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

    // Draw player
    Rectangle arg2 = { 0, 0, playerTexture.width, playerTexture.height };
    Rectangle arg3 = { playerX + tileSize / 2, playerY + tileSize / 2, playerTexture.width, playerTexture.height };

    DrawTexturePro(playerTexture, arg2, arg3, ORIGIN, playerRotationAngle, WHITE);
}