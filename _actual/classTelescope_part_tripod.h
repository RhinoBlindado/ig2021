#ifndef TELE_TRIPOD_H
#define TELE_TRIPOD_H

#include "object3d.h"
#include "classCube.h"

/**
 * [P3]
 * @brief The tripod of the telescope.
 */
class _teleTripod: public _object3D
{
    private:
        _cube feet;

    public:
        _teleTripod(){};
        void draw(int style);
        void setLighting(int style);
        void setMaterial();
};
#endif // TELE_TRIPOD_H

