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
  // Models Keys
  //    Tetrahedron
  case Qt::Key_1:
        Object=OBJECT_TETRAHEDRON;
        Window->modelSelectorInteraction(0);
  break;

  //    Cube
  case Qt::Key_2:
        Object=OBJECT_CUBE;
        Window->modelSelectorInteraction(1);
  break;

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

  //    Hierarchical Model
  case Qt::Key_7:
        Object=OBJECT_HIER;
        Window->modelSelectorInteraction(6);
  break;

  //    Chessboard
  case Qt::Key_8:
        Object=OBJECT_CHESS;
        Window->modelSelectorInteraction(7);
  break;

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

  //    Animation key
  case Qt::Key_A:animation=!animation;break;

  //    Unlit Render mode keys
  case Qt::Key_P:
        Draw_point=!Draw_point;
        Window->pointCheckBoxInteraction(Draw_point);
  break;
  case Qt::Key_L:
        Draw_line=!Draw_line;
        Window->lineCheckBoxInteraction(Draw_line);
  break;
  case Qt::Key_F1:
        Draw_fill=!Draw_fill;
        Window->fillCheckBoxInteraction(Draw_fill);
  break;
  case Qt::Key_F2:
        Draw_chess=!Draw_chess;
        Window->chessCheckBoxInteraction(Draw_chess);
  break;


  //    Camera Movement Keys
  case Qt::Key_Left:Observer_angle_y-=ANGLE_STEP;break;
  case Qt::Key_Right:Observer_angle_y+=ANGLE_STEP;break;
  case Qt::Key_Up:
        Observer_angle_x-=ANGLE_STEP;
        Window->text(std::to_string(Observer_angle_x));
  break;
  case Qt::Key_Down:
        Observer_angle_x+=ANGLE_STEP;
        Window->text(std::to_string(Observer_angle_x));
  break;
  case Qt::Key_Minus:Observer_distance*=1.2;break;
  case Qt::Key_Plus:Observer_distance/=1.2;break;


  // Lighting Keys
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
  //    Toggle between 3 materials
  case Qt::Key_M: ;break;
  }

  this->constrainAngles();
  cout<<"ALPHA  :"<<alpha<<" ("<<modAlpha<<") BETA: "<<beta<<" ("<<modBeta<<")    GAMMA: "<<gamma<<" ("<<modGamma<<")"<<endl;
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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
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
  glFrustum(X_MIN,X_MAX,Y_MIN,Y_MAX,FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);
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
    case OBJECT_HIER:Hier.draw(0, alpha, beta, gamma);break;
    case OBJECT_CHESS:Chess.draw(0);break;
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
    case OBJECT_HIER:Hier.draw(1, alpha, beta, gamma);break;
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
    case OBJECT_CYLINDER:Cylinder.draw_fill();break;
    case OBJECT_SPHERE:Sphere.draw_fill();break;
    case OBJECT_PLY:Ply.draw_fill();break;
    case OBJECT_HIER:Hier.draw(2, alpha, beta, gamma);break;
    case OBJECT_CHESS:Chess.draw(2);break;
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
    case OBJECT_HIER:Hier.draw(3, alpha, beta, gamma);break;
    case OBJECT_CHESS:Chess.draw(3);break;
    default:break;
    }
  }

  // LIGHTING
  //    Flat Lighting
  if(flatLit)
  {
      glEnable(GL_LIGHTING);
      switch (Object)
      {
          case OBJECT_TETRAHEDRON:
                Tetrahedron.setFlatLight();
                Tetrahedron.drawIlum();
          break;

          case OBJECT_CUBE:
                Cube.setFlatLight();
                Cube.setMaterialAmbient({0.24725f, 0.1995f, 0.0745f});
                Cube.setMaterialSpecular({0.628281f, 0.555802f, 0.366065f});
                Cube.setMaterialDiffuse({0.75164f, 0.60648f, 0.22648f});
                Cube.setMaterialShininess(51.2);

                Cube.drawIlum();
          break;

          case OBJECT_CONE:
                Cone.setFlatLight();
                Cone.drawIlum();
          break;

          case OBJECT_CYLINDER:
                Cylinder.setFlatLight();
                Cylinder.drawIlum();
          break;

          case OBJECT_SPHERE:Sphere.drawIlum();
                Sphere.setFlatLight();
                Sphere.drawIlum();
          break;

          case OBJECT_PLY:
                Ply.setFlatLight();
                Ply.drawIlum();
          break;
          case OBJECT_HIER:
                Hier.draw(4, alpha, beta, gamma);
          break;
          case OBJECT_CHESS:
                Chess.setSmoothLight();
                Chess.drawIlum();
          break;
          default:break;
      }
      glDisable(GL_LIGHTING);
  }

  //    Smooth Ligthing
  if(smoothLit)
  {
      glEnable(GL_LIGHTING);
      switch (Object)
      {
          case OBJECT_TETRAHEDRON:
                Tetrahedron.setSmoothLight();
                Tetrahedron.drawIlum();
          break;

          case OBJECT_CUBE:
                Cube.setSmoothLight();
                Cube.setMaterialAmbient({0.24725f, 0.1995f, 0.0745f});
                Cube.setMaterialSpecular({0.628281f, 0.555802f, 0.366065f});
                Cube.setMaterialDiffuse({0.75164f, 0.60648f, 0.22648f});
                Cube.setMaterialShininess(51.2);

                Cube.drawIlum();
          break;

          case OBJECT_CONE:
                Cone.setSmoothLight();
                Cone.drawIlum();
          break;

          case OBJECT_CYLINDER:
                Cylinder.setSmoothLight();
                Cylinder.drawIlum();
          break;

          case OBJECT_SPHERE:Sphere.drawIlum();
                Sphere.setSmoothLight();
                Sphere.drawIlum();
          break;

          case OBJECT_PLY:
                Ply.setSmoothLight();
                Ply.drawIlum();
          break;
          case OBJECT_HIER:
                Hier.draw(4, alpha, beta, gamma);
          break;
          case OBJECT_CHESS:
                Chess.setSmoothLight();
                Chess.drawIlum();
          break;
          default:break;
      }
      glDisable(GL_LIGHTING);
  }


  if(unLitTextured)
  {
      switch (Object)
      {
           case OBJECT_CHESS:
                Chess.setTexture(texture);
                Chess.drawUnLitTex();
           break;
           default:break;
      }
  }


  if(firstLight)
  {
      GLfloat lightPos[4] = {1,1,1,0.0};
      glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
      glEnable(GL_LIGHT0);
  }
  else
  {
      glDisable(GL_LIGHT0);
  }

  if(secondLight)
  {
      GLfloat lightPos[4] = {0,5,2.5,1};
      GLfloat lightColor[3] = {1,0,1};
      glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
      glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor);
      glEnable(GL_LIGHT1);

  }
  else
  {
      glDisable(GL_LIGHT1);
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

/*  Changes Made:
 * [P3] Initializing the angles, angle modifiers, and animation.
 *      Added initializing routines for the objects.
*/
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

  // Angle variables and animations
  alpha = 0;
  beta  = 0;
  gamma = 0;
  modAlpha = 1;
  modBeta  = 1;
  modGamma = 1;
  animation = false;
  foward1 = true;
  foward2 = true;

  Draw_point=false;
  Draw_line=true;
  Draw_fill=false;
  Draw_chess=false;

  // OBJECTS
  Cylinder.initialize();
  Sphere.initialize();
  Cone.initialize();
  Ply.initialize(1,"../ply_models/beethoven.ply");
  Chess.initialize(1,1);

  // LIGHTING
  flatLit = false;
  smoothLit = false;
  firstLight = false;
  secondLight = false;

  // TEXTURES
  unLitTextured = false;
  litFlatTextured = false;
  litSmoothTextured = false;
}

// ANIMATION CONTRAINTS
void _gl_widget::constrainAngles()
{
  if(beta > 42)
      beta = 42;

  if(beta < -42)
      beta = -42;

  if(gamma > 10)
      gamma = 10;

  if(gamma < -10)
      gamma = -10;

   alpha = fmod(alpha,360);
}

// COMMUNICATION WITH QT
//  SLOTS
void _gl_widget::slotPoint(int state)
{
    if(state == Qt::Checked)
    {
        Draw_point = true;
    }
    else
    {
        Draw_point = false;
    }
    update();

}
void _gl_widget::slotLine(int state)
{

    if(state == Qt::Checked)
    {
        Draw_line = true;
    }
    else
    {
        Draw_line = false;
    }

    update();

}
void _gl_widget::slotFill(int state)
{
    if(state == Qt::Checked)
    {
        Draw_fill= true;
    }
    else
    {
        Draw_fill = false;
    }
    update();

}
void _gl_widget::slotChess(int state)
{
    if(state == Qt::Checked)
    {
        Draw_chess = true;
    }
    else
    {
        Draw_chess = false;
    }
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
    }
    update();
}

//  Animation Slot
void _gl_widget::slotAnimationToggle()
{
    if(animation)
    {
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

        alpha  += ANGLE_STEP*modBeta;

        cout<<"ALPHA  :"<<alpha<<" ("<<modAlpha<<") BETA: "<<beta<<" ("<<modBeta<<")    GAMMA: "<<gamma<<" ("<<modGamma<<")"<<endl;
        update();
    }
}

//  Get the texture from Qt
void _gl_widget::getTexture(QImage _texture)
{
    this->texture = _texture;
}
