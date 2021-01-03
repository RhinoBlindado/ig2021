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

      // ANIMATION
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

      // UNLIT DRAWING
      //    Draw Point
      case Qt::Key_P:
            Draw_point=!Draw_point;
            Window->pointCheckBoxInteraction(Draw_point);
      break;

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

    // LIGHTING & TEXTURES
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
    case Qt::Key_Up:
        Observer_angle_x-=ANGLE_STEP;
        Window->text(std::to_string(Observer_angle_x));
    break;
    case Qt::Key_Down:
        Observer_angle_x+=ANGLE_STEP;
        Window->text(std::to_string(Observer_angle_x));
    break;
    //      Zoom
    case Qt::Key_Minus:Observer_distance*=1.2;break;
    case Qt::Key_Plus:Observer_distance/=1.2;break;

    // PROYECTION
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
  if(perspective)
      glFrustum(X_MIN,X_MAX,Y_MIN,Y_MAX,FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);
    else
      glOrtho(10*X_MIN*Observer_distance, 10*X_MAX*Observer_distance,
              10*Y_MIN*Observer_distance, 10*Y_MAX*Observer_distance,
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

      _ply a,b,c,d;
  //a.initialize(1,"../ply_models/airplane_fixed.ply");
  //b.initialize(1,"../ply_models/ant.ply");
 // cout<<"BUNNY:"<<endl;
//  d.initialize(1,"../ply_models/bunny.ply");
  //c.initialize(4,"../ply_models/sandal.ply");

//  glMatrixMode(GL_MODELVIEW);

//  glPushMatrix();
//      glPushMatrix();
//          glTranslated(0, 3, 0);
//          c.draw_chess();
//      glPopMatrix();

//      glPushMatrix();
//          glTranslated(0,0,-4);
//          b.draw_chess();
//      glPopMatrix();

//      glPushMatrix();
//          glTranslated(2,0,0);
//          a.draw_chess();
//      glPopMatrix();
//  glPopMatrix();



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

  // LIGHTING

  //    Toggle Lights
  light.toggleFirstLight(firstLight);
  light.toggleSecondLight(secondLight);

  //    Flat Lighting
  if(flatLit)
  {
      switch (Object)
      {
          case OBJECT_TETRAHEDRON:
                Tetrahedron.setFlatLight();

                Tetrahedron.setMaterialAmbient(__material[actMaterial].ambient);
                Tetrahedron.setMaterialSpecular(__material[actMaterial].specular);
                Tetrahedron.setMaterialDiffuse(__material[actMaterial].diffuse);
                Tetrahedron.setMaterialShininess(__material[actMaterial].shine);

                Tetrahedron.drawIlum();
          break;

          case OBJECT_CUBE:
                Cube.setFlatLight();

                Cube.setMaterialAmbient(__material[actMaterial].ambient);
                Cube.setMaterialSpecular(__material[actMaterial].specular);
                Cube.setMaterialDiffuse(__material[actMaterial].diffuse);
                Cube.setMaterialShininess(__material[actMaterial].shine);

                Cube.drawIlum();
          break;

          case OBJECT_CONE:
                Cone.setFlatLight();

                Cone.setMaterialAmbient(__material[actMaterial].ambient);
                Cone.setMaterialSpecular(__material[actMaterial].specular);
                Cone.setMaterialDiffuse(__material[actMaterial].diffuse);
                Cone.setMaterialShininess(__material[actMaterial].shine);

                Cone.drawIlum();
          break;

          case OBJECT_CYLINDER:
                Cylinder.setFlatLight();

                Cylinder.setMaterialAmbient(__material[actMaterial].ambient);
                Cylinder.setMaterialSpecular(__material[actMaterial].specular);
                Cylinder.setMaterialDiffuse(__material[actMaterial].diffuse);
                Cylinder.setMaterialShininess(__material[actMaterial].shine);

                Cylinder.drawIlum();
          break;

          case OBJECT_SPHERE:
                Sphere.setFlatLight();

                Sphere.setMaterialAmbient(__material[actMaterial].ambient);
                Sphere.setMaterialSpecular(__material[actMaterial].specular);
                Sphere.setMaterialDiffuse(__material[actMaterial].diffuse);
                Sphere.setMaterialShininess(__material[actMaterial].shine);

                Sphere.drawIlum();
          break;

          case OBJECT_PLY:
                Ply.setFlatLight();

                Ply.setMaterialAmbient(__material[actMaterial].ambient);
                Ply.setMaterialSpecular(__material[actMaterial].specular);
                Ply.setMaterialDiffuse(__material[actMaterial].diffuse);
                Ply.setMaterialShininess(__material[actMaterial].shine);

                Ply.drawIlum();
          break;
          case OBJECT_HIER:
                Hier.draw(4);
          break;
          case OBJECT_CHESS:
                Chess.setFlatLight();

                Chess.setMaterialAmbient(__material[actMaterial].ambient);
                Chess.setMaterialSpecular(__material[actMaterial].specular);
                Chess.setMaterialDiffuse(__material[actMaterial].diffuse);
                Chess.setMaterialShininess(__material[actMaterial].shine);

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
                Tetrahedron.setSmoothLight();

                Tetrahedron.setMaterialAmbient(__material[actMaterial].ambient);
                Tetrahedron.setMaterialSpecular(__material[actMaterial].specular);
                Tetrahedron.setMaterialDiffuse(__material[actMaterial].diffuse);
                Tetrahedron.setMaterialShininess(__material[actMaterial].shine);

                Tetrahedron.drawIlum();
          break;

          case OBJECT_CUBE:
                Cube.setSmoothLight();

                Cube.setMaterialAmbient(__material[actMaterial].ambient);
                Cube.setMaterialSpecular(__material[actMaterial].specular);
                Cube.setMaterialDiffuse(__material[actMaterial].diffuse);
                Cube.setMaterialShininess(__material[actMaterial].shine);

                Cube.drawIlum();
          break;

          case OBJECT_CONE:
                Cone.setSmoothLight();

                Cone.setMaterialAmbient(__material[actMaterial].ambient);
                Cone.setMaterialSpecular(__material[actMaterial].specular);
                Cone.setMaterialDiffuse(__material[actMaterial].diffuse);
                Cone.setMaterialShininess(__material[actMaterial].shine);

                Cone.drawIlum();
          break;

          case OBJECT_CYLINDER:
                Cylinder.setSmoothLight();

                Cylinder.setMaterialAmbient(__material[actMaterial].ambient);
                Cylinder.setMaterialSpecular(__material[actMaterial].specular);
                Cylinder.setMaterialDiffuse(__material[actMaterial].diffuse);
                Cylinder.setMaterialShininess(__material[actMaterial].shine);

                Cylinder.drawIlum();
          break;

          case OBJECT_SPHERE:
                Sphere.setSmoothLight();

                Sphere.setMaterialAmbient(__material[actMaterial].ambient);
                Sphere.setMaterialSpecular(__material[actMaterial].specular);
                Sphere.setMaterialDiffuse(__material[actMaterial].diffuse);
                Sphere.setMaterialShininess(__material[actMaterial].shine);

                Sphere.drawIlum();
          break;

          case OBJECT_PLY:
                Ply.setSmoothLight();

                Ply.setMaterialAmbient(__material[actMaterial].ambient);
                Ply.setMaterialSpecular(__material[actMaterial].specular);
                Ply.setMaterialDiffuse(__material[actMaterial].diffuse);
                Ply.setMaterialShininess(__material[actMaterial].shine);

                Ply.drawIlum();
          break;
          case OBJECT_HIER:
                Hier.draw(4);
          break;
          case OBJECT_CHESS:
                Chess.setSmoothLight();

                Chess.setMaterialAmbient(__material[actMaterial].ambient);
                Chess.setMaterialSpecular(__material[actMaterial].specular);
                Chess.setMaterialDiffuse(__material[actMaterial].diffuse);
                Chess.setMaterialShininess(__material[actMaterial].shine);

                Chess.drawIlum();
          break;
          default:break;
      }
  }

  // TEXTURES
  //    Unlit Textured
  if(unLitTextured)
  {
    switch (Object)
    {
        case OBJECT_CYLINDER:
            Cylinder.setTexture(texture);
            Cylinder.setLighting(0);
            Cylinder.drawTex();
        break;

        case OBJECT_SPHERE:
            Sphere.setTexture(texture);
            Sphere.setLighting(0);
            Sphere.drawTex();
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
            Cylinder.setTexture(texture);
            Cylinder.setLighting(1);
            Cylinder.drawTex();
        break;

        case OBJECT_SPHERE:
            Sphere.setTexture(texture);
            Sphere.setLighting(1);
            Sphere.drawTex();
        break;

        case OBJECT_CHESS:
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
          Cylinder.setTexture(texture);
          Cylinder.setLighting(2);
          Cylinder.drawTex();
        break;

        case OBJECT_SPHERE:
          Sphere.setTexture(texture);
          Sphere.setLighting(2);
          Sphere.drawTex();
        break;

        case OBJECT_CHESS:
            Chess.setTexture(texture);
            Chess.setLighting(2);
            Chess.drawTex();
        break;
        default:break;
      }
  }

  // ANIMATION
  //    Set the degrees of rotation of each degree of freedom.
  this->constrainAngles();
  Hier.rotateFirstDegree(alpha);
  Hier.rotateSecondDegree(beta);
  Hier.rotateThirdDegree(gamma);

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

  glewInit();


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
  delta = 0;
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
  Cylinder.initialize(1, 0.5, 4, 4, 20, true, true);
  Sphere.initialize(0.5, 40, 40);
  Cone.initialize();
  Ply.initialize(1,"../ply_models/beethoven.ply");
  Chess.initialize(1,1);

  // LIGHTING
  light.initialize();
  flatLit = false;
  smoothLit = false;
  firstLight = false;
  secondLight = false;

  // MATERIAL
  __material[MAT_GOLD].ambient  = _vertex3f(0.24725f, 0.2245f, 0.0645f);
  __material[MAT_GOLD].diffuse  = _vertex3f(0.34615f, 0.3143f, 0.0903f);
  __material[MAT_GOLD].specular = _vertex3f(0.797357f, 0.723991f, 0.208006f);
  __material[MAT_GOLD].shine    = 83.2f;

  __material[MAT_PLASTIC].ambient  = _vertex3f(0.0f, 0.1f, 0.06f);
  __material[MAT_PLASTIC].diffuse  = _vertex3f(0.0f, 0.50980392f, 0.50980392f);
  __material[MAT_PLASTIC].specular = _vertex3f(0.50196078f, 0.50196078f, 0.50196078f);
  __material[MAT_PLASTIC].shine    = 32.0f;

  __material[MAT_RUBBER].ambient  = _vertex3f(0.05f, 0.0f, 0.0f);
  __material[MAT_RUBBER].diffuse = _vertex3f(0.5f, 0.4f, 0.4f);
  __material[MAT_RUBBER].specular  = _vertex3f(0.7f, 0.04f, 0.04f);
  __material[MAT_RUBBER].shine    = 10.f;

  __material[MAT_NULL].ambient = _vertex3f(0.2, 0.2, 0.2);
  __material[MAT_NULL].diffuse = _vertex3f(0.8, 0.8, 0.8);
  __material[MAT_NULL].specular  = _vertex3f(0.0, 0.0, 0.0);
  __material[MAT_NULL].shine    = 0.0f;

  actMaterial = 3;

  //    Textures
  unLitTextured = false;
  litFlatTextured = false;
  litSmoothTextured = false;

  // CAMERA
  perspective = true;
  lastClickX = 0;
  lastClickY = 0;
  mouseDrag = false;

  // PICK
  Window_width = 0;
  Window_height = 0;
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
        Draw_point = true;
    else
        Draw_point = false;
    update();
}

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
        alpha = fmod(alpha, 360);

        if(secondLight)
        {
            delta = fmod(delta += ANGLE_STEP, 360);
            light.rotateSecondLight(delta);
        }

        update();
    }
}

//  Get the texture from Qt
void _gl_widget::getTexture(QImage _texture)
{
    this->texture = _texture;
}


// MOUSE EVENTS
//     Drag Event
void _gl_widget::mouseMoveEvent(QMouseEvent *event)
{
    if(mouseDrag)
    {
        Observer_angle_x += (event->y() - lastClickY) * 0.05;
        Observer_angle_y += (event->x() - lastClickX) * 0.05;
    }
    update();
}

//      Click Event
void _gl_widget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::RightButton)
    {
        Window_width = this->size().width();
        Window_height =this->size().height();

        Selection_position_x = (event->x());
        Selection_position_y = (Window_height - event->y());
        this->pick();
    }

    if(event->buttons() & Qt::LeftButton)
    {
        lastClickX = event->x();
        lastClickY = event->y();
        mouseDrag = true;
    }
    update();
}

//      Release Event
void _gl_widget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mouseDrag = false;
    }
    update();
}

//      Scroll Wheel Zoom
void _gl_widget::wheelEvent(QWheelEvent *scrollWheel)
{
    Observer_distance += (-(float)(scrollWheel->angleDelta().y()))/360;
    update();
}


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
  cout<<"WIN X:"<<Window_width<<" Y:"<<Window_height<<endl;
  cout<<"MOUSE X:"<<Selection_position_x<<" Y: "<<Selection_position_y<<endl;
  cout<<"SEL COLOR: "<<Color<<endl;
  cout<<"SEL TRIANGLE="<<selTriangle<<endl;
  if(selTriangle == 16777215)
      selTriangle = -1;

  cout<<"------"<<endl;
  switch (Object)
  {
      case OBJECT_TETRAHEDRON:Tetrahedron.setTrigSelected(selTriangle);break;
      case OBJECT_CUBE:Cube.setTrigSelected(selTriangle);break;
      case OBJECT_CONE:Cone.setTrigSelected(selTriangle);break;
      case OBJECT_CYLINDER:Cylinder.setTrigSelected(selTriangle);break;
      case OBJECT_SPHERE:Sphere.setTrigSelected(selTriangle);break;
      case OBJECT_PLY:Ply.setTrigSelected(selTriangle);break;
      case OBJECT_CHESS:Chess.setTrigSelected(selTriangle);break;
      default:break;
  }

  /*************************/

  glDeleteTextures(1,&Color_texture);
  glDeleteTextures(1,&Depth_texture);
  glDeleteFramebuffers(1,&FBO);
  // the normal framebuffer takes the control of drawing
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER,defaultFramebufferObject());
}
