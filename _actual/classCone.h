#ifndef CONE_H
#define CONE_H
#include "classObjectRevolution.h"

class _cone:public _objRev
{
    public:
      _cone(float height = 1, float radius = 0.5, int vCuts = 1, int hCuts = 1, int rCuts = 3);
};
#endif
