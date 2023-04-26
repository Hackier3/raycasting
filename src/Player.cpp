#include "Player.h"
#include "Map.h"
#include "Defines.h"

Player::Player(const char* texturePath) : texture(LoadTexture(texturePath)),
                                                                            speed(0.35),
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

void Player::calculateRaysCoords()
{
    float distanceToVertical;  // LEFT and UP is negative
    float distanceToHorizontal;// LEFT and UP is negative

    float rayX;
    float rayY;

    float rayEndHorDis;
    float rayEndVerDis;

    for (int i = -numberOfRays/2; i < numberOfRays/2; i++)
    {
        float angleRotationAngle = fmod(rotationAngle + fieldOfViewAngle * float(i/(numberOfRays)), 360);
        float dx = sin(angleRotationAngle * PI / 180.0);
        float dy = -cos(angleRotationAngle * PI / 180.0);

        if (angleRotationAngle <= 180)
            distanceToVertical = tileSize - fmod(x - 0.3, tileSize);
        else
            distanceToVertical = -fmod(x + 0.3, tileSize);

        if (angleRotationAngle <= 90 || angleRotationAngle >= 270)
            distanceToHorizontal = -fmod(y + 0.3, tileSize);
        else
            distanceToHorizontal = tileSize - fmod(y - 0.3, tileSize);

        if (dy / distanceToHorizontal >= dx / distanceToVertical)
        {
            rayEndHorDis = -tan(angleRotationAngle * PI / 180) * (distanceToHorizontal);
            rayX = x + rayEndHorDis;
            rayY = y + distanceToHorizontal;
        }
        else
        {
            rayEndVerDis = -distanceToVertical / tan(angleRotationAngle * PI / 180);
            rayX = x + distanceToVertical;
            rayY = y + rayEndVerDis;
        }

        while (true)
        {
            if (map[(int)((rayY) / tileSize) * mapWidth + (int)((rayX) / tileSize)] != '.')
                break;

            if (((int)rayX % tileSize == 0 || (int)(rayX - 1) % tileSize == 0) && ((int)rayY % tileSize == 0 || (int)(rayY - 1) % tileSize == 0)) {

                int mapIndexX;
                int mapIndexY;

                if ((int)rayX % tileSize == 0)
                    mapIndexX = rayX - 1;
                else
                    mapIndexX = rayX + 1;

                if ((int)rayY % tileSize == 0)
                    mapIndexY = rayY - 1;
                else
                    mapIndexY = rayY + 1;

                if (map[(mapIndexY / tileSize) * mapWidth + (mapIndexX / tileSize)] != '.')
                    break;
            }

            if (((int)rayY % tileSize == tileSize - 1) && (angleRotationAngle >= 270 || angleRotationAngle <= 90))
                distanceToHorizontal -= tileSize;
            else if ((int)rayY % tileSize == 0 && angleRotationAngle >= 90 && angleRotationAngle <= 270)
                distanceToHorizontal += tileSize;

            if ((int)rayX % tileSize == tileSize - 1 && angleRotationAngle >= 180)
                distanceToVertical -= tileSize;
            else if ((int)rayX % tileSize == 0 && angleRotationAngle <= 180)
                distanceToVertical += tileSize;

            if (dy / distanceToHorizontal >= dx / distanceToVertical)
            {
                rayEndHorDis = -tan(angleRotationAngle * PI / 180) * (distanceToHorizontal);
                rayX = x + rayEndHorDis;
                rayY = y + distanceToHorizontal;
            }
            else
            {
                rayEndVerDis = -distanceToVertical / tan(angleRotationAngle * PI / 180);
                rayX = x + distanceToVertical;
                rayY = y + rayEndVerDis;
            }
        }

        DrawLine(x, y, rayX, rayY, DARKBLUE);
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
        else if ((Player::isDLEdge && Player::isULEdge) && rotationAngle < 360 && rotationAngle > 180)
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
        }                                  // DOWN LEFT EDGE
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
        }                                   // UP RIGHT EDGE
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
        }                                   // DOWN RIGHT EDGE
        else if (Player::isDREdge)
        {
            if (((int)x + texture.width / 2) % tileSize == 0)
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
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
    {                                     // UP LEFT
        if (Player::isULEdge && Player::isUREdge && Player::isDLEdge)
        {
            if (rotationAngle >= 180 && rotationAngle <= 270)
            {
                x -= moveX;
            }
            else if (rotationAngle <= 90)
            {
                y -= moveY;
            }
            else if (rotationAngle >= 270)
            {
                x -= moveX;
                y -= moveY;
            }
        }                                   // UP RIGHT
        else if (Player::isUREdge && Player::isULEdge && Player::isDREdge)
        {
            if (rotationAngle >= 90 && rotationAngle <= 180)
            {
                x -= moveX;
            }
            else if (rotationAngle >= 270)
            {
                y -= moveX;
            }
            else if (rotationAngle <= 90)
            {
                x -= moveX;
                y -= moveY;
            }
        }                                   // DOWN LEFT
        else if (Player::isDLEdge && Player::isDREdge && Player::isULEdge)
        {
            if (rotationAngle >= 270)
            {
                x -= moveX;
            }
            else if (rotationAngle >= 90 && rotationAngle <= 180)
            {
                y -= moveY;
            }
            else if (rotationAngle >= 180 && rotationAngle <= 270)
            {
                x -= moveX;
                y -= moveY;
            }
        }                                   // DOWN RIGHT
        else if (Player::isDREdge && Player::isDLEdge && Player::isUREdge)
        {
            if (rotationAngle <= 90)
            {
                x -= moveX;
            }
            else if (rotationAngle >= 180 && rotationAngle <= 270)
            {
                y -= moveY;
            }
            else if (rotationAngle >= 90 && rotationAngle <= 180)
            {
                x -= moveX;
                y -= moveY;
            }
        }                                       // LEFT
        else if ((Player::isDLEdge && Player::isULEdge) && rotationAngle <= 180)
        {
            y -= moveY;
        }                                       // RIGHT
        else if ((Player::isDREdge && Player::isUREdge) && rotationAngle >= 180)
        {
            y -= moveY;
        }                                       // UP
        else if ((Player::isULEdge && Player::isUREdge) && rotationAngle >= 90 && rotationAngle <= 270)
        {
            x += moveX;
        }                                       // DOWN
        else if ((Player::isDLEdge && Player::isDREdge) && (rotationAngle <= 90 || rotationAngle >= 270))
        {
            x += moveX;
        }                                  // DOWN LEFT EDGE
        else if (Player::isDLEdge)
        {
            if (((int)y + texture.height / 2) % tileSize == 0)
            {
                x += moveX;
                if (rotationAngle >= 90 && rotationAngle <= 270)
                {
                    y += moveY;
                }
            }
            else
            {
                y -= moveY;
                if (rotationAngle >= 180)
                {
                    x -= moveX;
                }
            }
        }                                   // UP LEFT EDGE
        else if (Player::isULEdge)
        {
            if (((int)x - texture.width / 2) % tileSize == (tileSize - 1))
            {
                y -= moveY;
                if (rotationAngle >= 180)
                {
                    x -= moveX;
                }
            }
            else
            {
                x -= moveX;
                if (rotationAngle <= 90 || rotationAngle >= 270)
                {
                    y -= moveY;
                }
            }
        }                                   // UP RIGHT EDGE
        else if (Player::isUREdge)
        {
            if (((int)y - texture.height / 2) % tileSize == (tileSize - 1))
            {
                x -= moveX;
                if (rotationAngle <= 90 || rotationAngle >= 270)
                {
                    y -= moveY;
                }
            }
            else
            {
                y -= moveY;
                if (rotationAngle <= 180)
                {
                    x -= moveX;
                }
            }
        }                               // DOWN RIGHT EDGE
        else if (Player::isDREdge)
        {
            if (((int)x - texture.width / 2) % tileSize == 0)
            {
                y -= moveY;
                if (rotationAngle <= 180)
                {
                    x -= moveX;
                }
            }
            else
            {
                x -= moveX;
                if (rotationAngle >= 90 && rotationAngle <= 270)
                {
                    y -= moveY;
                }
            }
        }
        else
        {
            x -= moveX;
            y -= moveY;
        }
    }
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