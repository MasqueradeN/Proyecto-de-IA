#include "Agente.h"
#include "../raylib/raymath.h"
#include "../entorno/Grid.h"
#include <cmath>
#include <iostream>

const float linearAcc = 0.01f; // per sec
const float angularAcc = 0.02f;

Agente::Agente()
	: mTime{ 0.f }
{
}

void Agente::Initialize(int scW, int scH)
{
	mTexture = LoadTexture("resources/hamtaro.png");

	int frameWidth = mTexture.width;
	int frameHeight = mTexture.height;

	mCineman.orientation = { 0, -1 };
	mCineman.position = { scW / 2.0f, scH / 2.0f };
	mCineman.rotation = 0.f;

	mManejo.linear = { 0, 0 };
	mManejo.angular = 0.f;

	deltaPos = { 0, 0 };
	deltaAng = 0.f;
}

void Agente::Update(float deltaTime)
{
	GoTo(deltaTime);
}

void Agente::Render()
{
	int frameWidth = mTexture.width;
	int frameHeight = mTexture.height;
	
	const Vector2 origin = { (float)frameWidth / 2.0f, (float)frameHeight / 2.0f };
	const Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };

	Vector2 rnrPos = Grid::GetSnapCoords(GetInternalPosition());
	const Rectangle destRec = {
	rnrPos.x, rnrPos.y, (float)frameWidth, (float)frameHeight };

	float rndRot = GetAgentRotation();
	DrawTexturePro(mTexture, sourceRec, destRec, origin, rndRot, WHITE);
}

void Agente::End()
{
	UnloadTexture(mTexture);
}

sMoveResult Agente::GoTo(float deltaTime)
{
	mTime += deltaTime;

	float epsilon = 10.f;
	Vector2 thrPos = GetInternalPosition();
	Vector2 rtarget = Grid::GetRealCoords(mTarget.x, mTarget.y);

	float cobaX = abs(thrPos.x - rtarget.x);
	float cobaY = abs(thrPos.y - rtarget.y);
	if (cobaX < epsilon && cobaY < epsilon) {
		// Set pos/orient to reset
		return sMoveResult::arrived;
	}

	if (checkForBarriers(thrPos)) {
		return sMoveResult::stoped;
	}

	float samt = linearAcc * mTime;
	Translate(samt);

	Vector2 vecGo = { rtarget.x - thrPos.x, rtarget.y - thrPos.y };
	Vector2 nnorm = Vector2Normalize(vecGo);
	Vector2 orient = { mCineman.orientation.x, mCineman.orientation.y };

	Vector3 angSide = Vector3CrossProduct({ orient.x, orient.y, 0 }, { nnorm.x, nnorm.y, 0 });

	float sign = angSide.z > 0 ? 1.f : -1.f;
	float angt = sign * angularAcc * mTime;

	Rotate(angt);

	return sMoveResult::gook;
}

void Agente::SetTarget(int x, int y)
{
	mTime = 0.f;
	mTarget = VectorInt2{ x,y };
	mCineman.position = GetInternalPosition();
	mCineman.rotation = GetAgentRotation();
	deltaPos = { 0,0 };
	deltaAng = 0.f;
}

void Agente::SetPosition(int x, int y)
{
	mCineman.position = Grid::GetRealCoords(x, y);
}

void Agente::SetBarriers(const std::vector<Barrera> &barreras)
{
	mBarriers = barreras;
}

Vector2 Agente::GetInternalPosition()
{
	return { mCineman.position.x + deltaPos.x, mCineman.position.y + deltaPos.y };
}

VectorInt2 Agente::GetAgentPosition()
{
	return Grid::GetGridCoords(GetInternalPosition());
}

float Agente::GetAgentRotation()
{
	return mCineman.rotation + deltaAng;
}

void Agente::Translate(float damount)
{
	deltaPos =
	{ deltaPos.x + (damount * mCineman.orientation.x),
		deltaPos.y + (damount * mCineman.orientation.y) };
}

void Agente::Rotate(float dangle)
{
	deltaAng += dangle;
	float totAng = GetAgentRotation();
	if (totAng > 360.f) { totAng -= 360.f; }
	float angtmp = (-90.f + totAng);
	mCineman.orientation = { cosf(DEG2RAD * angtmp), sinf(DEG2RAD * angtmp) };
}

bool Agente::checkForBarriers(const Vector2& realPos)
{
	const VectorInt2& gridp = Grid::GetGridCoords(realPos);
	sCell info[9] = {
		Grid::GetCell(gridp.x, gridp.y + 1),
		Grid::GetCell(gridp.x, gridp.y),
		Grid::GetCell(gridp.x, gridp.y - 1),
		Grid::GetCell(gridp.x - 1, gridp.y + 1),
		Grid::GetCell(gridp.x - 1, gridp.y),
		Grid::GetCell(gridp.x - 1, gridp.y - 1),
		Grid::GetCell(gridp.x + 1, gridp.y + 1),
		Grid::GetCell(gridp.x + 1, gridp.y),
		Grid::GetCell(gridp.x + 1, gridp.y - 1)
	};

	for (int cel = 0; cel < 9; cel++) {
		if (info[cel].object == eObjType::barrier) {
			return true;
		}
	}
	return false;
}
