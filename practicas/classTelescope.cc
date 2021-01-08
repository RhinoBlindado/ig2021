#include "classTelescope.h"

/**
 * @brief Redefinition of the draw method so that it can be used
 *        to move the subparts of the telescope.
 * @param style     Type of drawing style.
 */
void _telescope::draw(int style)
{
    __tripod.draw(style);
    __mount.draw(style);
    __tube.draw(style);
}

/**
 * @brief First degree of freedom.
 * @param nAlpha    Angle of the first degree.
 */
void _telescope::rotateFirstDegree(float nAlpha)
{
    __tube.setAlpha(nAlpha);
}

/**
 * @brief Second degree of freedom.
 * @param nBeta     Angle of the second degree.
 */
void _telescope::rotateSecondDegree(float nBeta)
{
    __tube.setBeta(nBeta);
}

/**
 * @brief Third degree of freedom.
 * @param nGamma    Angle of the third degree.
 */
void _telescope::rotateThirdDegree(float nGamma)
{
    __tube.setGamma(nGamma);
}

/**
 * @brief Redefinition of the lighting so that it can be passed to the hierarchy.
 * @param style     0 : No Lighting | 1 : Flat Lighting | 2 : Smooth/Goraund Lighting
 */
void _telescope::setLighting(int type)
{
    __tripod.setLighting(type);
    __mount.setLighting(type);
    __tube.setLighting(type);
}
