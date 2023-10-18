#pragma once
#include "../raylib/raylib.h"
#include "Grid.h"
#include "Barrera.h"
#include <vector>

class EntornoMgr
{
public:
	EntornoMgr();

	void Initialize(int scW, int scH);
	void Update();
	void Render();
	void End();

	void AddBorder();
	VectorInt2 AddEscena01();

private:
	int maxW, maxH;
	bool hasBorder;

	std::vector<Barrera> mBarreras;
};

