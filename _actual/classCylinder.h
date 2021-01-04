#ifndef CYLINDER_H
#define CYLINDER_H
#include "classObjectRevolution.h"

/**
 * [P2]
 * @brief The Cylinder class
 */
class _cylinder:public _objRev
{
    public:
      _cylinder(){};
      void initialize(float height = 1, float radius = 0.5, int hCuts = 1, int vCuts = 1, int rCuts = 3, bool bottom = true, bool top = true);
      void rotation(int rCuts);
      void genTriangles(int rCuts);
      void mapTexture(int rCuts, int hCuts, int vCuts);
};
#endif

