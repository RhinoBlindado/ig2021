/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#include "glwidget.h"
#include "window.h"
#include <cmath>

using namespace std;
using namespace _gl_widget_ne;
using namespace _colors_ne;


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_gl_widget::_gl_widget(_window *Window1):Window(Window1)
{
  setMinimumSize(300, 300);
  setFocusPolicy(Qt::StrongFocus);
  Object = _gl_widget_ne::OBJECT_TETRAHEDRON;
}


/*****************************************************************************//**
 * Evento tecla pulsada
 *
 *
 *
 *****************************************************************************/

void _gl_widget::keyPressEvent(QKeyEvent *Keyevent)
{
  switch(Keyevent->key()){
      // OBJECTS
      //    Tetrahedron
      case Qt::Key_1:
            Object=OBJECT_TETRAHEDRON;
            Window->modelSelectorInteraction(0);
      break;
      //    P1
      //    Cube
      case Qt::Key_2:
            Object=OBJECT_CUBE;
            Window->modelSelectorInteraction(1);
      break;

      //    P2
      //    Cone
      case Qt::Key_3:
            Object=OBJECT_CONE;
            Window->modelSelectorInteraction(2);
      break;

      //    Cylinder
      case Qt::Key_4:
            Object=OBJECT_CYLINDER;
            Window->modelSelectorInteraction(3);
      break;

      //    Sphere
      case Qt::Key_5:
            Object=OBJECT_SPHERE;
            Window->modelSelectorInteraction(4);
      break;

      //    PLY Object
      case Qt::Key_6:
            Object=OBJECT_PLY;
            Window->modelSelectorInteraction(5);
      break;

      //    P3
      //    Hierarchical Model
      case Qt::Key_7:
            Object=OBJECT_HIER;
            Window->modelSelectorInteraction(6);
      break;

      //    P4
      //    Chessboard
      case Qt::Key_8:
            Object=OBJECT_CHESS;
            Window->modelSelectorInteraction(7);
      break;


      //    P5
      //    PLY Scene
      case Qt::Key_9:
            Object=OBJECT_SCENE;

      break;

      // [P3] ANIMATION
      //    First degree of freedom keys and rate of modification
      case Qt::Key_Q:alpha+=ANGLE_STEP*modAlpha;break;
      case Qt::Key_W:alpha-=ANGLE_STEP*modAlpha;break;
      case Qt::Key_E:modAlpha+=0.5;break;
      case Qt::Key_R:modAlpha-=0.5;break;

      //    Second degree of freedom keys and rate of modification
      case Qt::Key_S:beta+=ANGLE_STEP*modBeta;break;
      case Qt::Key_D:beta-=ANGLE_STEP*modBeta;break;
      case Qt::Key_T:modBeta+=0.5;break;
      case Qt::Key_Y:modBeta-=0.5;break;

      //    Third degree of freedom keys and rate of modification
      case Qt::Key_Z:gamma+=ANGLE_STEP*modGamma;break;
      case Qt::Key_X:gamma-=ANGLE_STEP*modGamma;break;
      case Qt::Key_U:modGamma+=0.01;break;
      case Qt::Key_I:modGamma-=0.01;break;

      //    Auto Animation key
      case Qt::Key_A:animation=!animation;break;

      // DRAWING
      //    Draw Point
      case Qt::Key_P:
            Draw_point=!Draw_point;
            Window->pointCheckBoxInteraction(Draw_point);
      break;

      //    P1
      //    Draw Lines
      case Qt::Key_L:
            Draw_line=!Draw_line;
            Window->lineCheckBoxInteraction(Draw_line);
      break;

      //    Draw Fill
      case Qt::Key_F1:
            Draw_fill=!Draw_fill;
            Window->fillCheckBoxInteraction(Draw_fill);
      break;

      //    Draw Chess
      case Qt::Key_F2:
            Draw_chess=!Draw_chess;
            Window->chessCheckBoxInteraction(Draw_chess);
      break;

    // [P4] LIGHTING & TEXTURES
    //    Flat Shaded Light Mode
    case Qt::Key_F3:
          flatLit=!flatLit;
    break;
    //    Goraund Shaded Light Mode
    case Qt::Key_F4:
          smoothLit=!smoothLit;
    ;break;
    //    Unlit Texture Mode
    case Qt::Key_F5:
          unLitTextured = !unLitTextured;
    break;
    //    Flat Shaded Light Texture Mode
    case Qt::Key_F6:
          litFlatTextured = !litFlatTextured;
    break;
    //    Goraund Shaded Light Texture Mode
    case Qt::Key_F7:
          litSmoothTextured = !litSmoothTextured;
    break;

    //    Toggle ON/OFF First Light
    case Qt::Key_J:
          firstLight=!firstLight;
    break;
    //    Toggle ON/OFF Second Light
    case Qt::Key_K:
          secondLight=!secondLight;
    break;
    //    Toggle between materials
    case Qt::Key_M:
          actMaterial++;
          actMaterial = actMaterial % 4;
    break;


    // CAMERA
    //      Movement
    case Qt::Key_Left:Observer_angle_y-=ANGLE_STEP;break;
    case Qt::Key_Right:Observer_angle_y+=ANGLE_STEP;break;
    case Qt::Key_Up:Observer_angle_x-=ANGLE_STEP;break;
    case Qt::Key_Down:Observer_angle_x+=ANGLE_STEP;break;
    //      Zoom
    case Qt::Key_Minus:Observer_distance*=1.2;break;
    case Qt::Key_Plus:Observer_distance/=1.2;break;

    // [P5] PROJECTION
    case Qt::Key_C:perspective = true;break;
    case Qt::Key_V:perspective = false;break;
  }

    update();
}


/*****************************************************************************//**
 * Limpiar ventana
 *
 *
 *
 *****************************************************************************/

void _gl_widget::clear_window()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



/*****************************************************************************//**
 * Funcion para definir la transformación de proyeccion
 *
 *
 *
 *****************************************************************************/

void _gl_widget::change_projection()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
  // Front_plane>0  Back_plane>PlanoDelantero)

  // P5
  if(perspective)
      glFrustum(X_MIN, X_MAX, Y_MIN * ((float)this->height()/(float)this->width()), Y_MAX * ((float)this->height()/(float)this->width()),
                FRONT_PLANE_PERSPECTIVE, BACK_PLANE_PERSPECTIVE);
    else
      glOrtho(10*X_MIN*Observer_distance, 10*X_MAX*Observer_distance,
              10*Y_MIN*Observer_distance * ((float)this->height()/(float)this->width()),
              10*Y_MAX*Observer_distance * ((float)this->height()/(float)this->width()),
              FRONT_PLANE_PERSPECTIVE, BACK_PLANE_PERSPECTIVE);
}



/*****************************************************************************//**
 * Funcion para definir la transformación de vista (posicionar la camara)
 *
 *
 *
 *****************************************************************************/

void _gl_widget::change_observer()
{
  // posicion del observador
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0,0,-Observer_distance);
  glRotatef(Observer_angle_x,1,0,0);
  glRotatef(Observer_angle_y,0,1,0);
}


/*****************************************************************************//**
 * Funcion que dibuja los objetos
 *
 *
 *
 *****************************************************************************/

void _gl_widget::draw_objects()
{

  // AXIS
  Axis.draw_line();

  // OBJECTS
  if (Draw_point){
    glPointSize(5);
    glColor3fv((GLfloat *) &BLACK);
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_point();break;
    case OBJECT_CUBE:Cube.draw_point();break;
    case OBJECT_CONE:Cone.draw_point();break;
    case OBJECT_CYLINDER:Cylinder.draw_point();break;
    case OBJECT_SPHERE:Sphere.draw_point();break;
    case OBJECT_PLY:Ply.draw_point();break;
    case OBJECT_HIER:Hier.draw(0);break;
    default:break;
    }
  }

  if (Draw_line){
    glLineWidth(3);
    glColor3fv((GLfloat *) &MAGENTA);
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_line();break;
    case OBJECT_CUBE:Cube.draw_line();break;
    case OBJECT_CONE:Cone.draw_line();break;
    case OBJECT_CYLINDER:Cylinder.draw_line();break;
    case OBJECT_SPHERE:Sphere.draw_line();break;
    case OBJECT_PLY:Ply.draw_line();break;
    case OBJECT_HIER:Hier.draw(1);break;
    case OBJECT_CHESS:Chess.draw(1);break;
    default:break;
    }
  }

  if (Draw_fill){
    glColor3fv((GLfloat *) &BLUE);
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_fill();break;
    case OBJECT_CUBE:Cube.draw_fill();break;
    case OBJECT_CONE:Cone.draw_fill();break;
    case OBJECT_CYLINDER:Cylinder.draw(2);break;
    case OBJECT_SPHERE:Sphere.draw_fill();break;
    case OBJECT_PLY:Ply.draw_fill();break;
    case OBJECT_HIER:Hier.draw(2);break;
    case OBJECT_CHESS:Chess.draw(2);break;
    case OBJECT_SCENE:Scene.draw(2);break;
    default:break;
    }
  }

  if (Draw_chess){
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_chess();break;
    case OBJECT_CUBE:Cube.draw_chess();break;
    case OBJECT_CONE:Cone.draw_chess();break;
    case OBJECT_CYLINDER:Cylinder.draw_chess();break;
    case OBJECT_SPHERE:Sphere.draw_chess();break;
    case OBJECT_PLY:Ply.draw_chess();break;
    case OBJECT_HIER:Hier.draw(3);break;
    case OBJECT_CHESS:Chess.draw(3);break;
    default:break;
    }
  }

  // [P3] ANIMATION
  //    Set the degrees of rotation of each degree of freedom.
  this->constrainAngles();
  Hier.rotateFirstDegree(alpha);
  Hier.rotateSecondDegree(beta);
  Hier.rotateThirdDegree(gamma);

  // [P4] LIGHTING

  //    Toggle Lights
  light.toggleFirstLight(firstLight);
  light.toggleSecondLight(secondLight);

  //    Flat Lighting
  if(flatLit)
  {
      switch (Object)
      {
          case OBJECT_TETRAHEDRON:
                Tetrahedron.setMaterialAmbient(__material[actMaterial].ambient);
                Tetrahedron.setMaterialSpecular(__material[actMaterial].specular);
                Tetrahedron.setMaterialDiffuse(__material[actMaterial].diffuse);
                Tetrahedron.setMaterialShininess(__material[actMaterial].shine);

                Tetrahedron.setLighting(1);
                Tetrahedron.drawIlum();
          break;

          case OBJECT_CUBE:
                Cube.setMaterialAmbient(__material[actMaterial].ambient);
                Cube.setMaterialSpecular(__material[actMaterial].specular);
                Cube.setMaterialDiffuse(__material[actMaterial].diffuse);
                Cube.setMaterialShininess(__material[actMaterial].shine);

                Cube.setLighting(1);
                Cube.drawIlum();
          break;

          case OBJECT_CONE:
                Cone.setMaterialAmbient(__material[actMaterial].ambient);
                Cone.setMaterialSpecular(__material[actMaterial].specular);
                Cone.setMaterialDiffuse(__material[actMaterial].diffuse);
                Cone.setMaterialShininess(__material[actMaterial].shine);

                Cone.setLighting(1);
                Cone.drawIlum();
          break;

          case OBJECT_CYLINDER:
                Cylinder.setMaterialAmbient(__material[actMaterial].ambient);
                Cylinder.setMaterialSpecular(__material[actMaterial].specular);
                Cylinder.setMaterialDiffuse(__material[actMaterial].diffuse);
                Cylinder.setMaterialShininess(__material[actMaterial].shine);

                Cylinder.setLighting(1);
                Cylinder.drawIlum();
          break;

          case OBJECT_SPHERE:
                Sphere.setMaterialAmbient(__material[actMaterial].ambient);
                Sphere.setMaterialSpecular(__material[actMaterial].specular);
                Sphere.setMaterialDiffuse(__material[actMaterial].diffuse);
                Sphere.setMaterialShininess(__material[actMaterial].shine);

                Sphere.setLighting(1);
                Sphere.drawIlum();
          break;

          case OBJECT_PLY:
                Ply.setMaterialAmbient(__material[actMaterial].ambient);
                Ply.setMaterialSpecular(__material[actMaterial].specular);
                Ply.setMaterialDiffuse(__material[actMaterial].diffuse);
                Ply.setMaterialShininess(__material[actMaterial].shine);

                Ply.setLighting(1);
                Ply.drawIlum();
          break;
          case OBJECT_HIER:
                Hier.setLighting(1);
                Hier.draw(4);
          break;
          case OBJECT_CHESS:
                Chess.setMaterialAmbient(__material[actMaterial].ambient);
                Chess.setMaterialSpecular(__material[actMaterial].specular);
                Chess.setMaterialDiffuse(__material[actMaterial].diffuse);
                Chess.setMaterialShininess(__material[actMaterial].shine);

                Chess.setLighting(1);
                Chess.drawIlum();
          break;
          default:break;
      }
  }

  //    Smooth Ligthing
  if(smoothLit)
  {
      switch (Object)
      {
          case OBJECT_TETRAHEDRON:
                Tetrahedron.setMaterialAmbient(__material[actMaterial].ambient);
                Tetrahedron.setMaterialSpecular(__material[actMaterial].specular);
                Tetrahedron.setMaterialDiffuse(__material[actMaterial].diffuse);
                Tetrahedron.setMaterialShininess(__material[actMaterial].shine);

                Tetrahedron.setLighting(2);
                Tetrahedron.drawIlum();
          break;

          case OBJECT_CUBE:
                Cube.setMaterialAmbient(__material[actMaterial].ambient);
                Cube.setMaterialSpecular(__material[actMaterial].specular);
                Cube.setMaterialDiffuse(__material[actMaterial].diffuse);
                Cube.setMaterialShininess(__material[actMaterial].shine);

                Cube.setLighting(2);
                Cube.drawIlum();
          break;

          case OBJECT_CONE:
                Cone.setMaterialAmbient(__material[actMaterial].ambient);
                Cone.setMaterialSpecular(__material[actMaterial].specular);
                Cone.setMaterialDiffuse(__material[actMaterial].diffuse);
                Cone.setMaterialShininess(__material[actMaterial].shine);

                Cone.setLighting(2);
                Cone.drawIlum();
          break;

          case OBJECT_CYLINDER:
                Cylinder.setMaterialAmbient(__material[actMaterial].ambient);
                Cylinder.setMaterialSpecular(__material[actMaterial].specular);
                Cylinder.setMaterialDiffuse(__material[actMaterial].diffuse);
                Cylinder.setMaterialShininess(__material[actMaterial].shine);

                Cylinder.setLighting(2);
                Cylinder.drawIlum();
          break;

          case OBJECT_SPHERE:
                Sphere.setMaterialAmbient(__material[actMaterial].ambient);
                Sphere.setMaterialSpecular(__material[actMaterial].specular);
                Sphere.setMaterialDiffuse(__material[actMaterial].diffuse);
                Sphere.setMaterialShininess(__material[actMaterial].shine);

                Sphere.setLighting(2);
                Sphere.drawIlum();
          break;

          case OBJECT_PLY:
                Ply.setMaterialAmbient(__material[actMaterial].ambient);
                Ply.setMaterialSpecular(__material[actMaterial].specular);
                Ply.setMaterialDiffuse(__material[actMaterial].diffuse);
                Ply.setMaterialShininess(__material[actMaterial].shine);

                Ply.setLighting(2);
                Ply.drawIlum();
          break;
          case OBJECT_HIER:
                Hier.setLighting(2);
                Hier.draw(4);
          break;
          case OBJECT_CHESS:
                Chess.setMaterialAmbient(__material[actMaterial].ambient);
                Chess.setMaterialSpecular(__material[actMaterial].specular);
                Chess.setMaterialDiffuse(__material[actMaterial].diffuse);
                Chess.setMaterialShininess(__material[actMaterial].shine);

                Chess.setLighting(2);
                Chess.drawIlum();
          break;
          default:break;
      }
  }

  // [P4] TEXTURES
  //    Unlit Textured
  if(unLitTextured)
  {
    switch (Object)
    {
        case OBJECT_CYLINDER:
            CylinderTex.setTexture(texture);
            CylinderTex.setLighting(0);
            CylinderTex.drawTex();
        break;

        case OBJECT_SPHERE:
            SphereTex.setTexture(texture);
            SphereTex.setLighting(0);
            SphereTex.drawTex();
        break;

        case OBJECT_CHESS:
            Chess.setTexture(texture);
            Chess.setLighting(0);
            Chess.drawTex();
        break;
        default:break;
    }
  }

  //    Flat Lit Textured
  if(litFlatTextured)
  {
    switch (Object)
    {
        case OBJECT_CYLINDER:
            CylinderTex.setMaterialAmbient(__material[actMaterial].ambient);
            CylinderTex.setMaterialSpecular(__material[actMaterial].specular);
            CylinderTex.setMaterialDiffuse(__material[actMaterial].diffuse);
            CylinderTex.setMaterialShininess(__material[actMaterial].shine);

            CylinderTex.setTexture(texture);
            CylinderTex.setLighting(1);
            CylinderTex.drawTex();
        break;

        case OBJECT_SPHERE:
            SphereTex.setMaterialAmbient(__material[actMaterial].ambient);
            SphereTex.setMaterialSpecular(__material[actMaterial].specular);
            SphereTex.setMaterialDiffuse(__material[actMaterial].diffuse);
            SphereTex.setMaterialShininess(__material[actMaterial].shine);

            SphereTex.setTexture(texture);
            SphereTex.setLighting(1);
            SphereTex.drawTex();
        break;

        case OBJECT_CHESS:
            Chess.setMaterialAmbient(__material[actMaterial].ambient);
            Chess.setMaterialSpecular(__material[actMaterial].specular);
            Chess.setMaterialDiffuse(__material[actMaterial].diffuse);
            Chess.setMaterialShininess(__material[actMaterial].shine);

            Chess.setTexture(texture);
            Chess.setLighting(1);
            Chess.drawTex();
        break;
        default:break;
    }
  }

  //    Smooth Lit Textured
  if(litSmoothTextured)
  {
      switch (Object)
      {
        case OBJECT_CYLINDER:
            CylinderTex.setMaterialAmbient(__material[actMaterial].ambient);
            CylinderTex.setMaterialSpecular(__material[actMaterial].specular);
            CylinderTex.setMaterialDiffuse(__material[actMaterial].diffuse);
            CylinderTex.setMaterialShininess(__material[actMaterial].shine);

            CylinderTex.setTexture(texture);
            CylinderTex.setLighting(2);
            CylinderTex.drawTex();
        break;

        case OBJECT_SPHERE:
            SphereTex.setMaterialAmbient(__material[actMaterial].ambient);
            SphereTex.setMaterialSpecular(__material[actMaterial].specular);
            SphereTex.setMaterialDiffuse(__material[actMaterial].diffuse);
            SphereTex.setMaterialShininess(__material[actMaterial].shine);

            SphereTex.setTexture(texture);
            SphereTex.setLighting(2);
            SphereTex.drawTex();
        break;

        case OBJECT_CHESS:
            Chess.setMaterialAmbient(__material[actMaterial].ambient);
            Chess.setMaterialSpecular(__material[actMaterial].specular);
            Chess.setMaterialDiffuse(__material[actMaterial].diffuse);
            Chess.setMaterialShininess(__material[actMaterial].shine);

            Chess.setTexture(texture);
            Chess.setLighting(2);
            Chess.drawTex();
        break;
        default:break;
      }
  }

  update();
}



/*****************************************************************************//**
 * Evento de dibujado
 *
 *
 *
 *****************************************************************************/

void _gl_widget::paintGL()
{
  clear_window();
  change_projection();
  change_observer();
  draw_objects();
}


/*****************************************************************************//**
 * Evento de cambio de tamaño de la ventana
 *
 *
 *
 *****************************************************************************/

void _gl_widget::resizeGL(int Width1, int Height1)
{
  glViewport(0,0,Width1,Height1);

}


/*****************************************************************************//**
 * Inicialización de OpenGL
 *
 *
 *
 *****************************************************************************/

void _gl_widget::initializeGL()
{
  const GLubyte* strm;

  strm = glGetString(GL_VENDOR);
  std::cerr << "Vendor: " << strm << "\n";
  strm = glGetString(GL_RENDERER);
  std::cerr << "Renderer: " << strm << "\n";
  strm = glGetString(GL_VERSION);
  std::cerr << "OpenGL Version: " << strm << "\n";

  if (strm[0] == '1'){
    std::cerr << "Only OpenGL 1.X supported!\n";
    exit(-1);
  }

  strm = glGetString(GL_SHADING_LANGUAGE_VERSION);
  std::cerr << "GLSL Version: " << strm << "\n";

  int Max_texture_size=0;
  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &Max_texture_size);
  std::cerr << "Max texture size: " << Max_texture_size << "\n";

  glClearColor(1.0,1.0,1.0,1.0);
  glEnable(GL_DEPTH_TEST);;

  Observer_angle_x=0;
  Observer_angle_y=0;
  Observer_distance=DEFAULT_DISTANCE;

  // DRAWING
  Draw_point=false;
  Draw_line=true;
  Draw_fill=false;
  Draw_chess=false;

  // OBJECTS
  //    Initalizing the objects.
  //    P2
  Cylinder.initialize(1, 0.5, 20, 10, 30, true, true);
  Sphere.initialize(0.5, 40, 40);
  Cone.initialize(1, 0.5, 20, 10, 30);
  Ply.initialize(1,"../ply_models/utah.ply");

  //    P4
  Chess.initialize(1.777,1);
  SphereTex.initialize(0.5, 40, 40);
  CylinderTex.initialize(1, 0.5, 20, 10, 30);

  //    P5
  Scene.initialize(0.07, 4);

  // [P3] ANIMATION
  //    Setting initial angle variables and Modifiers.
  alpha = 0;
  beta  = 0;
  gamma = 0;
  delta = 0;
  modAlpha = 1;
  modBeta  = 1;
  modGamma = 1;

  //    Auto Animation bools.
  animation = false;
  foward1 = true;
  foward2 = true;

  // [P4] LIGHTING
  light.initialize();
  flatLit = false;
  smoothLit = false;
  firstLight = false;
  secondLight = false;

  // [P4] MATERIALS
  //    Gold
  __material[MAT_GOLD].ambient  = _vertex4f(0.24725f, 0.2245f, 0.0645f, 1.0f);
  __material[MAT_GOLD].diffuse  = _vertex4f(0.34615f, 0.3143f, 0.0903f, 1.0f);
  __material[MAT_GOLD].specular = _vertex4f(0.797357f, 0.723991f, 0.208006f, 1.0f);
  __material[MAT_GOLD].shine    = 83.2f;

  //    Cyan Plastic
  __material[MAT_PLASTIC].ambient  = _vertex4f(0.0f, 0.1f, 0.06f, 1.0f);
  __material[MAT_PLASTIC].diffuse  = _vertex4f(0.0f, 0.50980392f, 0.50980392f, 1.0f);
  __material[MAT_PLASTIC].specular = _vertex4f(0.50196078f, 0.50196078f, 0.50196078f, 1.0f);
  __material[MAT_PLASTIC].shine    = 32.0f;

  //    Red Rubber
  __material[MAT_RUBBER].ambient  = _vertex4f(0.05f, 0.0f, 0.0f, 1.0f);
  __material[MAT_RUBBER].diffuse = _vertex4f(0.5f, 0.4f, 0.4f, 1.0f);
  __material[MAT_RUBBER].specular  = _vertex4f(0.7f, 0.04f, 0.04f, 1.0f);
  __material[MAT_RUBBER].shine    = 10.f;

  //    Default Material
  __material[MAT_NULL].ambient = _vertex4f(0.2, 0.2, 0.2, 1.0);
  __material[MAT_NULL].diffuse = _vertex4f(0.8, 0.8, 0.8, 1.0);
  __material[MAT_NULL].specular = _vertex4f(0.0, 0.0, 0.0, 1.0);
  __material[MAT_NULL].shine    = 0.0f;

  actMaterial = 3;

  // [P4] TEXTURES
  unLitTextured = false;
  litFlatTextured = false;
  litSmoothTextured = false;

  // [P5] CAMERA
  perspective = true;
  lastClickX = 0;
  lastClickY = 0;
  mouseDrag = false;

  // [P5] PICK
  glewInit();
  Window_width = this->width();
  Window_height = this->height();
}

/**
 * [P3]
 * @brief Constrain the angles of the hierarchical model. Also update the UI.
 */
void _gl_widget::constrainAngles()
{
    Window->alphaSetText(to_string(modAlpha));
    Window->alphaSetSlider((int)modAlpha*100);

    Window->betaSetText(to_string(modBeta));
    Window->betaSetSlider((int)modBeta*100);

    Window->gammaSetText(to_string(modGamma));
    Window->gammaSetSlider((int)modGamma*100);

    alpha = fmod(alpha,360);

    if(beta > 42)
      beta = 42;

    if(beta < -42)
      beta = -42;

    if(gamma > 10)
      gamma = 10;

    if(gamma < -10)
      gamma = -10;

    if(modAlpha > 20)
       modAlpha = 20;

    if(modAlpha < 0)
       modAlpha = 0;

    if(modBeta > 20)
       modBeta = 20;

    if(modBeta < 0)
       modBeta = 0;

    if(modGamma > 20)
       modGamma = 20;

    if(modGamma < 0)
       modGamma = 0;
}

/**
 * [P3][P4]
 * @brief Toggle the animation of the hierarchical object and 2nd light
 */
void _gl_widget::slotAnimationToggle()
{
    if(animation)
    {
        // This is so that when the telescope reaches its max angle, reverses the movement.
        if(foward1)
            beta += ANGLE_STEP*modAlpha;
        else
            beta -= ANGLE_STEP*modAlpha;

        if(beta < -42 || beta > 42)
            foward1 = !foward1;

        if(foward2)
            gamma += ANGLE_STEP*modGamma;
        else
            gamma -= ANGLE_STEP*modGamma;

        if(gamma < -10 || gamma > 10)
            foward2 = !foward2;

        // This is so that the numbers stay between [0º, 360º]
        alpha = fmod(alpha  += ANGLE_STEP*modBeta, 360);

        if(secondLight)
        {
            // Ditto from Alpha.
            delta = fmod(delta += ANGLE_STEP, 360);
            light.rotateSecondLight(delta);
        }

        update();
    }
}

/**
 * [P4]
 * @brief Obtain the image for the texture.
 * @param _texture  A QImage file that will be the texture.
 */
void _gl_widget::getTexture(QImage _texture)
{
    this->texture = _texture;
}

/**
 * [P5]
 * @brief Capture different parameters when the mouse is right or left clicked.
 * @param event     The mouse event.
 */
void _gl_widget::mousePressEvent(QMouseEvent *event)
{
    //  If right-clicked: Select triangles.
    if(event->buttons() & Qt::RightButton)
    {
        Window_width = this->width();
        Window_height = this->height();

        Selection_position_x = (event->x());
        Selection_position_y = (Window_height - event->y());
        this->pick();
    }

    //  If left-clicked: Move the camera.
    if(event->buttons() & Qt::LeftButton)
    {
        lastClickX = event->x();
        lastClickY = event->y();
        mouseDrag = true;
    }
    update();
}

/**
 * [P5]
 * @brief Capture the coordinates when the mouse is being dragged and also being left clicked.
 * @param event     The mouse event.
 */
void _gl_widget::mouseMoveEvent(QMouseEvent *event)
{
    if(mouseDrag)
    {
        Observer_angle_x += (event->y() - lastClickY) * 0.05;
        Observer_angle_y += (event->x() - lastClickX) * 0.05;
    }
    update();
}

/**
 * [P5]
 * @brief Capture when the mouse buttons have been released.
 * @param event     The mouse event.
 */
void _gl_widget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mouseDrag = false;
    }
    update();
}

/**
 * [P5]
 * @brief Capture the event when the mouse wheel is spun.
 * @param scrollWheel   The scrollwheel event.
 */
void _gl_widget::wheelEvent(QWheelEvent *scrollWheel)
{
    // Given the scrollwheel angle, divide it and negated so it behaves accordinly.
    Observer_distance += (-(float)(scrollWheel->angleDelta().y()))/360;
    update();
}

// [P5]
// Skeleton for pick fuction using glDeleteFramebuffers
//
// Domingo Martín Perandrés
// GPL
//
// Window_width and Window_height are the widht and height of the device window
// Selection_position_x and Selection_position_y are the coordinates of the mouse

void _gl_widget::pick()
{
  makeCurrent();

  // Frame Buffer Object to do the off-screen rendering
  GLuint FBO;
  glGenFramebuffers(1,&FBO);
  glBindFramebuffer(GL_FRAMEBUFFER,FBO);

  // Texture for drawing
  GLuint Color_texture;
  glGenTextures(1,&Color_texture);
  glBindTexture(GL_TEXTURE_2D,Color_texture);
  // RGBA8
  glTexStorage2D(GL_TEXTURE_2D,1,GL_RGBA8, Window_width,Window_height);
  // this implies that there is not mip mapping
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

  // Texure for computing the depth
  GLuint Depth_texture;
  glGenTextures(1,&Depth_texture);
  glBindTexture(GL_TEXTURE_2D,Depth_texture);
  // Float
  glTexStorage2D(GL_TEXTURE_2D,1,GL_DEPTH_COMPONENT24, Window_width,Window_height);

  // Attatchment of the textures to the FBO
  glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,Color_texture,0);
  glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,Depth_texture,0);

  // OpenGL will draw to these buffers (only one in this case)
  static const GLenum Draw_buffers[]={GL_COLOR_ATTACHMENT0};
  glDrawBuffers(1,Draw_buffers);

  /*************************/
  // dibujar escena para seleccion
  clear_window();
  change_projection();
  change_observer();
  switch (Object)
  {
      case OBJECT_TETRAHEDRON:Tetrahedron.drawSelection();break;
      case OBJECT_CUBE:Cube.drawSelection();break;
      case OBJECT_CONE:Cone.drawSelection();break;
      case OBJECT_CYLINDER:Cylinder.drawSelection();break;
      case OBJECT_SPHERE:Sphere.drawSelection();break;
      case OBJECT_PLY:Ply.drawSelection();break;
      case OBJECT_CHESS:Chess.drawSelection();break;
      case OBJECT_SCENE:Scene.draw(6);break;
      default:break;
  }
  /*************************/

  // get the pixel
  int Color;
  glReadBuffer(GL_FRONT);
  glPixelStorei(GL_PACK_ALIGNMENT,1);
  glReadPixels(Selection_position_x,Selection_position_y,1,1,GL_RGBA,GL_UNSIGNED_BYTE,&Color);

  /*************************/
  // actualizar el identificador de la parte seleccionada en el objeto
  int selTriangle;
  uint B = (uint)((Color & 0x00FF0000) >> 16);
  uint G = (uint)((Color & 0x0000FF00) >> 8);
  uint R = (uint)(Color & 0x000000FF);

  selTriangle = (R << 16) + (G << 8) + B;

  switch (Object)
  {
      case OBJECT_TETRAHEDRON:Tetrahedron.setTrigSelected(selTriangle);break;
      case OBJECT_CUBE:Cube.setTrigSelected(selTriangle);break;
      case OBJECT_CONE:Cone.setTrigSelected(selTriangle);break;
      case OBJECT_CYLINDER:Cylinder.setTrigSelected(selTriangle);break;
      case OBJECT_SPHERE:Sphere.setTrigSelected(selTriangle);break;
      case OBJECT_PLY:Ply.setTrigSelected(selTriangle);break;
      case OBJECT_CHESS:Chess.setTrigSelected(selTriangle);break;
      case OBJECT_SCENE:Scene.setObjSelected(selTriangle);break;
      default:break;
  }
  /*************************/

  glDeleteTextures(1, &Color_texture);
  glDeleteTextures(1, &Depth_texture);
  glDeleteFramebuffers(1, &FBO);
  // the normal framebuffer takes the control of drawing
 glBindFramebuffer(GL_DRAW_FRAMEBUFFER, defaultFramebufferObject());

}

// EXTRA: COMMUNICATION WITH QT
/**
 * @brief Chaging the state of the drawing style depending on the checkbox.
 * @param state     State of the boolean
 */
void _gl_widget::slotPoint(int state)
{
    if(state == Qt::Checked)
        Draw_point = true;
    else
        Draw_point = false;
    update();
}

// Ditto for each draw style.
void _gl_widget::slotLine(int state)
{
    if(state == Qt::Checked)
        Draw_line = true;
    else
        Draw_line = false;
    update();
}

void _gl_widget::slotFill(int state)
{
    if(state == Qt::Checked)
        Draw_fill= true;
    else
        Draw_fill = false;
    update();
}

void _gl_widget::slotChess(int state)
{
    if(state == Qt::Checked)
        Draw_chess = true;
    else
        Draw_chess = false;
    update();
}

void _gl_widget::slotFlat(int state)
{
    if(state == Qt::Checked)
        flatLit = true;
    else
        flatLit = false;
    update();
}

void _gl_widget::slotSmooth(int state)
{
    if(state == Qt::Checked)
        smoothLit = true;
    else
        smoothLit = false;
    update();
}

void _gl_widget::slotUnlitText(int state)
{
    if(state == Qt::Checked)
        unLitTextured = true;
    else
        unLitTextured = false;
    update();
}

void _gl_widget::slotFlatText(int state)
{
    if(state == Qt::Checked)
        litFlatTextured = true;
    else
        litFlatTextured = false;
    update();
}

void _gl_widget::slotSmoothText(int state)
{
    if(state == Qt::Checked)
        litSmoothTextured = true;
    else
        litSmoothTextured = false;
    update();
}

void _gl_widget::slotAnimation(int state)
{
    if(state == Qt::Checked)
        animation = true;
    else
        animation = false;
    update();
}

void _gl_widget::slotFirstLight(int state)
{
    if(state == Qt::Checked)
        firstLight = true;
    else
        firstLight = false;
    update();
}

void _gl_widget::slotSecondLight(int state)
{
    if(state == Qt::Checked)
        secondLight = true;
    else
        secondLight = false;
    update();
}

void _gl_widget::slotModel(int index)
{
    switch(index)
    {
        case 0:Object=OBJECT_TETRAHEDRON;break;
        case 1:Object=OBJECT_CUBE;break;
        case 2:Object=OBJECT_CONE;break;
        case 3:Object=OBJECT_CYLINDER;break;
        case 4:Object=OBJECT_SPHERE;break;
        case 5:Object=OBJECT_PLY;break;
        case 6:Object=OBJECT_HIER;break;
        case 7:Object=OBJECT_CHESS;break;
        case 8:Object=OBJECT_SCENE;break;
    }
    update();
}

void _gl_widget::slotMaterial(int index)
{
    switch(index)
    {
        case 0:actMaterial=MAT_NULL;break;
        case 1:actMaterial=MAT_GOLD;break;
        case 2:actMaterial=MAT_PLASTIC;break;
        case 3:actMaterial=MAT_RUBBER;break;
    }
    update();
}

void _gl_widget::slotPerspective(int index)
{
    cout<<index<<endl;
    switch(index)
    {
        case 0: perspective = true;break;
        case 1: perspective = false;break;
    }
    update();
}

void _gl_widget::slotAlphaPlus()
{
    alpha += ANGLE_STEP * modAlpha;
}

void _gl_widget::slotAlphaMinus()
{
    alpha -= ANGLE_STEP * modAlpha;
}

void _gl_widget::slotAlphaSlider(int mod)
{
    modAlpha = ( (float)mod ) / 100;
}

void _gl_widget::slotBetaPlus()
{
    beta += ANGLE_STEP * modBeta;
}

void _gl_widget::slotBetaMinus()
{
    beta -= ANGLE_STEP * modBeta;
}

void _gl_widget::slotBetaSlider(int mod)
{
    modBeta = ( (float)mod ) / 100;
}

void _gl_widget::slotGammaPlus()
{
    gamma += ANGLE_STEP * modGamma;
}

void _gl_widget::slotGammaMinus()
{
    gamma -= ANGLE_STEP * modGamma;
}

void _gl_widget::slotGammaSlider(int mod)
{
    modGamma = ( (float)mod ) / 100;
}
