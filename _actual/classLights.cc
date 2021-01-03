#include "classLights.h"
#include <qwidget.h>

using namespace _colors_ne;


void _lights::initialize()
{
    //      Setting up the color.
    glLightfv(GL_LIGHT1, GL_DIFFUSE, (GLfloat *) &MAGENTA);
}

void _lights::toggleFirstLight(bool toggle)
{
    if(toggle)
    {
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, (GLfloat *) &lightPos);
    }
    else
        glDisable(GL_LIGHT0);

}

void _lights::toggleSecondLight(bool toggle)
{
    if(toggle)
    {
        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_POSITION, (GLfloat *) &actPos2);
    }
    else
        glDisable(GL_LIGHT1);

}

void _lights::rotateSecondLight(float nDelta)
{
    this->actPos2.y = lightPos2.y * cos((nDelta * PI) / 180) - lightPos2.z * sin((nDelta * PI) / 180);
    this->actPos2.z = lightPos2.y * sin((nDelta * PI) / 180) + lightPos2.z * cos((nDelta * PI) / 180);
}
