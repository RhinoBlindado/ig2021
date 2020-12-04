#ifndef TELE_LENS_H
#define TELE_LENS_H

#include "object3d.h"
#include "classSphere.h"

class _teleLens:public _object3D
{
    private:
        _sphere lens;

    public:
        _teleLens(){this->lens.initialize(0.5, 20, 20);};
        void draw(int style);
};
#endif // TELE_LENS_H
