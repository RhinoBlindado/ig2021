#ifndef SPHERE_H
#define SPHERE_H
#include "classObjectRevolution.h"

class _sphere:public _objRev
{
    public:
      _sphere(float radius = 0.5, int vCuts = 1, int rCuts = 3);
};
#endif

