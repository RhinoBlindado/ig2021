#ifndef OBJREV_H
#define OBJREV_H

#include "object3d.h"
#include <cmath>

#define PI 3.14159265

/**
 * [P2]
 * @brief The Object Revoltuion virtual class
 * @details Virtual class made in order to originally reuse code for the
 *          Cone, Cylinder, Sphere and Profile PLY classes.
 */
class _objRev:public _object3D
{
    public:
        _objRev(){};
        void rotation(int rCuts);
        void genTriangles(int rCuts, bool topCap, bool bottomCap, vector<_vertex3f> caps);
};

#endif // OBJREV_H
