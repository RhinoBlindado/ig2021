#ifndef TELESCOPE_H
#define TELESCOPE_H

#include "object3d.h"

//  Subparts
#include "classTelescope_part_tripod.h"
#include "classTelescope_part_mount.h"
#include "classTelescope_part_tube.h"

class _telescope:public _object3D
{
    private:
     _teleTripod __tripod;
     _teleMount __mount;
     _teleTube __tube;

     float alpha;
     float beta;
     float gamma;

    public:
        _telescope();
        void initizalice();
        void draw(int style = 1);

        void rotateFirstDegree(float nAlpha = 0);
        void rotateSecondDegree(float nBeta = 0);
        void rotateThirdDegree(float nGamma = 0);

        void setLighting(int style);
        void setMaterial();

};

#endif // TELESCOPE_H
