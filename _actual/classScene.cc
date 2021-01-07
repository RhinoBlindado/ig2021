#include "classScene.h"

using namespace _colors_ne;

/**
 * @brief Initialize the scene
 * @param scale     Scale of the PLYs
 * @param initSide  Side of the PLY Matrix
 */
void _scene::initialize(float scale, int initSide)
{
    int mtrxSize = initSide*initSide;
    this->side = initSide;

    plyMatrix.resize(mtrxSize);
    for(auto i = 0; i < mtrxSize; i++)
    {
        plyMatrix[i].initialize(scale,"../ply_models/big_porsche.ply");
    }
}

/**
 * @brief Draw the PLY matrix
 * @param style     Used to discern if scene is being picked.
 */
void _scene::draw(int style)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    float R,G,B;

    for(auto i = 0; i < side; i++)
    {
        for(auto j = 0; j < side; j++)
        {
            glPushMatrix();

               glTranslated(i,0,j);

               if(selObj == (j + (i * side)))
               {
                    glColor3fv((GLfloat *) &YEllOW);
               }

               // If Picked
               if(style == 6)
               {
                    // For a given PLY, convert its index into a color using bitmasking.
                    R = ((j + (i * side)) & 0x00FF0000) >> 16;
                    G = ((j + (i * side)) & 0x0000FF00) >> 8;
                    B = ((j + (i * side)) & 0x000000FF);
                    //  Use the mask to make a color.
                    glColor3f(R/255.0f, G/255.0f, B/255.0f);
               }

               plyMatrix[j + (i * side)].draw_fill();

               if(selObj == (j + (i * side)))
               {
                   glColor3fv((GLfloat *) &BLUE);
               }

           glPopMatrix();
        }
    }

    glPopMatrix();
}

/**
 * @brief Select the index of an object
 * @param sel   Index
 */
void _scene::setObjSelected(int sel)
{
    this->selObj = sel;
}
