#include "../raylib/raylib.h"
#include "../entorno/Grid.h"
#include "../agente/Agente.h"
#include "../entorno/EntornoMgr.h"
//#include <cmath>

enum class turn //enum para saber que turno es actualmente
{
	NONE,
	AGENT,
	ENEMY
};

int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 800;

	InitWindow(screenWidth, screenHeight, "raylib [textures] example - texture loading and drawing");

	Grid::Initialize(screenWidth, screenHeight);

	//iniciar agente y bordes
	Agente ahemte;
	EntornoMgr entomgr;
	float accTime = 0.f;
	turn pstate = turn::NONE;
	ahemte.Initialize(screenWidth, screenHeight);
	entomgr.Initialize(screenWidth, screenHeight);
	entomgr.AddBorder();
	VectorInt2 mpos = entomgr.AddEscena01();
	ahemte.SetPosition(mpos.x, mpos.y);

	ahemte.SetTarget(80, 40); //a donde irá el agente
	
	while (!WindowShouldClose()) 
	{
		float elapsedTime = GetFrameTime();

		// Update
		ahemte.Update(elapsedTime);
		accTime += elapsedTime;

		//Maquina de estados es un switch case

		switch (pstate)
		{
		case turn::NONE:
			pstate = turn::AGENT;
			accTime = 0.f;
			break;
		case turn::AGENT:
			ahemte.Update(elapsedTime);
			if (accTime > 1.0f)
			{
				pstate = turn::ENEMY;
				accTime = 0.f;
			}
			break;
		case turn::ENEMY:
			//enemigo.Update(elapsedTime);   supongo que aqui irá nuestra parte después de completar al enemigo
			if (accTime > 1.0f)
			{
				pstate = turn::AGENT;
				accTime = 0.f;
			}
			break;
		default:
			break;
		}

		// Draw		
		BeginDrawing();
		
		ClearBackground(RAYWHITE);

		for (size_t gap = 0; gap < 800; gap+=10) {
			DrawLine(gap, 0, gap, 800, LIGHTGRAY);
			DrawLine(0, gap, 800, gap, LIGHTGRAY);
		}

		entomgr.Render();
		ahemte.Render();
		
		EndDrawing();
		
	}
	ahemte.End();
	entomgr.End();
	CloseWindow();          
	
	return 0;
}