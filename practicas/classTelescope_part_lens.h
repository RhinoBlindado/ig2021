#ifndef TELE_LENS_H
#define TELE_LENS_H

#include "object3d.h"
#include "classSphere.h"

/**
 * [P3]
 * @brief The lens of the telescope.
 */
class _teleLens:public _object3D
{
    private:
        _sphere lens;

    public:
        _teleLens();
        void draw(int style);
        void setLighting(int type);
        void setMaterial();
};
#endif // TELE_LENS_H
