#include "Player.h"
#include "Map.h"
#include "Defines.h"

Player::Player(const char* texturePath) :   texture(LoadTexture(texturePath)), 
                                            speed(1.5), 
                                            rotationAngle(0),
                                            raysEndCoords(numberOfRays)
{
    x = tileSize + texture.width;
    y = tileSize + texture.height;
}

void Player::drawPlayer() {

    Rectangle arg2 = { 0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height) };
    Rectangle arg3 = { x, y, static_cast<float>(texture.width), static_cast<float>(texture.height) };

    DrawTexturePro(texture, arg2, arg3, ORIGIN, rotationAngle, WHITE);
}

void Player::calculateRaysCoords() {

    std::vector<float> lineNewPositionX(numberOfRays, x);
    std::vector<float> lineNewPositionY(numberOfRays, y);

    for (float i = 0; i < numberOfRays; i++)
    {
        float dx = sin((rotationAngle + i / rayDestributtionDestiny - numberOfRays / (2 * rayDestributtionDestiny) - 1) * PI / 180.0);
        float dy = cos((rotationAngle + i / rayDestributtionDestiny - numberOfRays / (2 * rayDestributtionDestiny) - 1) * PI / 180.0) * (-1);

        lineNewPositionX.at(i) += dx * speed;
        lineNewPositionY.at(i) += dy * speed;

        while ((int)lineNewPositionX.at(i) % tileSize != 0 || (int)lineNewPositionY.at(i) % tileSize != 0)
        {
            lineNewPositionX.at(i) += dx;
            lineNewPositionY.at(i) += dy;

            if (map[(int)lineNewPositionX.at(i) / tileSize + (int)(lineNewPositionY.at(i) / tileSize) * mapWidth] != '.')
            {
                break;
            }
        }

        raysEndCoords.at(i) = { lineNewPositionX.at(i), lineNewPositionY.at(i) };
    }
}

void Player::drawVisionRays() {

    for (int i = 0; i < numberOfRays; i++) {
        DrawLine(x, y, raysEndCoords.at(i).x, raysEndCoords.at(i).y, DARKBLUE);
    }
}

void Player::movement()
{
    float dx = sin(rotationAngle * PI / 180.0);
    float dy = cos(rotationAngle * PI / 180.0) * (-1);

    if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))) {
        rotationAngle += 1.5;
    }
    if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))) {
        rotationAngle -= 1.5;
    }
    if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)))
    {
        x += dx * speed;
        y += dy * speed;
    }
    if (IsKeyDown(KEY_DOWN))
    {
        x -= dx * speed;
        y -= dy * speed;
    }
}