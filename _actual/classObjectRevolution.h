#ifndef OBJREV_H
#define OBJREV_H
#include "object3d.h"


class _objRev:public _object3D
{
    public:
        _objRev(){};
        void rotation(int rCuts);
        void genTriangles(int rCuts, int caps, vector<_vertex3f> aux);
};

#endif // OBJREV_H
