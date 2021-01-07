#ifndef CYLINDERTEX_H
#define CYLINDERTEX_H
#include "classObjectRevolution.h"

/**
 * [P4]
 * @brief The Textured Cylinder class
 */
class _cylinderTex:public _objRev
{
    public:
      _cylinderTex(){};
      void initialize(float height = 1, float radius = 0.5, int hCuts = 1, int vCuts = 1, int rCuts = 3);
      void rotation(int rCuts);
      void genTriangles(int rCuts);
      void mapTexture(int rCuts, int hCuts, int vCuts);
};
#endif

