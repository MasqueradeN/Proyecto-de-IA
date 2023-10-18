#include "Enemigo.h"
#include "../raylib/raymath.h"
#include "../entorno/Grid.h"
#include "../agente/Agente.h"
#include <cmath>
#include <iostream>

VectorInt2 Enemigo::GetAgentPosition()
{
    return Agente::GetAgentPosition();
}
