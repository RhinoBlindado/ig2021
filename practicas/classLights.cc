#include "classLights.h"

using namespace _colors_ne;

/**
 * [Practice 4]
 * @brief Initializing the Lights
 */
void _lights::initialize()
{
    //      Setting up the color.
    //_vertex3f color = _vertex3f(1,1,1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, (GLfloat *) &MAGENTA);
    glLightfv(GL_LIGHT1, GL_SPECULAR, (GLfloat *) &MAGENTA);
}

/**
 * @brief Toggle the 1st light.
 * @param toggle    Boolean, switch ON or OFF the 1st light.
 */
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

/**
 * @brief Toggle ON/OFF the 2nd light.
 * @param toggle    Boolean, switch On/OFF the 2nd light.
 */
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

/**
 * @brief Rotate the 2nd light around the X axis.
 * @param nDelta    Angle of rotation of the light in Degrees.
 */
void _lights::rotateSecondLight(float nDelta)
{
    this->actPos2.y = lightPos2.y * cos((nDelta * PI) / 180) - lightPos2.z * sin((nDelta * PI) / 180);
    this->actPos2.z = lightPos2.y * sin((nDelta * PI) / 180) + lightPos2.z * cos((nDelta * PI) / 180);
}
