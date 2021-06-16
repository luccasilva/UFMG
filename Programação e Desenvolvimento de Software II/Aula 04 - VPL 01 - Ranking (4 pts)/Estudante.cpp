#include <iostream>
#include <iomanip>
#include "Estudante.hpp"

float Estudante::calcularRSG(){
    float rsg = 0;
    for (size_t i = 0; i < 5; i++)
    {
        rsg = rsg+notas[i];
    }
    return rsg/5.0;
}