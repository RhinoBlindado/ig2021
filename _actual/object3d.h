/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "basic_object3d.h"
#include <QImage>

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _object3D:public _basic_object3D
{
  public:
  vector<_vertex3ui> Triangles;
  vector<_vertex3f>  trigNormals;
  vector<_vertex3f>  vectNormals;

  bool flatLight;
  bool smoothLight;

  // Drawing Methods
  void draw(int style = 0);
  void draw_line();
  void draw_fill();
  void draw_chess(vector<float> color1 = {1,0.4451,0.8078}, vector<float> color2 = {0.0039,0.8039,0.9961});

  void drawIlum();
  void drawUnLitTex();
  void calculateTrigNormals();
  void calculateVertNormals();

  // Setters
  void setLighting(int type);
  void setFlatLight();
  void setSmoothLight();
  void setTexture(QImage texture);

  void setMaterialDiffuse(_vertex3f color);
  void setMaterialSpecular(_vertex3f color);
  void setMaterialAmbient(_vertex3f color);
  void setMaterialShininess(float color);

};

#endif // OBJECT3D_H
