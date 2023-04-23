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

void Player::calculateRaysCoords() 
{
    float distanceToVertical;  // LEFT and UP is negative
    float distanceToHorizontal;// LEFT and UP is negative

    float lineX;
    float lineY;

    float rayEndHorDis;
    float rayEndVerDis;

    float dx = sin(rotationAngle * PI / 180.0);
    float dy = -cos(rotationAngle * PI / 180.0);

    if (rotationAngle <= 180)
        distanceToVertical = tileSize - fmod(x - 0.3, tileSize);
    else
        distanceToVertical = -fmod(x + 0.3, tileSize);

    if (rotationAngle <= 90 || rotationAngle >= 270)
        distanceToHorizontal = -fmod(y + 0.3, tileSize);
    else
        distanceToHorizontal = tileSize - fmod(y - 0.3, tileSize);

    if (dy / distanceToHorizontal >= dx / distanceToVertical)
    { 
        rayEndHorDis = -tan(rotationAngle * PI / 180) * (distanceToHorizontal);
        lineX = x + rayEndHorDis;
        lineY = y + distanceToHorizontal;
    }
    else
    {
        rayEndVerDis = -distanceToVertical / tan(rotationAngle * PI / 180);
        lineX = x + distanceToVertical;
        lineY = y + rayEndVerDis;
    }

    while (true)
    { 
        if (map[(int)((lineY) / tileSize) * mapWidth + (int)((lineX) / tileSize)] != '.')
            break;

        if ((int)lineY % tileSize == tileSize - 1)
            distanceToHorizontal -= tileSize;
        else if ((int)lineY % tileSize == 0)
            distanceToHorizontal += tileSize;

        if ((int)lineX % tileSize == tileSize - 1)
            distanceToVertical -= tileSize;
        else if ((int)lineX % tileSize == 0)
            distanceToVertical += tileSize;

        if (dy / distanceToHorizontal >= dx / distanceToVertical)
        {
            rayEndHorDis = -tan(rotationAngle * PI / 180) * (distanceToHorizontal);
            lineX = x + rayEndHorDis;
            lineY = y + distanceToHorizontal;
        }
        else
        {
            rayEndVerDis = -distanceToVertical / tan(rotationAngle * PI / 180);
            lineX = x + distanceToVertical;
            lineY = y + rayEndVerDis;
        }
    }

    DrawLine(x, y, lineX, lineY, DARKBLUE);
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