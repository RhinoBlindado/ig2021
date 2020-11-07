#ifndef TELESCOPE_H
#define TELESCOPE_H

#include "object3d.h"

class _telescope:public _object3D
{
    public:
    _telescope(){};
    void draw_fill();
};

#endif // TELESCOPE_H
