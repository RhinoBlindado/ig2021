#ifndef TELESCOPE_H
#define TELESCOPE_H

#include "object3d.h"

class _telescope:public _object3D
{
    public:
    _telescope(){};
    void draw(int style = 1);
};

#endif // TELESCOPE_H
