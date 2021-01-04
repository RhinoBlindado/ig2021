#ifndef SPHERE_H
#define SPHERE_H
#include "classObjectRevolution.h"

/**
 * [P2]
 * @brief The Sphere Class
 */
class _sphere:public _objRev
{
    public:
      _sphere(){};
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

