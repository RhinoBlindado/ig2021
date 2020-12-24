/*  ESPAÑOL
    Titulo: Práctica 3
    Fecha: 07/11/2020
    Autor: Valentino Lugli
    Versión: 0.1
    Descripción: Realización de un modelo jerárquico de 5 niveles.
    Uso: Generar un telescopio hecho de formas básicas.

    ENGLISH
    Title: Practice 3
    Date: 07/11/2020
    Author: Valentino Lugli
    Version: 0.1
    Description: Making a hierarchical model with 5 levels.
    Usage: Making a telescope made out of basic shapes.
*/

//  Libraries
#include "classTelescope.h"

_telescope::_telescope(){}

void _telescope::draw(int style)
{
    __tripod.draw(style);
    __mount.draw(style);
    __tube.draw(style);
}

void _telescope::rotateFirstDegree(float nAlpha)
{
    __tube.setAlpha(nAlpha);
}

void _telescope::rotateSecondDegree(float nBeta)
{
    __tube.setBeta(nBeta);
}

void _telescope::rotateThirdDegree(float nGamma)
{
    __tube.setGamma(nGamma);
}
