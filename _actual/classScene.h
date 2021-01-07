#ifndef CLASSSCENE_H
#define CLASSSCENE_H

#include "classObjectPly.h"

/** [P5}
 * @brief The object PLY Scene Class
 */
class _scene
{
    private:
        int selObj = -1;
        int side;
        vector<_ply> plyMatrix;

    public:
            _scene(){};
            void initialize(float scale=0.1, int initSide = 4);
            void draw(int style);
            void setObjSelected(int selection);
};

#endif // CLASSSCENE_H
