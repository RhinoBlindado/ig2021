#ifndef TELESCOPE_H
#define TELESCOPE_H

#include "object3d.h"

//  Subparts
#include "classTelescope_part_tripod.h"

class _telescope:public _object3D
{
    private:
     _teleTripod __tripod;
     float alpha;
     float beta;
     float gamma;

    public:
        _telescope();
        void initizalice();
        void draw(int style = 1, float alpha = 0, float beta = 0, float gamma = 0);

        void rotateFirstDegree(float nAlpha = 0);
        void rotateSecondDegree(float nBeta = 0);
        void rotateThirdDegree(float nGamma = 0);
};

#endif // TELESCOPE_H
