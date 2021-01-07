#ifndef SPHERETEX_H
#define SPHERETEX_H
#include "classObjectRevolution.h"

/**
 * [P4]
 * @brief The Textured Sphere Class
 */
class _sphereTex:public _objRev
{
    public:
      _sphereTex(){};
      void initialize(float radius = 0.5, int vCuts = 4, int rCuts = 4);

      // [P4] Overloaded functions
      // Originally, the Sphere used the _objRev versions but in order to map the textures, these have been redefined.
      void rotation(int rCuts);
      void genTriangles(int rCuts);

      // More efficiente way of calculating them based on being a Sphere.
      void calculateTrigNormals();
      void calculateVertNormals();
      void mapTexture(int rCuts);
};
#endif

