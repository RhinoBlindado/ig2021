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

    public:
        _teleTube(){this->tube.initialize(1,0.5,12,2,10);};
        void draw(int style, float beta, float gamma);
};

#endif // TELE_TUBE_H

