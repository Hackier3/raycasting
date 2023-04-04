#define PI 3.14159
#define ORIGIN { (float)playerTexture.width / 2, (float)playerTexture.height / 2 }
#define NUMBER_OF_RAYS 539
#define RAY_DESTRIBUTION_DESTINY 10

#include <raylib.h>
#include <math.h>
#include <stdlib.h>
#include <vector>

void drawMap();
void drawVisionRays(float, float, float);
void drawPlayer(float, float, Texture2D);

const int screenWidth = 800;
const int screenHeight = 800;
const int tileSize = 75;
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

    Texture2D playerTexture = LoadTexture("images/circle.png");
    float playerX = tileSize + playerTexture.width;
    float playerY = tileSize + playerTexture.height;
    float playerSpeed = 1.5;
    
    SetTargetFPS(60);

    while (!WindowShouldClose()) 
    {
        float dx(99);
        float dy(99);

        dx = sin(playerRotationAngle * PI / 180.0);
        dy = cos(playerRotationAngle * PI / 180.0) * (-1);

        float newPlayerX = playerX + dx * playerSpeed;
        float newPlayerY = playerY + dy * playerSpeed;

        if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))) {
            playerRotationAngle += 1.5;
        }
        if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))) {
            playerRotationAngle -= 1.5;
        }
        if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)))
        {
            playerX = newPlayerX;
            playerY = newPlayerY;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw map
        drawMap();
        drawPlayer(playerX, playerY, playerTexture);
        drawVisionRays(playerX, playerY, playerSpeed);

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

void drawVisionRays(float playerX, float playerY, float playerSpeed) {

    float lineNewPositionX;
    float lineNewPositionY;

    for(float i = 0; i < NUMBER_OF_RAYS; i++)
    { 
        lineNewPositionX = playerX;
        lineNewPositionY = playerY;

        float dx = sin((playerRotationAngle + i / RAY_DESTRIBUTION_DESTINY - NUMBER_OF_RAYS / (2 * RAY_DESTRIBUTION_DESTINY) - 1) * PI / 180.0);
        float dy = cos((playerRotationAngle + i / RAY_DESTRIBUTION_DESTINY - NUMBER_OF_RAYS / (2 * RAY_DESTRIBUTION_DESTINY) - 1) * PI / 180.0) * (-1);

        lineNewPositionX = playerX + dx * playerSpeed;
        lineNewPositionY = playerY + dy * playerSpeed;

        while ((int)lineNewPositionX % tileSize != 0 || (int)lineNewPositionY % tileSize != 0)
        {
            lineNewPositionX += dx;
            lineNewPositionY += dy;

            if (map[(int)lineNewPositionX / tileSize + (int)(lineNewPositionY / tileSize) * mapWidth] != '.')
            {
                break;
            }
            else
            {
                lineNewPositionX += dx;
                lineNewPositionY += dy;
            }
        }

        DrawLine(playerX, playerY, lineNewPositionX, lineNewPositionY, DARKBLUE);
    }
}

void drawPlayer(float playerX, float playerY, Texture2D playerTexture) {

    Rectangle arg2 = { 0, 0, playerTexture.width, playerTexture.height };
    Rectangle arg3 = { playerX, playerY, playerTexture.width, playerTexture.height };

    DrawTexturePro(playerTexture, arg2, arg3, ORIGIN, playerRotationAngle, WHITE);
}