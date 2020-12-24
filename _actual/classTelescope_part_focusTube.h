#ifndef TELE_FOCUSTUBE_H
#define TELE_FOCUSTUBE_H

#include "object3d.h"
#include "classCylinder.h"
#include "classTelescope_part_lens.h"

class _teleFocusTube: public _object3D
{
   private:
        _teleLens lens;
        _cylinder  focusTube;

        float gamma;

   public:
        _teleFocusTube(){this->focusTube.initialize(1,0.5,12,2,10,false,false); gamma = 0;};
        void draw(int style);
        void setGamma(float nGamma);
};

#endif // TELE_FOCUSTUBE_H
