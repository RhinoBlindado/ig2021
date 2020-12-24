#ifndef CYLINDER_H
#define CYLINDER_H
#include "classObjectRevolution.h"

class _cylinder:public _objRev
{
    public:
      _cylinder(){};
      void initialize(float height = 1, float radius = 0.5, int hCuts = 1, int vCuts = 1, int rCuts = 6, bool bottom = true, bool top = true);
};
#endif

