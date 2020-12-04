#ifndef SPHERE_H
#define SPHERE_H
#include "classObjectRevolution.h"

class _sphere:public _objRev
{
    public:
      _sphere(){};
      void initialize(float radius = 0.5, int vCuts = 20, int rCuts = 20);
};
#endif

