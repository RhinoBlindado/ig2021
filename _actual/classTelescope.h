#ifndef TELESCOPE_H
#define TELESCOPE_H

#include "object3d.h"

class _telescope:public _object3D
{
    public:
    _telescope(){};
    void draw(int style = 1, float alpha = 0, float beta = 0, float gamma = 0);
};

#endif // TELESCOPE_H
