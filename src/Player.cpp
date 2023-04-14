#include "Player.h"
#include "Map.h"
#include "Defines.h"

Player::Player(const char* texturePath) :   texture(LoadTexture(texturePath)), 
                                            speed(0.35), 
                                            rotationAngle(0),
                                            raysEndCoords(numberOfRays),
                                            raysForBlock(numberOfRays, 1)
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
    int lastWallPos = (int)lineNewPositionX.at(1) / tileSize + (int)(lineNewPositionY.at(1) / tileSize) * mapWidth;
    int newWallPos = -1;
    raysForBlock.assign(numberOfRays ,1);

    for (int i = 0; i < numberOfRays; i++)
    {
        float dx = sin((rotationAngle + i / rayDestributtionDestiny - numberOfRays / (2 * rayDestributtionDestiny) - 1) * PI / 180.0);
        float dy = cos((rotationAngle + i / rayDestributtionDestiny - numberOfRays / (2 * rayDestributtionDestiny) - 1) * PI / 180.0) * (-1);

        lineNewPositionX.at(i) += dx * speed;
        lineNewPositionY.at(i) += dy * speed;

        while (true)
        {
            lineNewPositionX.at(i) += dx;
            lineNewPositionY.at(i) += dy;

            if (map[(int)lineNewPositionX.at(i) / tileSize + (int)(lineNewPositionY.at(i) / tileSize) * mapWidth] != '.')
            {
                newWallPos = (int)lineNewPositionX.at(i) / tileSize + (int)(lineNewPositionY.at(i) / tileSize) * mapWidth;
                break;
            }
        }

        if (lastWallPos == newWallPos && i != 0)
            raysForBlock.at(i) = raysForBlock.at(i - 1) + 1;
        lastWallPos = newWallPos;
    }

    int j = 1;
    for (int i = numberOfRays - 1; i >= 1; i--)
    {          
        if (raysForBlock.at(i - 1) + j == raysForBlock.at(i))
        {
            raysForBlock.at(i - 1) = raysForBlock.at(i);
            j++;
        }
        else
            j = 1;
        raysEndCoords.at(i) = { lineNewPositionX.at(i), lineNewPositionY.at(i) };
    }

    if (raysForBlock.at(0) + 1 == raysForBlock.at(1))
        raysForBlock.at(0) = raysForBlock.at(1);
    raysEndCoords.at(0) = { lineNewPositionX.at(1), lineNewPositionY.at(1) };
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