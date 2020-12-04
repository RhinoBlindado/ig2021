#ifndef TELE_EYEPIECE_H
#define TELE_EYEPIECE_H

#include "object3d.h"
#include "classCylinder.h"

class _teleEyePiece: public _object3D
{
    private:
        _cylinder eyePiece;

    public:
        _teleEyePiece(){this->eyePiece.initialize(1,0.5,12,2,10,true,true);};
        void draw(int style);
};
#endif // TELE_EYEPIECE_H
