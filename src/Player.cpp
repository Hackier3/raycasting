#include "Player.h"
#include "Map.h"
#include "Defines.h"

Player::Player(const char* texturePath) :   texture(LoadTexture(texturePath)), 
                                            speed(0.35), 
                                            rotationAngle(0),
                                            raysEndCoords(numberOfRays),
                                            raysForBlock(numberOfRays, 1), 
                                            rayDestributtionDestiny(numberOfRays / 88)
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
    const float multiplier = 0.55;
    raysForBlock.assign(numberOfRays ,1);

    for (int i = 0; i < numberOfRays; i++)
    {
        float dx = sin((rotationAngle + i / rayDestributtionDestiny - numberOfRays / (2 * rayDestributtionDestiny) - 1) * PI / 180.0);
        float dy = cos((rotationAngle + i / rayDestributtionDestiny - numberOfRays / (2 * rayDestributtionDestiny) - 1) * PI / 180.0) * (-1);

        lineNewPositionX.at(i) += dx * multiplier;
        lineNewPositionY.at(i) += dy * multiplier;

        while (true)
        {                                    //  REASON WHY WALLS CORNERS HAVE STARNGE TEXTURES
            lineNewPositionX.at(i) += dx * multiplier;
            lineNewPositionY.at(i) += dy * multiplier;

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
    float moveX = dx * speed;
    float moveY = dy * speed;
    checkCollision();

    if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))) {
        rotationAngle += 1.5;
        if (rotationAngle > 360)
        {
            rotationAngle = (int)rotationAngle % 360;
        }
    }
    if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))) {
        rotationAngle -= 1.5;
        if (rotationAngle < 0)
        {
            rotationAngle = 360 + rotationAngle;
        }
    }
    if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)))
    {                                       // UP LEFT
        if (Player::isULEdge && Player::isUREdge && Player::isDLEdge)
        {
            if (rotationAngle <= 90)
            {
                x += moveX;
            }
            else if (rotationAngle <= 270 && rotationAngle >= 180)
            {
                y += moveY;
            }
            else if (rotationAngle >= 90 && rotationAngle <= 180)
            { 
                x += moveX;
                y += moveY;
            }
        }                                   // UP RIGHT
        else if (Player::isUREdge && Player::isULEdge && Player::isDREdge)
        {
            if (rotationAngle >= 270)
            {
                x += moveX;
            }
            else if (rotationAngle <= 180 && rotationAngle >= 90)
            {
                y += moveX;
            }
            else if (rotationAngle >= 180 && rotationAngle <= 270)
            {
                x += moveX;
                y += moveY;
            }
        }                                   // DOWN LEFT
        else if (Player::isDLEdge && Player::isDREdge && Player::isULEdge)
        {
            if (rotationAngle >= 90 && rotationAngle <= 180)
            {
                x += moveX;
            }
            else if (rotationAngle >= 270)
            {
                y += moveY;
            }
            else if (rotationAngle <= 90)
            {
                x += moveX;
                y += moveY;
            }
        }                                   // DOWN RIGHT
        else if (Player::isDREdge && Player::isDLEdge && Player::isUREdge)
        {
            if (rotationAngle >= 180 && rotationAngle <= 270)
            {
                x += moveX;
            }
            else if (rotationAngle <= 90)
            {
                y += moveY;
            }
            else if (rotationAngle >= 270)
            {
                x += moveX;
                y += moveY;
            }
        }                                       // LEFT
        else if((Player::isDLEdge && Player::isULEdge) && rotationAngle < 360 && rotationAngle > 180)
        { 
            y += moveY;
        }                                       // RIGHT
        else if ((Player::isDREdge && Player::isUREdge) && rotationAngle > 0 && rotationAngle < 180)
        {
            y += moveY;
        }                                       // UP
        else if ((Player::isULEdge && Player::isUREdge) && (rotationAngle < 90 || rotationAngle > 270))
        {
            x += moveX;
        }                                       // DOWN
        else if ((Player::isDLEdge && Player::isDREdge) && rotationAngle > 90 && rotationAngle < 270)
        {
            x += moveX;
        }                                  // RIGHT UP EDGE
        else if (Player::isDLEdge)
        {
            if (((int)y + texture.height / 2) % tileSize == 0)
            {
                x += moveX;
                if (rotationAngle < 90 || rotationAngle > 270)
                {
                    y += moveY;
                }
            }
            else 
            {
                y += moveY;
                if (rotationAngle < 180)
                {
                    x += moveX;
                }
            }
        }                                   // UP LEFT EDGE
        else if (Player::isULEdge)
        {
            if (((int)x - texture.width / 2) % tileSize == (tileSize - 1))
            {
                y += moveY;
                if (rotationAngle < 180)
                {
                    x += moveX;
                }
            }
            else
            {
                x += moveX;
                if (rotationAngle > 90 && rotationAngle < 270)
                {
                    y += moveY;
                }
            }
        }
        else if (Player::isUREdge)
        {
            if (((int)y - texture.height / 2) % tileSize == (tileSize - 1))
            {
                x += moveX;
                if (rotationAngle > 90 && rotationAngle < 270)
                {
                    y += moveY;
                }
            }
            else
            {
                y += moveY;
                if (rotationAngle > 180)
                {
                    x += moveX;
                }
            }
        }
        else if (Player::isDREdge)
        {
            if (((int)x + texture.width/ 2) % tileSize == 0)
            {
                y += moveY;
                if (rotationAngle > 180)
                {
                    x += moveX;
                }
            }
            else
            {
                x += moveX;
                if (rotationAngle < 90 || rotationAngle > 270)
                {
                    y += moveY;
                }
            }
        }
        else
        {
            x += moveX;
            y += moveY;
        }
    }
//    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
//    {

//    }
}

void Player::checkCollision()
{
    isULEdge = false;
    isUREdge = false;
    isDLEdge = false;
    isDREdge = false;

    if (map[(int)((y - texture.height / 2) / tileSize) * mapWidth + (int)((x - texture.width / 2) / tileSize)] != '.')
    {
        isULEdge = true;
    }
    if (map[(int)((y - texture.height / 2) / tileSize) * mapWidth + (int)((x + texture.width / 2) / tileSize)] != '.')
    {
        isUREdge = true;
    }
    if (map[(int)((y + texture.height / 2) / tileSize) * mapWidth + (int)((x - texture.width / 2) / tileSize)] != '.')
    {
        isDLEdge = true;
    }
    if (map[(int)((y + texture.height / 2) / tileSize) * mapWidth + (int)((x + texture.width / 2) / tileSize)] != '.')
    {
        isDREdge = true;
    }
}