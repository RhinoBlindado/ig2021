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

    public:
        _teleTripod(){};
        void draw(int style);
};
#endif // TELE_TRIPOD_H

