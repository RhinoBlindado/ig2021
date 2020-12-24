#ifndef TELE_TUBE_H
#define TELE_TUBE_H

#include "object3d.h"
#include <classTelescope_part_focusTube.h>
#include <classTelescope_part_eyepiece.h>

class _teleFocusTube;
class _teleEyePiece;

class _teleTube: public _object3D
{
    private:
        _teleFocusTube focusTube;
        _teleEyePiece eyePiece;
        _cylinder tube;

        float alpha;
        float beta;

    public:
        _teleTube(){this->tube.initialize(1,0.5,12,2,10); alpha = 0; beta = 0;};
        void draw(int style);
        void setAlpha(float nAlpha);
        void setBeta(float nBeta);
        void setGamma(float nGamma);
};

#endif // TELE_TUBE_H

