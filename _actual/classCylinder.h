#ifndef CYLINDER_H
#define CYLINDER_H
#include "classObjectRevolution.h"

class _cylinder:public _objRev
{
    public:
      _cylinder(){};
      void initialize(float height = 1, float radius = 0.5, int hCuts = 20, int vCuts = 10, int rCuts = 30, bool bottom = true, bool top = true);
};
#endif

