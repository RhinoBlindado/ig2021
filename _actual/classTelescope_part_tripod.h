#ifndef TELE_TRIPOD_H
#define TELE_TRIPOD_H

#include "object3d.h"
#include "cube.h"
#include "classTelescope_part_mount.h"

class _teleMount;

class _teleTripod: public _object3D
{
    private:
        _cube feet;
        _teleMount __mount;

    public:
        _teleTripod(){};
        void draw(int style, float alpha, float beta, float gamma);
};
#endif // TELE_TRIPOD_H

