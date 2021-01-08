#ifndef TELE_FOCUSTUBE_H
#define TELE_FOCUSTUBE_H

#include "object3d.h"
#include "classCylinder.h"
#include "classTelescope_part_lens.h"

/**
 * [P3]
 * @brief The focusing tube of the Telescope.
 */
class _teleFocusTube: public _object3D
{
   private:
        _teleLens lens;
        _cylinder focusTube;

        float gamma;

   public:
        _teleFocusTube();
        void draw(int style);
        void setGamma(float nGamma);
        void setLighting(int type);
        void setMaterial();
};

#endif // TELE_FOCUSTUBE_H
