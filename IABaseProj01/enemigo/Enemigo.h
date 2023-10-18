#pragma once
#include "../raylib/raylib.h"
#include "../entorno/Barrera.h"
#include "../entorno/Grid.h"
#include "../agente/Agente.h"
#include <vector>

struct Kinematic
{
	Vector2 position;
	Vector2 orientation;
	float rotation;
};

struct SteeringOutput
{
	VectorInt2 linear;
	float angular;
};

enum class sMoveResult
{
	NONE = 0,
	gook,
	arrived,
	stoped,
};

class Enemigo
{
private:

public:
	Enemigo();

	void Initialize(int scW, int scH);
	void Update(float deltaTime);
	void Render();
	void End();

	void SetTarget(int x, int y);
	void SetPosition(int x, int y);

	void SetBarriers(const std::vector<Barrera>& barreras);

	VectorInt2 GetAgentPosition();
	float GetAgentRotation();
};

