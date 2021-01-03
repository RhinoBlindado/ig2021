#ifndef SPHERE_H
#define SPHERE_H
#include "classObjectRevolution.h"

class _sphere:public _objRev
{
    public:
      _sphere(){};
      void initialize(float radius = 0.5, int vCuts = 4, int rCuts = 4);

      // Overloaded functions
      void rotation(int rCuts);
      void genTriangles(int rCuts, bool bottomCap, bool topCap, vector<_vertex3f> caps);
      void calculateTrigNormals();
      void calculateVertNormals();

      void mapTexture(int rCuts);
};
#endif

