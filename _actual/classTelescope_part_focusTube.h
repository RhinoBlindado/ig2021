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

   public:
        _teleFocusTube(){this->focusTube.initialize(1,0.5,12,2,10,false,false);};
        void draw(int style, float gamma);
};

#endif // TELE_FOCUSTUBE_H
