#include "Player.h"
#include "Main.cpp"

// implementation of constructor
Player::Player(const char* texturePath)
{
    Texture2D playerTexture = LoadTexture(texturePath);
    x = tileSize + playerTexture.width;
    y = tileSize + playerTexture.height;
}

void Player::drawPlayer() {

    Rectangle arg2 = { 0, 0, playerTexture.width, playerTexture.height };
    Rectangle arg3 = { x, y, playerTexture.width, playerTexture.height };

    DrawTexturePro(playerTexture, arg2, arg3, ORIGIN, playerRotationAngle, WHITE);
}