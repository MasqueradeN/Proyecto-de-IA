#include "Agente.h"
#include <math.h>

#define M_PI 3.1415f
#define ACCEL 2

void Agente::Initialize(const int w, const int h)
{
    mTexture = LoadTexture("resources/ye.png");

    float frameWidth = mTexture.width;
    float frameHeight = mTexture.height;

    sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };

    origin = { (float)frameWidth, (float)frameHeight };
    direction = { 0.0f, 1.0f };
    realPos = { w / 2.f, h / 2.f };
    rotation = 0.f;
}

void Agente::Update(float dtime)
{
    //if (IsKeyDown(KEY_RIGHT))
    //{
    //    rotation += 1.0f;
    //    direction = { -sinf(DEG2RAD * rotation), cosf(DEG2RAD * rotation) };
    //}
    //if (IsKeyDown(KEY_LEFT))
    //{
    //    rotation -= 1.0f;
    //    direction = { -sinf(DEG2RAD * rotation), cosf(DEG2RAD * rotation) };
    //}
    /*if (!collision)
    {*/
    //if (IsKeyDown(KEY_UP)) realPos = { realPos.x + (-2 * direction.x), realPos.y + (-2 * direction.y) };
    //if (IsKeyDown(KEY_DOWN)) realPos = { realPos.x + (2 * direction.x), realPos.y + (2 * direction.y) };
    //}
    //if (IsKeyReleased(KEY_UP) || IsKeyReleased(KEY_DOWN)) speed = 0;
    if (moveToTarget)
    {
        accTime += dtime;
        float S = (ACCEL / 2) * (dtime * dtime);
        realPos = { movePos.x + (_steering.linear.x * S), movePos.y + (_steering.linear.y * S) };
        float dx = mTarget.x - realPos.x;
        float dy = mTarget.y - realPos.y;

        mDistance = sqrtf((dx * dx) + (dy * dy));

        if (mDistance/*abs(realPos.x - mTarget.x)*/ < 0.1f)
        {
            moveToTarget = false;
            accTime = 0.f;
        }
    }

}

void Agente::Draw()
{
    float frameWidth = mTexture.width;
    float frameHeight = mTexture.height;
    destRec = { realPos.x, realPos.y, frameWidth * 2.0f, frameHeight * 2.0f };

    DrawTexturePro(mTexture, sourceRec, destRec, origin, rotation, WHITE);
}

void Agente::End()
{
    UnloadTexture(mTexture);
}

void Agente::setTargetMove(Vector2 target)
{
    mTarget = target;
    float dx = target.x - realPos.x;
    float dy = target.y - realPos.y;

    mDistance = sqrtf((dx * dx) + (dy * dy));

    moveToTarget = true;
    // s = k/2 * (t^2)
    _steering.linear = { dx / mDistance , dy / mDistance };
    movePos = realPos;
}
