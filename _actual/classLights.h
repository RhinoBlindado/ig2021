#ifndef CLASSLIGHTS_H
#define CLASSLIGHTS_H

#include <GL/gl.h>
#include "vertex.h"
#include "colors.h"
#define PI 3.14159265

class _lights
{
    private:
        _vertex4f lightPos = _vertex4f{0, 50, 100, 0};
        _vertex4f lightPos2 = _vertex4f{0, 0, 5, 1};
        _vertex4f actPos2 = _vertex4f{0, 0, 5, 1};

    public:
        _lights(){};
        void initialize();

        void toggleFirstLight(bool toggle);
        void toggleSecondLight(bool toggle);
        void rotateSecondLight(float nDelta);
};

#endif // CLASSLIGHTS_H

