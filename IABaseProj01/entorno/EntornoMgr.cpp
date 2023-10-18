#include "EntornoMgr.h"
#include "../raylib/raymath.h"

#include <cmath>
#include <iostream>

const int stdBorde = 2;

EntornoMgr::EntornoMgr()
{
}

void EntornoMgr::Initialize(int scW, int scH)
{
	maxW = scW;
	maxH = scW;
}

void EntornoMgr::Update()
{
}

void EntornoMgr::Render()
{
	for (Barrera& barr : mBarreras) {
		barr.Render();
	}
}

void EntornoMgr::End()
{
}

void EntornoMgr::AddBorder()
{
	VectorInt2 dim = Grid::GetGridCoords({ (float)maxW, (float)maxH });
	Barrera top, right, left, bottom;
	top.Initialize(0, 0, dim.x, stdBorde);
	right.Initialize(dim.x - stdBorde, stdBorde, stdBorde, dim.y - 2 * stdBorde);
	left.Initialize(0, stdBorde, stdBorde, dim.y - 2 * stdBorde);
	bottom.Initialize(0, dim.y - stdBorde, dim.x, stdBorde);
	
	mBarreras.push_back(top);
	mBarreras.push_back(right);
	mBarreras.push_back(left);
	mBarreras.push_back(bottom);
}

VectorInt2 EntornoMgr::AddEscena01()
{
	VectorInt2 dim = Grid::GetGridCoords({ (float)maxW, (float)maxH });
	Barrera sceneb[4];
	sceneb[0].Initialize(dim.x / 2 - 3, dim.y / 5, 6, dim.y / 5);
	sceneb[1].Initialize(dim.x / 5, dim.y / 4, dim.y / 5, 6);
	sceneb[2].Initialize(3 * dim.x / 5, dim.y / 4, dim.y / 5, 6);
	sceneb[3].Initialize(dim.x / 2 - 3, 3 * dim.y / 5, dim.y / 5, 6);
	for (int i = 0; i < 4; i++)	{ mBarreras.push_back(sceneb[i]); }

	VectorInt2 vecRet = { 70, 4 * dim.y / 5 };
	return vecRet;
}
