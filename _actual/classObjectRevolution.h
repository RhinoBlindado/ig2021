#ifndef OBJREV_H
#define OBJREV_H
#include "object3d.h"

#define PI 3.14159265


class _objRev:public _object3D
{
    public:
        _objRev(){};
        void rotation(int rCuts);
        void genTriangles(int rCuts, bool topCap, bool bottomCap, vector<_vertex3f> caps);
};

#endif // OBJREV_H
