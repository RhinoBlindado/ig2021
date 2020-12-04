#ifndef CONE_H
#define CONE_H
#include "classObjectRevolution.h"

class _cone:public _objRev
{
    public:
      _cone(){};
      void initialize(float height = 1, float radius = 0.5, int vCuts = 20, int hCuts = 10, int rCuts = 30);

};
#endif
