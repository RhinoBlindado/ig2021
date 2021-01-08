#ifndef TELE_EYEPIECE_H
#define TELE_EYEPIECE_H

#include "object3d.h"
#include "classCylinder.h"

/**
 * [P3]
 * @brief Eyepiece of the Telescope
 */
class _teleEyePiece: public _object3D
{
    private:
        _cylinder eyePiece;

    public:
        _teleEyePiece();
        void draw(int style);
        void setLighting(int type);
        void setMaterial();
};
#endif // TELE_EYEPIECE_H
