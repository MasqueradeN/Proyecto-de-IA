#pragma once
#include "raylib/raylib.h"

struct Kinematic
{
	Vector3 position;
	Vector2 velocity;
	float orientation;
	float rotations;
};

struct SteeringOutput
{
	Vector2 linear;
	float angular;
};

class Agente
{
public:
	void Initialize(const int w, const int h);
	void Update(float dtime);
	void Draw();
	void End();

	void setTargetMove(Vector2 target);

private:
	Texture2D mTexture;

	Rectangle sourceRec;
	Rectangle destRec;

	Vector2 origin;
	Vector2 direction;
	Vector2 realPos;
	Vector2 tergetPos;
	Vector2 mTarget;
	Vector2 movePos;

	Kinematic _kinematics;
	SteeringOutput _steering;

	float rotation;
	float mTargetDir;
	float mDistance;
	float accTime;
	
	bool  moveToTarget = false;
};