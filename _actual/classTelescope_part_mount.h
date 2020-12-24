#ifndef TELE_MOUNT_H
#define TELE_MOUNT_H

#include "object3d.h"
#include "classCone.h"
#include <classTelescope_part_tube.h>

class _teleMount: public _object3D
{
    private:
        _teleTube __tube;
        _cone mount1;
        _cylinder mount2;

        float alpha;

    public:
        _teleMount();
        void draw(int style);
        void setAlpha(float nAlpha);
};

#endif // TELE_MOUNT_H

