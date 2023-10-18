#pragma once
#include "../raylib/raylib.h"
#include <vector>

struct VectorInt2 
{
	int x;
	int y;
};

enum class eObjType
{
	none = 0,
	barrier,
	enemy,
	energyorb
};

struct sCell 
{
	eObjType object;
};

class Grid
{
public:
	Grid() = default;

	static void Initialize(int scW, int scH);
	static sCell GetCell(int x, int y);
	static void SetCell(int x, int y, sCell value);
	
	static Vector2 GetRealCoords(int x, int y);
	static VectorInt2 GetGridCoords(Vector2 pos);
	static Vector2 GetSnapCoords(Vector2 pos);



private:

	static void boundCoords(int& x, int& y);
	static std::vector<std::vector<sCell>> mGrid;
	static int maxCol, maxRow;
};

