#ifndef TELE_MOUNT_H
#define TELE_MOUNT_H

#include "object3d.h"
#include "classCone.h"
#include "classCube.h"
#include "classCylinder.h"

/**
 * [P3]
 * @brief The mount of the tube of the Telescope.
 */
class _teleMount: public _object3D
{
    private:
        _cone mount1;
        _cylinder mount2;

    public:
        _teleMount();
        void draw(int style);
        void setLighting(int type);
        void setMaterial();
};

#endif // TELE_MOUNT_H

