#ifndef TELE_TUBE_H
#define TELE_TUBE_H

#include "object3d.h"
#include <classTelescope_part_focusTube.h>
#include <classTelescope_part_eyepiece.h>


/**
 * [P3]
 * @brief Main tube of the telescope. Connects the focusing tube and the eyepiece.
 */
class _teleTube: public _object3D
{
    private:
        _teleFocusTube focusTube;
        _teleEyePiece eyePiece;
        _cylinder tube;

        float alpha;
        float beta;

    public:
        _teleTube();
        void draw(int style);
        void setLighting(int style);
        void setAlpha(float nAlpha);
        void setBeta(float nBeta);
        void setGamma(float nGamma);
        void setMaterial();
};

#endif // TELE_TUBE_H

